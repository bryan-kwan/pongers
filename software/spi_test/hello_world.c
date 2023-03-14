/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include"alt_types.h"
#include"altera_avalon_spi_regs.h"
#include"altera_avalon_spi.h"
#include"system.h"
#include<stdio.h>
#include<unistd.h>



int main()
{
  printf("Entered Main\n");
  alt_u16 rcvd_M;



  while(1){
	  IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_1_BASE, 1);
	  usleep(75);

	  rcvd_M = IORD_ALTERA_AVALON_SPI_RXDATA(SPI_1_BASE);

	  printf("adc value = %i\n", rcvd_M);

	  usleep(1000);

  }

  return 0;
}
