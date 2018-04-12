#pragma once
#include <SDL.h>

void render(SDL_Window *w);

SDL_Surface* createSurface(Uint32 flags, int w, int h, const SDL_Surface* display);
void drawNum(int num, int color, SDL_Rect rects[], int count, SDL_Surface *s);