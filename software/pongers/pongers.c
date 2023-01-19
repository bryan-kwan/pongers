
#include <stdio.h>
#include <io.h>
#include <system.h>
//NEW_SDRAM_CONTROLLER_0_BASE
//ONCHIP_MEMORY2_0_BASE
int main()
{
  printf("Test from Nios II!\n");
  for(int i=0;i<1000;i++){
	  IOWR_16DIRECT(NEW_SDRAM_CONTROLLER_0_BASE, i, (unsigned short)0xdead);
  }

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
