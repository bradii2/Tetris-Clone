#include "inputHandler.h"
#include <stdio.h>

int *keys = NULL;

void initHandler() {
	keys = new int[(int) Key::KEYS_LENGTH];
	for (int i = 0; i < (int)Key::KEYS_LENGTH; i++) {
		keys[i] = 0;
	}
}
void deinitHandler() {
	if (keys != NULL)
		delete[] keys;
}

int lookup(SDL_Keycode *key) {
	int ret = -1;
	switch (*key) {
	case SDLK_UP:
		ret = (int) Key::UP;
		break;
	case SDLK_DOWN:
		ret = (int) Key::DOWN;
		break;
	case SDLK_LEFT:
		ret = (int) Key::LEFT;
		break;
	case SDLK_RIGHT:
		ret = (int) Key::RIGHT;
		break;
	case SDLK_z:
		ret = (int) Key::Z;
		break;
	case SDLK_x:
		ret = (int) Key::X;
		break;
	case SDLK_RETURN:
	case SDLK_RETURN2:
		ret = (int) Key::ENTER;
		break;
	case SDLK_SPACE:
		ret = (int) Key::SPACE;
		break;
	default:
		printf("Unknown key pressed: %d\n", *key);
	}
	return ret;
}

void keyEventHandle(bool down, SDL_Event *e) {
	SDL_Keycode key = e->key.keysym.sym;
	int num = lookup(&key);
	if (num != -1) {
		keys[num] = down;
	}
}

void handleEvent(SDL_Event *e) {
	if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
		keyEventHandle(e->type == SDL_KEYDOWN ? 1 : 0, e);
	}
}

bool keyPressed(int key) {
	if (key >= (int) Key::KEYS_LENGTH || key < 0)
		return 0;
	else
		return keys[key];
}