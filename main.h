#pragma once
#define SCALE 2
#define WINDOW_WIDTH 256 * SCALE
#define WINDOW_HEIGHT 240 * SCALE

struct SDL_Surface;
struct Tetromino;
struct Point;

extern int frames;
extern int score;
extern int topScore;
extern int level;
extern int lines;
extern int tetScore[7];

extern Tetromino *falling;
extern Tetromino *next;
extern Point     *origin;

extern bool loss;

extern SDL_Surface *windowSurface;
extern SDL_Surface *background;
extern SDL_Surface *blocks;
extern SDL_Surface *numbers;