
#include <stdio.h>
#include <io.h>
#include <system.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
//NEW_SDRAM_CONTROLLER_0_BASE
//ONCHIP_MEMORY2_0_BASE
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

	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev, 0);
	usleep(1000000);// 1sec

	// Draw
	alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev, 50, 50, 100, 100, 0xF800, 0);
	alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev, 100, 100, 150, 150, 0x07E0, 0);
	alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev, 150, 150, 200, 200, 0x001F, 0);
	alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev, 0, 0, 50, 50, 0xFFFF, 0);
	return 0;
}

// Below is some test code that is supposed to make a line move on the screen
//#define SDRAM_0_BASE NEW_SDRAM_CONTROLLER_0_BASE
//#define SDRAM_VIDEO_OFFSET 0
//#define FRAME_WIDTH 640
//#define FRAME_HEIGHT 480
//#define COLOR_BLACK 0x00
//#define COLOR_WHITE 0xFF
//int main()
//{
//	int row = 0;
//	int col = 0;
//	// Clear the screen
//	for (row = 0; row < FRAME_HEIGHT; row++){
//		for (col = 0; col < FRAME_WIDTH; col = col + 4){
//			IOWR_32DIRECT(NEW_SDRAM_CONTROLLER_0_BASE, SDRAM_VIDEO_OFFSET + row * FRAME_WIDTH + col, COLOR_BLACK);
//		}
//	}
////	ALT_CI_CI_FRAME_DONE_0; // Custom command to trigger frame swap
//	// Draw pattern
//	unsigned int position = 0;
//	while (1)
//	{
//	for (row = 0; row < FRAME_HEIGHT; row++)
//	{
//		// Clear previous position of line
//		if (position == 0) {
//			IOWR_8DIRECT(SDRAM_0_BASE, SDRAM_VIDEO_OFFSET + row *
//			FRAME_WIDTH + FRAME_WIDTH - 8, COLOR_BLACK);
//		} else {
//			IOWR_8DIRECT(SDRAM_0_BASE, SDRAM_VIDEO_OFFSET + row *
//			FRAME_WIDTH + position - 8, COLOR_BLACK);
//		}
//		// Draw new line
//		IOWR_8DIRECT(SDRAM_0_BASE, SDRAM_VIDEO_OFFSET + row * FRAME_WIDTH
//		+ position, COLOR_WHITE);
//	}
//	position = (position + 8) % 640;
////	ALT_CI_CI_FRAME_DONE_0; // Trigger frame swap
//	}
//	return 0;
//}
