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
#include <stdlib.h>
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
#define MAX_SNAKE_LENGTH 100
#define SNAKE_PIXEL_SIZE 5
#define SNAKE_COLOUR 0x0FF0
#define FRUIT_COLOUR 0xF000
#define JOYSTICK_LEFT 0
#define JOYSTICK_RIGHT 1
#define JOYSTICK_UP 2
#define JOYSTICK_DOWN 3
#define SNAKE_DEFAULT_X SCREEN_WIDTH / 2
#define SNAKE_DEFAULT_Y SCREEN_HEIGHT / 2

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
struct SnakeGame {
	Rectangle snake[MAX_SNAKE_LENGTH];
	int snake_size;
	Rectangle fruit;
	int score;
	alt_u32 adc_val_horz;
	alt_u32 adc_val_vert;
	int user_input[8];
	int current_joystick_direction;
	int previous_joystick_direction;
	int time;
	int game_over_flag;
}; typedef struct SnakeGame SnakeGame;

#endif /* GAMEUTIL_H_ */
