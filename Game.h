#pragma once

struct SDL_Rect;

enum Types {
	I, J, L, O, Z, S, T, TYPES_COUNT
};


struct Point {
	Point(int x = 0, int y = 0) { this->x = x; this->y = y; }
	int x, y;
};
struct Tetromino {
	int rotation;
	Tetromino(int type); //The type from Types
	void setRot(int rot);
	int getRot();
	void reinit(int type);
	int type;
	Point blocks[4];
	SDL_Rect *blockImage;
	bool collides(int x, int y);
	bool move(int x, int y);
	void fixAroundOrigin();
};

extern Point pieces[7][4][4]; //[type][rotation][point]
// Gravity is measured in frames per grid cell.
// Levels that share a value: 10-12, 13-15, 16-18, 19-28, 29+
extern int gravity[30];

// Not true random, follow the guidelines in main.cpp
int getRand();

void clearLines();
void scoreUp(int num);

void initGame();
void deinitGame();