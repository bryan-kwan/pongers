
#include <stdio.h>
#include <io.h>
#include <system.h>
#include <unistd.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_avalon_pio_regs.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define PADDLE_SPEED 2
#define BALL_XSPEED 4
#define BALL_YSPEED 2
#define BALL_XDEFAULT 100
#define BALL_YDEFAULT 100
#define NUM_BALLS 1
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_COLOUR 0xFFFF
#define NUM_PADDLES 2
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 50
#define PADDLE_COLOUR 0xFFFF
#define BACKGROUND_COLOUR 0x0000

struct Rectangle {
	int x;
	int y;
	int xspeed;
	int yspeed;
	int width;
	int height;
	int colour;
};
typedef struct Rectangle Rectangle;

// Updates paddle positions
// There must be at least 2 paddles in the paddle[] array
void update_paddle(Rectangle paddle[], int len) {
	// Adjust speed according to user input
	int SW = IORD(SW_BASE, 0);
	int SW_0 = 0b00000001 & SW;
	int SW_1 = 0b00000010 & SW;
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
void update_rect(Rectangle rect[], Rectangle paddles[], int rect_len, int paddle_len, int* scores) {
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
void clear(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, int buffer) {
	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev, buffer);
}
// Renders game components on the screen
void draw(Rectangle rect[], int len, alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev,int colour, int buffer) {
	// Draw each rectangle
	for(int i = 0; i<len; i++) {
		alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev,
				rect[i].x, rect[i].y, rect[i].x + rect[i].width - 1,
				rect[i].y + rect[i].height - 1,
				colour, buffer);
	}
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

	// Game objects
	int scores[2] = {0, 0};
	Rectangle balls[NUM_BALLS];
	Rectangle ball = {BALL_XDEFAULT, BALL_YDEFAULT, BALL_XSPEED, BALL_YSPEED, BALL_WIDTH, BALL_HEIGHT, BALL_COLOUR};
	balls[0] = ball;
	Rectangle paddles[NUM_PADDLES];
	Rectangle paddle_left = {0, 0, 0, 0, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR};
	Rectangle paddle_right = {SCREEN_WIDTH-PADDLE_WIDTH, 0, 0, 0, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR};
	paddles[0] = paddle_left;
	paddles[1] = paddle_right;
	// Clear screen
	clear(pixel_buf_dma_dev, 1);

	while(1) {
		// Cleanup - clear old objects from screen
		draw(balls, NUM_BALLS, pixel_buf_dma_dev, BACKGROUND_COLOUR,1);
		draw(paddles, NUM_PADDLES, pixel_buf_dma_dev, BACKGROUND_COLOUR, 1);
		// Game logic
		update_rect(balls, paddles, NUM_BALLS, NUM_PADDLES, scores);
		update_paddle(paddles, NUM_PADDLES);
		// Render the screen
		draw(balls, NUM_BALLS, pixel_buf_dma_dev, BALL_COLOUR,1);
		draw(paddles, NUM_PADDLES, pixel_buf_dma_dev, PADDLE_COLOUR, 1);
		usleep(10000);
		printf("Player 1 score: %d, Player 2 score: %d\n", scores[0], scores[1]);
	}
	return 0;
}
