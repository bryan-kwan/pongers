/*
 * gameutil.h
 *
 *  Created on: Jan 26, 2023
 *      Author: bryan
 */

#ifndef GAMEUTIL_H_
#define GAMEUTIL_H_
#include <system.h>
#include <stdio.h>
#include <io.h>
#include <system.h>
#include <unistd.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define PADDLE_SPEED 2
#define BALL_XSPEED 4
#define BALL_YSPEED 2
#define BALL_XDEFAULT SCREEN_WIDTH / 2
#define BALL_YDEFAULT SCREEN_HEIGHT / 2
#define NUM_BALLS 1
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_COLOUR 0xFFFF
#define NUM_PADDLES 2
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 50
#define PADDLE_COLOUR 0xFFFF
#define BACKGROUND_COLOUR 0x0000
#define MAX_SCORE 69

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
struct Game {
	int screen_width;
	int screen_height;
	int scores[2];
	int balls_len;
	int paddles_len;
	Rectangle balls[NUM_BALLS];
	Rectangle paddles[NUM_PADDLES];
	alt_u32 adc_val_left;
	alt_u32 adc_val_right;
	float adc_volt_left;
	float adc_volt_right;
	int user_input[8];
	int time;
};
typedef struct Game Game;

#endif /* GAMEUTIL_H_ */
