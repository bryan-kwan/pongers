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
#include "alt_types.h"
#include "altera_modular_adc.h"
#include "system.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  printf("Entered Main\n");
  alt_u32 adc_val;
  float adc_volt;

  adc_stop(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
  adc_set_mode_run_once(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
  while(1){
	  adc_start(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
	  usleep(100000);
	  alt_adc_word_read(MODULAR_ADC_0_SAMPLE_STORE_CSR_BASE, &adc_val, MODULAR_ADC_0_SAMPLE_STORE_CSR_CSD_LENGTH);


	  adc_volt = (float)adc_val * 5.0 / 4096.0;

	  printf("adc value = %lu\t adc_voltage = %f\t", adc_val, adc_volt);

  }


  return 0;
}
