/*
 * gameutil.c
 *
 *  Created on: Jan 26, 2023
 *      Author: bryan
 */

#include "gameutil.h"


// Updates paddle positions
// There must be at least 2 paddles in the paddle[] array
void update_paddle(Rectangle paddle[], int len, float* user_input) {
	// Adjust speed according to user input

	if(*user_input>=2.6){
		paddle[1].yspeed = *user_input;
		paddle[0].yspeed = *user_input;
	}
	else if(*user_input<=2.4){
		paddle[1].yspeed = -(5-*user_input);
		paddle[0].yspeed = -(5-*user_input);
	}
	else{
		paddle[1].yspeed =0;
		paddle[0].yspeed = 0;
	}
	for(int i = 0; i< len; i++) {
			// Update position
			paddle[i].y += paddle[i].yspeed;
			paddle[0].x = 10;
			paddle[1].x = SCREEN_WIDTH - paddle[1].width;
			// Check for collisions
			if (paddle[i].y + paddle[i].height >= SCREEN_HEIGHT) {
				paddle[i].y = SCREEN_HEIGHT - paddle[i].height;
				paddle[i].yspeed = 0;
			}
			else if (paddle[i].y <= 0) {
				paddle[i].y = 0;
				paddle[i].yspeed = 0;
			}

	/*
	int SW_0 = user_input[0];
	int SW_1 = user_input[1];
	if(SW_0) // SW_0 is on (left paddle)
		paddle[0].yspeed = -PADDLE_SPEED;
	else
		paddle[0].yspeed = PADDLE_SPEED;
	if(SW_1) // SW_1 is on (right paddle)
		paddle[1].yspeed = -PADDLE_SPEED;
	else
		paddle[1].yspeed = PADDLE_SPEED;
	// Adjust paddle positions
	for(int i = 0; i< len; i++) {
		// Update position
		paddle[i].y += paddle[i].yspeed;
		paddle[0].x = 0;
		paddle[1].x = SCREEN_WIDTH - paddle[1].width;
		// Check for collisions
		if (paddle[i].y + paddle[i].height >= SCREEN_HEIGHT) {
			paddle[i].y = SCREEN_HEIGHT - paddle[i].height;
			paddle[i].yspeed = 0;
		}
		else if (paddle[i].y <= 0) {
			paddle[i].y = 0;
			paddle[i].yspeed = 0;
			*/
		//}

	}
}
// Updates the position of each Rectangle object
// "bounces" each object upon collision with screen top/bottom edges
// or paddle objects
void update_rect(Rectangle rect[], Rectangle paddles[], int rect_len, int paddle_len, int* scores) {
	for(int i = 0; i< rect_len; i++) {
		// Update position
		rect[i].x += rect[i].xspeed;
		rect[i].y += rect[i].yspeed;
		// Check for collisions
		if(rect[i].x + rect[i].width >= SCREEN_WIDTH || rect[i].x + rect[i].width >= paddles[1].x) {
			// Collision with right paddle
			if(rect[i].y + rect[i].height >= paddles[1].y && rect[i].y <= paddles[1].y + paddles[1].height) {
				rect[i].x = paddles[1].x - rect[i].width;
				rect[i].xspeed*=-1; // Bounce
			}
			else { // Goal - player 1 scored
				// Reset ball position
				rect[i].x = BALL_XDEFAULT;
				rect[i].xspeed*=-1;
				// Add 1 to left player's score
				scores[0] += 1;
			}
		}
		else if (rect[i].x <= 0 || rect[i].x <= paddles[0].width) {
			// Collision with left paddle
			if(rect[i].y + rect[i].height >= paddles[0].y && rect[i].y <= paddles[0].y + paddles[0].height) {
				rect[i].x = paddles[0].x + paddles[0].width;
				rect[i].xspeed*=-1; //Bounce
			}
			else { // Goal - player 2 scored
				// Reset ball position
				rect[i].x = BALL_XDEFAULT;
				rect[i].xspeed*=-1;
				// Add 1 to right player's score
				scores[1] += 1;
			}
		}
		else if (rect[i].y + rect[i].height >= SCREEN_HEIGHT) {
			rect[i].y = SCREEN_HEIGHT - rect[i].height;
			rect[i].yspeed *= -1;
		}
		else if (rect[i].y <= 0) {
			rect[i].y = 0;
			rect[i].yspeed *= -1;
		}
	}
}
void clear(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, int buffer) {
	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev, buffer);
}
// Renders game components on the screen
void draw(Rectangle rect[], int len, alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev,int colour, int buffer) {
	// Draw each rectangle
	for(int i = 0; i<len; i++) {

		// Naive implementation of drawing each pixel - Much slower than draw_box function
		// alt_up_pixel_buffer_dma_draw() draws to the back buffer (buffer=1)
//		for(int x = rect[i].x; x<rect[i].x + rect[i].width; x++) {
//			for(int y = rect[i].y; y<rect[i].y + rect[i].height; y++) {
//				alt_up_pixel_buffer_dma_draw(pixel_buf_dma_dev, colour, x, y);
//			}
//		}

		alt_up_pixel_buffer_dma_draw_box (pixel_buf_dma_dev,
				rect[i].x, rect[i].y, rect[i].x + rect[i].width - 1,
				rect[i].y + rect[i].height - 1,
				colour, buffer);
	}
}

void run_game_tick(alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev, Rectangle paddles[], int paddle_len, Rectangle balls[], int ball_len, int* scores, int buffer, float* user_input) {
	// Wait for screen refresh
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
	while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev));
	//get_user_input(user_input);
	// Cleanup - erase old objects
	draw(balls, NUM_BALLS, pixel_buf_dma_dev, BACKGROUND_COLOUR,buffer);
	draw(paddles, NUM_PADDLES, pixel_buf_dma_dev, BACKGROUND_COLOUR, buffer);
	// Game logic
	update_rect(balls, paddles, NUM_BALLS, NUM_PADDLES, scores);
	update_paddle(paddles, NUM_PADDLES, user_input);
	// Render the screen
	draw(balls, NUM_BALLS, pixel_buf_dma_dev, BALL_COLOUR, buffer);
	draw(paddles, NUM_PADDLES, pixel_buf_dma_dev, PADDLE_COLOUR, buffer);
}
void get_user_input(int* user_input) {
	int SW = IORD(SW_BASE, 0);
	for(int i = 0; i<8; i++) {
		user_input[i] = (0b1 << i) & SW;
	}
}

