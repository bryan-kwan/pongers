
#include <stdio.h>
#include <io.h>
#include <system.h>
#include <unistd.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_avalon_pio_regs.h"

#include "gameutil.h"

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
