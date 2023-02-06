
#include <stdio.h>
#include <io.h>
#include <system.h>
#include <unistd.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "altera_modular_adc.h"

#include "gameutil.h"

#define SDRAM_COLOUR_BITS 16


int main()
{
	printf("Entered Main\n");
	alt_u32 adc_val;


	adc_stop(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
	adc_set_mode_run_once(MODULAR_ADC_0_SEQUENCER_CSR_BASE);

	int time; // Game timer measured in s
	// Have to set up these pointers to open the device
	// Reference : https://faculty-web.msoe.edu/johnsontimoj/EE3921/files3921/nios_pixel_sw.pdf
	alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev;
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev(VIDEO_PIXEL_BUFFER_DMA_0_NAME);
	// Check for error
	if ( pixel_buf_dma_dev == NULL)
		printf ("Error: could not open pixel buffer device \n");
	else
		printf ("Opened pixel buffer device \n");

	// Alarm setup - executes the callback function periodically (every second)
	alt_u32 alarm_callback(void *context) {
		time += 1;
		return alt_ticks_per_second();
	}
	static alt_alarm alarm;
	// Setup alarm to call the callback function every N_TICKS
	if (alt_alarm_start(&alarm, alt_ticks_per_second(), alarm_callback, NULL) < 0){
		printf ("No System Clock Available\n");
	}


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

	float* user_input;
	float adc_volt;
	// Clear screen
	clear(pixel_buf_dma_dev, 0); // Current screen


	while(1) {
		alt_adc_word_read(MODULAR_ADC_0_SAMPLE_STORE_CSR_BASE, &adc_val, MODULAR_ADC_0_SAMPLE_STORE_CSR_CSD_LENGTH);
		adc_volt = (float)adc_val * 5.0 / 4096.0;
		user_input = &adc_volt;
		run_game_tick(pixel_buf_dma_dev, paddles, NUM_PADDLES, balls, NUM_BALLS, scores, 0, user_input);
		adc_start(MODULAR_ADC_0_SEQUENCER_CSR_BASE);
		usleep(10000);




		//printf("adc value = %lu\t adc_voltage = %f\t", adc_val, adc_volt);
	}
	return 0;
}
