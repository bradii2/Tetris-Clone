#include "Game.h"
#include <stdio.h>
#include "main.h"
#include <SDL.h>
#include "rects.h"
#include <time.h>
#include <stdlib.h>

Point pieces[TYPES_COUNT][4][4]; //[type][rotation][point]
int gravity[30] = { 48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 };

void initGame() {
	// Init stuff for the random number generator
	srand(time(NULL));

	//Initialize I
	// OLD
/*	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++){
			pieces[I][j * 2][i] = Point(i, 1); //j is 180 rotation, so rot 0 = rot 2
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 3; j += 2) {
			pieces[I][j][i] = Point(1, i); //Vertical I
		}
	}
*/
	// NEW
	pieces[I][0][0] = Point(0, 1); pieces[I][0][1] = Point(1, 1); pieces[I][0][2] = Point(2, 1); pieces[I][0][3] = Point(3, 1);
	pieces[I][1][0] = Point(1, 0); pieces[I][1][1] = Point(1, 1); pieces[I][1][2] = Point(1, 2); pieces[I][1][3] = Point(1, 3);
	pieces[I][2][0] = Point(0, 1); pieces[I][2][1] = Point(1, 1); pieces[I][2][2] = Point(2, 1); pieces[I][2][3] = Point(3, 1);
	pieces[I][3][0] = Point(1, 0); pieces[I][3][1] = Point(1, 1); pieces[I][3][2] = Point(1, 2); pieces[I][3][3] = Point(1, 3);



	//Initialize J
	// OLD
/*
	for (int i = 0; i < 3; i++) {
		pieces[J][0][i] = Point(i, 1);
		pieces[J][1][i] = Point(1, i);
		pieces[J][2][i] = Point(i, 1);
		pieces[J][3][i] = Point(1, i);
	}
	pieces[J][0][3] = Point(2, 0);
	pieces[J][1][3] = Point(2, 2);
	pieces[J][2][3] = Point(2, 2);
	pieces[J][3][3] = Point(0, 0);
*/
	// NEW
	pieces[J][0][0] = Point(0, 1); pieces[J][0][1] = Point(1, 1); pieces[J][0][2] = Point(2, 1); pieces[J][0][3] = Point(2, 0);
	pieces[J][1][0] = Point(1, 0); pieces[J][1][1] = Point(1, 1); pieces[J][1][2] = Point(1, 2); pieces[J][1][3] = Point(2, 2);
	pieces[J][2][0] = Point(0, 1); pieces[J][2][1] = Point(1, 1); pieces[J][2][2] = Point(2, 1); pieces[J][2][3] = Point(0, 2);
	pieces[J][3][0] = Point(1, 0); pieces[J][3][1] = Point(1, 1); pieces[J][3][2] = Point(1, 2); pieces[J][3][3] = Point(0, 0);

	//Initialize L
	// OLD
/*/
	for (int i = 0; i < 3; i++) {
		pieces[L][0][i] = Point(i, 1);
		pieces[L][1][i] = Point(1, i);
		pieces[L][2][i] = Point(i, 1);
		pieces[L][3][i] = Point(1, i);
	}
	pieces[L][0][3] = Point(2, 2);
	pieces[L][1][3] = Point(0, 2);
	pieces[L][2][3] = Point(0, 0);
	pieces[L][3][3] = Point(2, 0);
*/
	// NEW
	pieces[L][0][0] = Point(0, 1); pieces[L][0][1] = Point(1, 1); pieces[L][0][2] = Point(2, 1); pieces[L][0][3] = Point(2, 2);
	pieces[L][1][0] = Point(1, 0); pieces[L][1][1] = Point(1, 1); pieces[L][1][2] = Point(1, 2); pieces[L][1][3] = Point(0, 2);
	pieces[L][2][0] = Point(0, 1); pieces[L][2][1] = Point(1, 1); pieces[L][2][2] = Point(2, 1); pieces[L][2][3] = Point(0, 0);
	pieces[L][3][0] = Point(1, 0); pieces[L][3][1] = Point(1, 1); pieces[L][3][2] = Point(1, 2); pieces[L][3][3] = Point(2, 0);


	//Initialize O
	for (int i = 0; i < 4; i++) {
		pieces[O][i][0] = Point(0, 0);
		pieces[O][i][1] = Point(0, 1);
		pieces[O][i][2] = Point(1, 0);
		pieces[O][i][3] = Point(1, 1);
	}

	//Initialize S
	pieces[S][0][0] = Point(1, 0); pieces[S][0][1] = Point(2, 0); pieces[S][0][2] = Point(0, 1); pieces[S][0][3] = Point(1, 1);
	pieces[S][1][0] = Point(0, 0); pieces[S][1][1] = Point(0, 1); pieces[S][1][2] = Point(1, 1); pieces[S][1][3] = Point(1, 2);
	pieces[S][2][0] = Point(1, 0); pieces[S][2][1] = Point(2, 0); pieces[S][2][2] = Point(0, 1); pieces[S][2][3] = Point(1, 1);
	pieces[S][3][0] = Point(0, 0); pieces[S][3][1] = Point(0, 1); pieces[S][3][2] = Point(1, 1); pieces[S][3][3] = Point(1, 2);

	//Initialize T
	pieces[T][0][0] = Point(1, 0); pieces[T][0][1] = Point(0, 1); pieces[T][0][2] = Point(1, 1); pieces[T][0][3] = Point(2, 1);
	pieces[T][3][0] = Point(1, 0); pieces[T][3][1] = Point(0, 1); pieces[T][3][2] = Point(1, 1); pieces[T][3][3] = Point(1, 2);
	pieces[T][2][0] = Point(0, 1); pieces[T][2][1] = Point(1, 1); pieces[T][2][2] = Point(2, 1); pieces[T][2][3] = Point(1, 2);
	pieces[T][1][0] = Point(1, 0); pieces[T][1][1] = Point(1, 1); pieces[T][1][2] = Point(2, 1); pieces[T][1][3] = Point(1, 2);

	//Initialize Z
	pieces[Z][0][0] = Point(0, 0); pieces[Z][0][1] = Point(1, 0); pieces[Z][0][2] = Point(1, 1); pieces[Z][0][3] = Point(2, 1);
	pieces[Z][1][0] = Point(1, 0); pieces[Z][1][1] = Point(0, 1); pieces[Z][1][2] = Point(1, 1); pieces[Z][1][3] = Point(0, 2);
	pieces[Z][2][0] = Point(0, 0); pieces[Z][2][1] = Point(1, 0); pieces[Z][2][2] = Point(1, 1); pieces[Z][2][3] = Point(2, 1);
	pieces[Z][3][0] = Point(1, 0); pieces[Z][3][1] = Point(0, 1); pieces[Z][3][2] = Point(1, 1); pieces[Z][3][3] = Point(0, 2);
}
void deinitGame() {

}

