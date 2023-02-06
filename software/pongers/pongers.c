
#include "gameutil.h"
#include "sys/alt_alarm.h"
#include "alt_types.h"


int main()
{
	// Have to set up these pointers to open the device
	// Reference : https://faculty-web.msoe.edu/johnsontimoj/EE3921/files3921/nios_pixel_sw.pdf
	alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev;
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev(VIDEO_PIXEL_BUFFER_DMA_0_NAME);
	// Check for error
	if ( pixel_buf_dma_dev == NULL)
		printf ("Error: could not open pixel buffer device \n");
	else
		printf ("Opened pixel buffer device \n");
	alt_up_char_buffer_dev * char_buf_dev;
	char_buf_dev = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	if ( char_buf_dev == NULL)
		printf ("Error: could not open char buffer device \n");
	else
		printf ("Opened char buffer device \n");

	alt_up_char_buffer_init(char_buf_dev);
	alt_up_char_buffer_init(char_buf_dev);

	// Game objects
	Game game = {SCREEN_WIDTH, SCREEN_HEIGHT, {0,0}, NUM_BALLS, NUM_PADDLES,
			{{BALL_XDEFAULT, BALL_YDEFAULT, BALL_XSPEED, BALL_YSPEED, BALL_WIDTH, BALL_HEIGHT, BALL_COLOUR}}, //Balls
			{{0, 0, 0, 0, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR}, //Paddles
					{SCREEN_WIDTH-PADDLE_WIDTH, 0, 0, 0, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR}},
			{0,0,0,0,0,0,0,0}, //User input
			0 // Game time
	};
	int time = game.time; // Game timer measured in s

	//Display strings
	char time_str[10];
	sprintf(time_str, "Time: %u", time);
	char score_str[20];

	// Alarm setup - executes the callback function periodically (every second)
	alt_u32 alarm_callback(void *context) {
		time += 1;
		sprintf(time_str, "Time: %u", time);
		return alt_ticks_per_second();
	}
	static alt_alarm alarm;
	// Setup alarm to call the callback function every N_TICKS
	if (alt_alarm_start(&alarm, alt_ticks_per_second(), alarm_callback, NULL) < 0){
		printf ("No System Clock Available\n");
	}

	// The makefile is not working as intended so the linker is unable to compile the dependencies.
	// As a result, we have to manually include the functions here ********
	// Updates paddle positions
	void update_paddle(Game* game) {
		int* user_input = (game -> user_input);
		int len = (game->paddles_len);
		Rectangle* paddle = (game -> paddles);
		// Adjust speed according to user input
		int SW_0 = user_input[0];
		int SW_1 = user_input[1];
		if(SW_0) // SW_0 is on (left paddle)
			paddle[0].yspeed = -PADDLE_SPEED;
		else
			paddle[0].yspeed = PADDLE_SPEED;
		if(SW_1) // SW_1 is on (right paddle)
			paddle[1].yspeed = -PADDLE_SPEED;
		else
			paddle[1].yspeed = PADDLE_SPEED;
		// Adjust paddle positions
		for(int i = 0; i< len; i++) {
			// Update position
			paddle[i].y += paddle[i].yspeed;
			paddle[0].x = 0;
			paddle[1].x = SCREEN_WIDTH - paddle[1].width;
			// Check for collisions
			if (paddle[i].y + paddle[i].height >= SCREEN_HEIGHT) {
				paddle[i].y = SCREEN_HEIGHT - paddle[i].height;
				paddle[i].yspeed = 0;
			}
			else if (paddle[i].y <= 0) {
				paddle[i].y = 0;
				paddle[i].yspeed = 0;
			}
		}
	}
	// Updates the position of each Rectangle object
	// "bounces" each object upon collision with screen top/bottom edges
	// or paddle objects
	void update_ball(Game* game) {
		int rect_len = (game -> balls_len);
		Rectangle* rect = (game -> balls);
		Rectangle* paddles = (game -> paddles);
		int* scores = (game -> scores);
		for(int i = 0; i< rect_len; i++) {
			// Update position
			rect[i].x += rect[i].xspeed;
			rect[i].y += rect[i].yspeed;
			// Check for collisions
			if(rect[i].x + rect[i].width >= SCREEN_WIDTH || rect[i].x + rect[i].width >= paddles[1].x) {
				// Collision with right paddle
				if(rect[i].y + rect[i].height >= paddles[1].y && rect[i].y <= paddles[1].y + paddles[1].height) {
					rect[i].x = paddles[1].x - rect[i].width;
					rect[i].xspeed*=-1; // Bounce
				}
				else { // Goal - player 1 scored
					// Reset ball position
					rect[i].x = BALL_XDEFAULT;
					rect[i].xspeed*=-1;
					// Add 1 to left player's score
					scores[0] += 1;
				}
			}
			else if (rect[i].x <= 0 || rect[i].x <= paddles[0].width) {
				// Collision with left paddle
				if(rect[i].y + rect[i].height >= paddles[0].y && rect[i].y <= paddles[0].y + paddles[0].height) {
					rect[i].x = paddles[0].x + paddles[0].width;
					rect[i].xspeed*=-1; //Bounce
				}
				else { // Goal - player 2 scored
					// Reset ball position
					rect[i].x = BALL_XDEFAULT;
					rect[i].xspeed*=-1;
					// Add 1 to right player's score
					scores[1] += 1;
				}
			}
			else if (rect[i].y + rect[i].height >= SCREEN_HEIGHT) {
				rect[i].y = SCREEN_HEIGHT - rect[i].height;
				rect[i].yspeed *= -1;
			}
			else if (rect[i].y <= 0) {
				rect[i].y = 0;
				rect[i].yspeed *= -1;
			}
		}
	}
	void clear(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, alt_up_char_buffer_dev * char_buf_dev,int buffer) {
		// Clear the screen
		alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev, buffer);
		alt_up_char_buffer_clear(char_buf_dev);
	}
	// Renders game components on the screen
	void draw(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev,int colour, int buffer, Rectangle rect[], int len) {
		// Draw each rectangle
		for(int i = 0; i<len; i++) {

			// Naive implementation of drawing each pixel - Much slower than draw_box function
			// alt_up_pixel_buffer_dma_draw() draws to the back buffer (buffer=1)
	//		for(int x = rect[i].x; x<rect[i].x + rect[i].width; x++) {
	//			for(int y = rect[i].y; y<rect[i].y + rect[i].height; y++) {
	//				alt_up_pixel_buffer_dma_draw(pixel_buf_dma_dev, colour, x, y);
	//			}
	//		}

			alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev,
					rect[i].x, rect[i].y, rect[i].x + rect[i].width - 1,
					rect[i].y + rect[i].height - 1,
					colour, buffer);
		}
	}
	void get_user_input(int* user_input) {
		int SW = IORD(SW_BASE, 0);
		for(int i = 0; i<8; i++) {
			user_input[i] = (0b1 << i) & SW;
		}
	}
	void reset_game(Game* game) {
		// Reset score
		int* scores = game -> scores;
		scores[0] = 0;
		scores[1] = 0;
		// Reset game time
		time = 0;
	}
	int check_win(Game* game) {
		int* scores = game->scores;
		if(scores[0]>=MAX_SCORE || scores[1]>=MAX_SCORE){
			reset_game(game);
			return 1;
		}
		return 0;

	}
	void run_game_tick(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, alt_up_char_buffer_dev * char_buf_dev, int buffer, Game* game) {
		// Check for winner
		if(check_win(game)) {
			clear(pixel_buf_dma_dev, char_buf_dev,0);
		}
		int* user_input = (game -> user_input);
		Rectangle* balls = (game -> balls);
		Rectangle* paddles = (game -> paddles);
		// Wait for screen refresh
		alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev));

		get_user_input(user_input);
		// Cleanup - erase old objects
		draw(pixel_buf_dma_dev, BACKGROUND_COLOUR,buffer, balls, NUM_BALLS);
		draw(pixel_buf_dma_dev, BACKGROUND_COLOUR, buffer, paddles, NUM_PADDLES);
		// Game logic
		update_ball(game);
		update_paddle(game);
		// Render the screen
		draw(pixel_buf_dma_dev, BALL_COLOUR, buffer, balls, NUM_BALLS);
		draw(pixel_buf_dma_dev, PADDLE_COLOUR, buffer, paddles, NUM_PADDLES);
	}
	// ****************
	// Clear screen
	clear(pixel_buf_dma_dev, char_buf_dev,0); // Current screen
	//clear(pixel_buf_dma_dev, 0, char_buf_dev); // Char buffer
	while(1) {
		run_game_tick(pixel_buf_dma_dev, char_buf_dev, 0, &game);
		sprintf(score_str, "%u - %u", game.scores[0], game.scores[1]);
		alt_up_char_buffer_string(char_buf_dev, score_str, 37, 2);
		alt_up_char_buffer_string(char_buf_dev, time_str, 65, 2);
		usleep(10000);
	}
	return 0;
}
