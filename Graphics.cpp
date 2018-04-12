#include "Graphics.h"
#include <stdio.h>


SDL_Surface* loadImage(char* filepath, SDL_Surface *ws) {
	//filepath: path to the image *.bmp
	//*ws is the Window Surface, used for formatting the image
	SDL_Surface *s = SDL_LoadBMP(filepath);
	SDL_Surface *os = NULL;
	if (s == NULL)
		printf("Unable to load image: %s\n\tSDL error: %s\n", filepath, SDL_GetError());
	else
		os = SDL_ConvertSurface(s, ws->format, NULL); //this makes it so image is not converted every frame
	if (os == NULL)
		printf("Unable to optimize image: %s\n", filepath);
	else
		printf("Loaded image: %s\n", filepath);
	SDL_FreeSurface(s);
	return os;
}