Tetromino::Tetromino(int type) {
	this->reinit(type);
}
void Tetromino::reinit(int type) {
	this->type = type;
	// Make the rotation and piece the correct one
	// S and Z need to be one lower?
	// If the block is S or Z, set the origin.y += 1;
	this->setRot(2);
	// Depending on the type, choose the correct SDL_Rect
	SDL_Rect *t = this->blockImage;

	// This switch statement chooses the correct image to show for each piece
	switch (type) {
	case T: case I: case O:
		t = &pieceImageRects[0];
		break;
	case J: case S:
		t = &pieceImageRects[1];
		break;
	default:
		t = &pieceImageRects[2];
		break;
	}
	if (type == S || type == Z || type == L)
		origin->y += 1;
	this->blockImage = t;

	this->fixAroundOrigin();
}

// This function assumes that collision detection has already happened, so it's safe to rotate.
// This rotates it and then checks for collision. if it collides, then un-rotate it.
void Tetromino::setRot(int rot) {
	int oldRot = rotation;
	if (rot == -1)
		rot = 3;
	rotation = rot % 4;
	this->fixAroundOrigin();
	if (this->collides(0, 0)) {
		rotation = oldRot;
		this->fixAroundOrigin();
		puts("Collide!");
	}
}
int Tetromino::getRot() {
	return this->rotation;
}

