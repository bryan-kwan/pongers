
#include <stdio.h>
#include <io.h>
#include <system.h>
//NEW_SDRAM_CONTROLLER_0_BASE
int main()
{
  printf("Test from Nios II!\n");
  for(int i=0;i<1000;i++){
	  IOWR_16DIRECT(ONCHIP_MEMORY2_0_BASE, i, (unsigned short)0xdead);
  }

  return 0;
}
