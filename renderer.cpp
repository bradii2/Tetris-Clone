#include "renderer.h"
#include "main.h"
#include <stdio.h>
#include "rects.h"
#include "Game.h"

void render(SDL_Window *w) {
	// For rendering - the blitting order is: background, placed pieces, falling, next, and then numbers
	// Here - start surface blitting
	
	//TODO: draw the scores/other boxes, draw the falling tetromino, draw the next tetromino
	SDL_Surface *s = SDL_GetWindowSurface(w);

	// Draw the background
	SDL_BlitScaled(background, NULL, s, NULL);

	// Draw the placed pieces
	for (int x = 0; x < 10; x++) {
		// There are 22 y rects, but the first two should not be shown to the player (0-1 are not shown, 2-21 are)
		for (int y = 2; y < 22; y++) {
			// If there is an empty place, don't draw
			if (gameBoardPlacements[x][y] == 0)
				continue;
			
			// Each number in the placements represent a rect type (color) - 1 through 3
			SDL_BlitScaled(blocks, &pieceImageRects[gameBoardPlacements[x][y] - 1], s, &gameBoard[x][y]);
			if (gameBoardPlacements[x][y] < 1 || gameBoardPlacements[x][y] - 1 > 2)
				printf("Error! Placement: %d\n", gameBoardPlacements[x][y]);
		}
	}

	// Draw the falling piece
	// NOTE: make sure that it doesn't draw if the piece y-val < 2
	for (int i = 0; i < 4; i++) {
		if (falling == NULL)
			break;
		// Check to make sure that whatever you are drawing is in bounds
		if (falling->blocks[i].y < 2 || falling->blocks[i].y > 21)
			continue;

		SDL_BlitScaled(blocks, falling->blockImage, s, &gameBoard[falling->blocks[i].x][falling->blocks[i].y]);
	}

	// TODO: Draw the "next" piece
	for (int i = 0; i < 4; i++) {
		if (next == NULL)
			break;
		// Because of my stupid coding, I have to reset the "next" piece so that if un-centers itself from the origin
		next->fixAroundOrigin();
		SDL_BlitScaled(blocks, next->blockImage, s, &nextBoard[abs(next->blocks[i].x - origin->x) % 4][abs(next->blocks[i].y - origin->y + 1) % 4]);
	}



	// Draw the numbers
	// topScore
	drawNum(topScore, 1, topScoreRects, 6, s);
	// score
	drawNum(score, 1, scoreRects, 6, s);
	// level
	drawNum(level, 1, levelRects, 2, s);
	// lines
	drawNum(lines, 1, linesRects, 3, s);
	// the number of each tetromino:
	for (int i = 0; i < 7; ++i)
		drawNum(tetScore[i], 0, tetScoreRects[i], 3, s);

	// Update the window, so that you can actually see the changes and everything
	SDL_UpdateWindowSurface(w);
}

SDL_Surface* createSurface(Uint32 flags, int w, int h, const SDL_Surface *display) {
	const SDL_PixelFormat &fmt = *(display->format);
	return SDL_CreateRGBSurface(flags, w, h, 
		fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
}

int ipow(int num, int pow) {
	if (pow == 0)
		return 1;
	int ret = 1;
	for (int i = 0; i < pow; i++) {
		ret *= num;
	}
	return ret;
}


void drawDigit(int digit, int color, SDL_Rect *r, SDL_Surface *s) {
	SDL_BlitScaled(numbers, &(numberRects[color][digit]), s, r);
}
/**
 *  rects[count-1] is the lowest digit
 *  rects[0] is the highest digit
 */
void drawNum(int num, int color, SDL_Rect rects[], int count, SDL_Surface *s) {
	int loop = 0;
	while (num != 0 && count > 0) {
		drawDigit(num % 10, color, &rects[--count], s);
		num /= 10;
	}
	while (count > 0) {
		drawDigit(0, color, &rects[--count], s);
	}
}