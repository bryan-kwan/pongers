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
#include "altera_avalon_pio_regs.h"

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
void update_paddle(Rectangle paddle[], int len, int* user_input);
void update_rect(Rectangle rect[], Rectangle paddles[], int rect_len, int paddle_len, int* scores);
void clear(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, int buffer);
void draw(Rectangle rect[], int len, alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev,int colour, int buffer);
void run_game_tick(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, Rectangle paddles[], int paddle_len, Rectangle balls[], int ball_len, int* scores, int buffer, int* user_input);
void get_user_input(int* user_input);

#endif /* GAMEUTIL_H_ */
