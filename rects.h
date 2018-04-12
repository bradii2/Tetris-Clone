#pragma once
#include <SDL.h>

extern SDL_Rect linesRects[3];
extern SDL_Rect scoreRects[6];
extern SDL_Rect topScoreRects[6];
extern SDL_Rect levelRects[2];
extern SDL_Rect numberRects[2][10]; //[color][digit]

extern SDL_Rect tetScoreRects[7][3]; // the number of pieces that have landed, for each piece

extern SDL_Rect nextBoard[4][4]; //192, 113 is the starting top right corner
extern SDL_Rect gameBoard[10][22];
extern int      gameBoardPlacements[10][22]; // For this, 0 = black, 1-3 = pieceImageRects[num - 1] for color

extern SDL_Rect pieceImageRects[3];

void initRects();
void deinitRects();