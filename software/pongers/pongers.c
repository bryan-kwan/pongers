
#include <stdio.h>
#include <io.h>
#include <system.h>
#include <unistd.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_avalon_pio_regs.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

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
	SW = SW - 128;
	printf("%SW value: d\n", SW);
	if(SW>0) // SW is on
		paddle[0].yspeed = -5;
	else
		paddle[0].yspeed = 5;
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
// "bounces" each object upon collision with screen edges
void update_rect(Rectangle rect[], int len) {
	for(int i = 0; i< len; i++) {
		// Update position
		rect[i].x += rect[i].xspeed;
		rect[i].y += rect[i].yspeed;
		// Check for collisions
		if(rect[i].x + rect[i].width >= SCREEN_WIDTH) {
			rect[i].x = SCREEN_WIDTH - rect[i].width;
			rect[i].xspeed *= -1;
		}
		else if (rect[i].x <= 0) {
			rect[i].x = 0;
			rect[i].xspeed *= -1;
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
// Renders game components on the screen
void draw(Rectangle rect[], int len, alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, int buffer) {
	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev, buffer);
	// Draw each rectangle
	for(int i = 0; i<len; i++) {
		alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev,
				rect[i].x, rect[i].y, rect[i].x + rect[i].width - 1,
				rect[i].y + rect[i].height - 1,
				rect[i].colour, buffer);
	}
}
int main()
{
	printf("Test from Nios II!\n");
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
	int num_balls = 1;
	int BALL_WIDTH = 10;
	int BALL_HEIGHT = 10;
	int BALL_COLOUR = 0xFFFF;
	Rectangle balls[num_balls];
	Rectangle ball = {100, 100, 10, 5, BALL_WIDTH, BALL_HEIGHT, BALL_COLOUR};
	balls[0] = ball;
	int num_paddles = 2;
	int PADDLE_WIDTH = 5;
	int PADDLE_HEIGHT = 50;
	int PADDLE_COLOUR = 0xFFFF;
	Rectangle paddles[num_paddles];
	Rectangle paddle_left = {0, 0, 0, 1, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR};
	Rectangle paddle_right = {SCREEN_WIDTH-PADDLE_WIDTH, 0, 0, 1, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOUR};
	paddles[0] = paddle_left;
	paddles[1] = paddle_right;
	while(1) {
		// Game logic
		update_rect(balls, num_balls);
		update_paddle(paddles, num_paddles);
		// Render the screen
		draw(balls, num_balls, pixel_buf_dma_dev, 1);
		draw(paddles, num_paddles, pixel_buf_dma_dev, 1);
		usleep(10000);// 0.01sec
	}
	return 0;
}