// The x, y int values are the offset - so if the piece were to move this many pixels, would it collide with anything?
bool Tetromino::collides(int x, int y) {
	for (int i = 0; i < 4; i++) {
		Point t = this->blocks[i];
		// If the piece hits an edge, it counts as colliding
		// Doing this check first also stops an out-of-bounds error in the next if statement
		if (t.x + x >= 10 || t.y + y >= 22 || t.x + x < 0 || t.y + y < 0)
			return 1;

		if (gameBoardPlacements[t.x + x][t.y + y] != 0)
			return 1;
	}
	return 0;
}
// A helper class, so that when the origin moves, the pieces arrange themselves to move to their correct positions.
// Maybe use this for rotation, in that you can rotate a piece just by changing the rotation value and then calling this function.
void Tetromino::fixAroundOrigin() {
	for (int i = 0; i < 4; ++i) {
		this->blocks[i].x = pieces[type][rotation][i].x + origin->x;
		this->blocks[i].y = pieces[type][rotation][i].y + origin->y;
	}
}

// Move returns true if successful, false if there is a collision
bool Tetromino::move(int x, int y) {
	if (this->collides(x, y)) {
		return false;
	}
	origin->x += x;
	origin->y += y;
	this->fixAroundOrigin();
	return true;
}

int getRand() {
	// Truly random for the first pieces
	if (falling == NULL)
		return rand() % 7; 
	
	int num1 = rand() % 8; // Random number 0-7

	// If you roll a 7 or the current type, roll again, but 0-6
	if (num1 == 7 || num1 == falling->type) {
		// Even if this is the same TYPE, at this point, it's going to stay that way
		num1 = rand() % 7;
	}
	return num1;
}

void clearLines() {
	// Scan to see if there are any 0's in a line. If there are not, clear it, and start scanning again from the same line (i++, continue;)
	// Starts at the bottom and works its way up
	int linesCleared = 0;
	for (int i = 21; i >= 0; i--) {
		// i is the row. Now scan along the row to add up any non-0, and if non-0 count == 10, then it's a full line to clear
		int count = 0;

		for (int j = 0; j < 10; j++) {
			if (gameBoardPlacements[j][i] != 0)
				count++;
		}
		
		// Now, if we have found a line to clear...
		if (count >= 10) {
			lines++;
			linesCleared++;
			// for every line above this one, copy the data and move it down
			for (int j = i; j >= 0; j--) {
				for (int k = 0; k < 10; k++) {
					if (j == 0)
						gameBoardPlacements[k][j] = 0;
					else
						// Every point is now the point above it
						gameBoardPlacements[k][j] = gameBoardPlacements[k][j - 1];
				}
			}
			i++;
		}
	}
	scoreUp(linesCleared);
	// Now, check the lines # and see if level should be updated
	level = (lines / 10) % 30;
	// Finally, check to see if the user has lost. this is determined if there is ANYTHING in the y-level 1
	for (int i = 0; i < 10; i++) {
		if (gameBoardPlacements[i][1] != 0) {
			loss = true;
			break;
		}
	}
}

void scoreUp(int num) {
	level++;
	switch (num) {
	case 1:
		score += 100 * level;
		break;
	case 2:
		score += 300 * level;
		break;
	case 3:
		score += 500 * level;
		break;
	case 4:
		score += 800 * level;
		break;
	}
	level--;
}