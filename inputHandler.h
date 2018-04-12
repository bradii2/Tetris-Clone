#pragma once
#include <SDL.h>

enum class Key {
	UP, DOWN, LEFT, RIGHT, Z, X, ENTER, SPACE, KEYS_LENGTH
};

void initHandler();
void deinitHandler();
bool keyPressed(int key);

void handleEvent(SDL_Event *e);