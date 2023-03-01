
#include "gameutil.h"
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "altera_modular_adc.h"

int pause_flag = 0;
int main_menu_flag = 0;
// Interrupt setup for PIO
static void pio_isr(void * context, alt_u32 id)    //this is the ISR
{
	pause_flag = !pause_flag;
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE, 0x0);    //resets edge capture register so interrupt can be triggered again
	                                                    //can write anything to the register to reset it, does not have to be 0x0
}
void init_pio_interrupt()
{
	alt_ic_isr_register(SW_IRQ_INTERRUPT_CONTROLLER_ID, SW_IRQ, (void *)pio_isr, NULL, 0x0);    //connects the ISR with the IRQ. Also requires *context and can choose a flag?
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SW_BASE, 0x20);    //0x20 = 0b0010_0000, so this will trigger an interrupt on rising edge of sw[2]
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SW_BASE, 0x0);    //resets edge capture register
}

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
			0,0,0,0, // ADC values
			{0,0,0,0,0,0,0,0}, //User input
			0 // Game time in s
	};
	//Display strings
	char time_str[10];
	sprintf(time_str, "Time: %u", game.time);
	char score_str[20];

	// Alarm setup - executes the callback function periodically (every second)
	alt_u32 alarm_callback(void *context) {
		game.time += 1;
		sprintf(time_str, "Time: %u", game.time);
		return alt_ticks_per_second();
	}
	static alt_alarm alarm;
	// Setup alarm to call the callback function every N_TICKS
	if (alt_alarm_start(&alarm, alt_ticks_per_second(), alarm_callback, NULL) < 0){
		printf ("No System Clock Available\n");
	}


	// The makefile is not working as intended so the linker is unable to link the dependencies.
	// As a result, we have to manually include the functions here ********
	void cheat_code(Game* game) {
		int* user_input = game->user_input;
		Rectangle* paddles = game ->paddles;
		if(user_input[3]) {
			paddles[0].height=SCREEN_HEIGHT-1;
			paddles[0].y=0;
			paddles[0].yspeed=0;
		} else { paddles[0].height=PADDLE_HEIGHT-1;}
		if(user_input[4]) {
			paddles[1].height=SCREEN_HEIGHT-1;
			paddles[1].y=0;
			paddles[1].yspeed=0;
		} else {paddles[1].height=PADDLE_HEIGHT-1;}
	}
	// Updates paddle positions
	void update_paddle(Game* game) {
		int* user_input = (game -> user_input);
		int len = (game->paddles_len);
		Rectangle* paddle = (game -> paddles);
		float adc_volt_left = game->adc_volt_left;
		float adc_volt_right = game->adc_volt_right;
		// Adjust speed according to user input
		int SW_0 = user_input[0];
		int SW_1 = user_input[1];
		if(adc_volt_left >=2.6) {
			paddle[0].yspeed = adc_volt_left;
		}
		else if(adc_volt_left <=2.4) {
			paddle[0].yspeed = -(5-adc_volt_left);
		}
		else {
			paddle[0].yspeed = 0;
		}
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
	int sign(int n) {
		if(n<0)
			return -1;
		return 1;
	}
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
					if(sign(rect[i].yspeed)!=sign(paddles[1].yspeed)&& paddles[1].yspeed!=0) // Ball bounces in direction of paddle movement
						rect[i].yspeed*=-1;
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
					if(sign(rect[i].yspeed)!=sign(paddles[0].yspeed) && paddles[0].yspeed!=0) // Ball bounces in direction of paddle movement
						rect[i].yspeed*=-1;
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
	void get_user_input(Game* game) {
		int SW = IORD(SW_BASE, 0);
		int* user_input = game->user_input;
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
		game -> time = 0;
		sprintf(time_str, "Time: %u", game->time);
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
		Rectangle* balls = (game -> balls);
		Rectangle* paddles = (game -> paddles);
		// Wait for screen refresh
		alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev));

		// User input
		get_user_input(game);
		// Cleanup - erase old objects
		draw(pixel_buf_dma_dev, BACKGROUND_COLOUR,buffer, balls, NUM_BALLS);
		draw(pixel_buf_dma_dev, BACKGROUND_COLOUR, buffer, paddles, NUM_PADDLES);
		// Game logic
		cheat_code(game); // Checks for cheat code input
		update_ball(game);
		update_paddle(game);
		// Render the screen
		draw(pixel_buf_dma_dev, BALL_COLOUR, buffer, balls, NUM_BALLS);
		draw(pixel_buf_dma_dev, PADDLE_COLOUR, buffer, paddles, NUM_PADDLES);
	}
	void music_on(){
			IOWR(AUDIO_MODULE_0_BASE, 0, 0x1);
			printf("Read %d\n", IORD(AUDIO_MODULE_0_BASE, 0));
		}
	void music_off(){
			IOWR(AUDIO_MODULE_0_BASE, 0, 0x0);
			printf("Read %d\n", IORD(AUDIO_MODULE_0_BASE, 0));
		}

	void pause_menu(alt_up_char_buffer_dev * char_buf_dev) {
		alt_up_char_buffer_string(char_buf_dev, "Pain Pong", 37, 8);
		//Play music
		music_on();

	}
	void clear_pause_menu(alt_up_char_buffer_dev * char_buf_dev) {
		alt_up_char_buffer_string(char_buf_dev, "         ", 37, 8);
		//Stop Music
		music_off();

	}
	// ****************

	// Clear screen
	clear(pixel_buf_dma_dev, char_buf_dev,0); // Current screen
	//clear(pixel_buf_dma_dev, 0, char_buf_dev); // Char buffer

	// Initialize interrupts
	init_pio_interrupt();

	// ADC setup
	adc_stop(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
	adc_set_mode_run_once(MODULAR_ADC_0_SEQUENCER_CSR_BASE);

	while(1) {
		if(pause_flag) { // Pause menu
			pause_menu(char_buf_dev);
		}
		else {
			clear_pause_menu(char_buf_dev);
			// Run Pong game
			// ADC
			adc_start(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
			//usleep(10000);
			alt_u32* adc_val_left = &(game.adc_val_left);
			alt_u32* adc_val_right = &(game.adc_val_right);
			float* adc_volt_left = &(game.adc_volt_left);
			float* adc_volt_right = &(game.adc_volt_right);
			// Read joystick values
			// TODO: implement right joystick
			alt_adc_word_read(MODULAR_ADC_0_SAMPLE_STORE_CSR_BASE, adc_val_left, 1);
	//		alt_adc_word_read(MODULAR_ADC_0_SAMPLE_STORE_CSR_BASE + 32 * 1, adc_val_right, 1);
			*adc_volt_left = (float)*adc_val_left * 5.0 / 4096.0;
			// ADC - end
			run_game_tick(pixel_buf_dma_dev, char_buf_dev, 0, &game);
			sprintf(score_str, "%u - %u", game.scores[0], game.scores[1]);
			alt_up_char_buffer_string(char_buf_dev, score_str, 37, 2);
			alt_up_char_buffer_string(char_buf_dev, time_str, 65, 2);
		}
	}
	return 0;
}
