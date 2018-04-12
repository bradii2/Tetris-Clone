#include "rects.h"
#include "Game.h"
#include "main.h"
#include <stdio.h>

SDL_Rect linesRects[3];
SDL_Rect scoreRects[6];
SDL_Rect topScoreRects[6];
SDL_Rect levelRects[2];
SDL_Rect numberRects[2][10]; //2 colors, 10 digits
SDL_Rect tetScoreRects[7][3];

SDL_Rect nextBoard[4][4];
SDL_Rect gameBoard[10][22];
int      gameBoardPlacements[10][22];

SDL_Rect pieceImageRects[3];

//this is for initRects() working with enum Types
int typesHelper[] = {T, J, Z, O, S, L, I};

int width = 10, height = 20 + 2; //w and h of the game board (the top 2 of height are not visible to the player)

//This is for setting up rects where there is a one-pixel space between each one
void initRectsArr(SDL_Rect* r, int xStart, int yStart, int count, int scale) {
	for (int i = 0; i < count; i++) {
		SDL_Rect *t = &r[i];
		t->w = 7 * scale;
		t->h = 7 * scale;
		t->x = (xStart * scale) + ((t->w + (1 * scale)) * i); // start + (width + 1 space between)(position)
		t->y =  yStart * scale;
	}
}

//Same as initRectsArr, but with no spaces between the rects
void initRectsArr2(SDL_Rect *r, int xStart, int yStart, int count, int scale) {
	for (int i = 0; i < count; i++) {
		SDL_Rect *t = &r[i]; //t is the rect we are now working with
		t->w = 7 * scale;
		t->h = 7 * scale;
		t->x = (xStart * scale) + (t->w * i);
		t->y =  yStart * scale;
	}
}

// gameBoard reacts must be initialized differently than the others, because of the [x][y] pattern (not [y][x]), and so it's init'd by column (not row)
void initGameboardRects() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			// t is the current rect
			SDL_Rect *t = &(gameBoard[x][y]);
			// The starting rect is at 96, 48 (at the top-left hand corner)
			// CORRECTION: that is the start of the VISIBLE rectangles!
			// there are 2 additional rows above what is visible to the player, which are not rendered
			// -> start at 96, 32
			t->w = 7 * SCALE;
			t->h = 7 * SCALE;
			t->x = (96 * SCALE) + ((t->w + SCALE) * x);
			t->y = (32 * SCALE) + ((t->h + SCALE) * y);
		}
	}
}
void initNextboardRects() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			// t is the current rect
			SDL_Rect *t = &(nextBoard[x][y]);
			// The starting rect is at 192, 113 (at the top-left hand corner)
			t->w = 7 * SCALE;
			t->h = 7 * SCALE;
			t->x = (192 * SCALE) + ((t->w + SCALE) * x);
			t->y = (113 * SCALE) + ((t->h + SCALE) * y);
		}
	}
	
}

void initRects() {
	//Init number rects
	for (int i = 0; i < 2; i++) initRectsArr2(numberRects[i], 0, i * 7, 10, 1);

	//Init lines
	initRectsArr(linesRects, 152, 24, 3, SCALE);
	//Init score 192 64
	initRectsArr(scoreRects, 192, 64, 6, SCALE);
	//Init top score
	initRectsArr(topScoreRects, 192, 40, 6, SCALE);
	//Init levels
	initRectsArr(levelRects, 208, 168, 2, SCALE);

	//Init the number of each piece that has fallen
	for (int i = 0; i < 7; i++)
		initRectsArr(tetScoreRects[typesHelper[i]], 48, 96 + (16 * i), 3, SCALE);

	initGameboardRects();

	// Init the rects for the individual blocks of a tetromino, for the image (each rect is around one of the pieces for colors)
	// For now, we're only using the colors for level 1 (there are way too many colors for me to do all of them)
	for (int i = 0; i < 3; i++) {
		pieceImageRects[i].x = 7 * i;
		pieceImageRects[i].y = 0;
		pieceImageRects[i].w = 7;
		pieceImageRects[i].h = 7;
	}

	// Make gameBoardPlacements all 0's
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 22; ++j) {
			gameBoardPlacements[i][j] = 0;
		}
	}

	// TODO: find out how to show the next piece nicely
	initNextboardRects();
	
}
void deinitRects() {
	
}