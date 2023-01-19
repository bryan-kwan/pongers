
#include <stdio.h>
#include <io.h>

int main()
{
  int MEM_START = 0x04000000;
  printf("Test from Nios II!\n");
  for(int i=0;i<100;i++){
	  printf("Testing from Nios II!\n");
	  IOWR_16DIRECT(MEM_START, i, (unsigned short)0xdead);
	  printf("Hello from Nios II!\n");
  }

  return 0;
}
