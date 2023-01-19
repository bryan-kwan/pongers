
#include <stdio.h>
#include <io.h>
#include <system.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"

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

// Updates the position of each Rectangle object
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
	int num_rectangles = 1;
	Rectangle rect[num_rectangles];
	Rectangle ball = {100, 100, 10, 5, 50, 50, 0xFFFF};
	rect[0] = ball;
	while(1) {
		// Game logic
		update_rect(rect, num_rectangles);
		// Render the screen
		draw(rect, num_rectangles, pixel_buf_dma_dev, 1);
		usleep(10000);// 0.01sec
	}
	return 0;
}
