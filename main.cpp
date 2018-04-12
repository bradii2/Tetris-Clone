#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "Graphics.h"
#include "Game.h"
#include "renderer.h"
#include "rects.h"
#include "inputHandler.h"

//MS_PER_UPDATE is used for keeping framerate at 60 fps = (1/60)*1000 = 100/6
#define MS_PER_UPDATE 100.0/6.0
#define USED_KEYS 6

int frames = 0; // frame counter

SDL_Window   *window        = NULL;
SDL_Renderer *renderer      = NULL;
SDL_GLContext glContext     = NULL;
SDL_Surface  *windowSurface = NULL;

SDL_Surface *background = NULL;
SDL_Surface *blocks     = NULL;
SDL_Surface *numbers    = NULL;

Tetromino *falling;
Tetromino *next;
Point     *origin; // origin of the falling tetromino - this is pretty much the offset, so that when you rotate or something, the origin helps
				   // the program determine where the pieces of the rotated tetromino would go.

bool loss = false;

int score    = 0;
int topScore = 0;
int level    = 0;
int lines    = 0;
int tetScore[7] = { 0, 0, 0, 0, 0, 0, 0 };

void loadMedia();
void initMedia();

void unloadMedia();
void deinitMain();

int SDL_main(int argc, char* argv[]) {
    //Init SDL and check to make sure it actually worked
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init failed! Error: %s\n", SDL_GetError());
        return -1;
    }

    //Set up the window and everything
    window = SDL_CreateWindow("Tetris2", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    glContext = SDL_GL_CreateContext(window);
    windowSurface = SDL_GetWindowSurface(window);
    if (window == NULL) {
        printf("Could not create window! Error:%s\n", SDL_GetError());
		
        return -1;
    }

    //Start and load parts that are needed to run the game
    loadMedia();
    initMedia();
    initGame();
	initRects();
	initHandler();

    //This is the space for the main game loop and everything
    int currTime, prevTime = 0;
	int currFrames = 0, prevFrames = 0;
    prevTime = SDL_GetTicks();
    double lag = 0;
	
	SDL_Event e;

	SDL_UpdateWindowSurface(window);

	// Only the very very first piece starts at y-val 0, so that the program has time to show it before it drops
	// Tetris piece randomizer - choose number 0-7; if rand = 7 || rand = current falling, then reroll 0-6. no matter what, THIS is the next type
	origin = new Point(5, 1);
	falling = new Tetromino(getRand());
	next = new Tetromino(getRand());
	// Everything needs to start at rotation 2

	// Presses - z, x, up, down, left, right
	bool prevPress[USED_KEYS]    = { 0, 0, 0, 0, 0, 0 };
	bool currPress[USED_KEYS]    = { 0, 0, 0, 0, 0, 0 };
	// pressCounter keeps track of how many frames a button has been held down
	int  pressCounter[USED_KEYS] = { 0, 0, 0, 0, 0, 0 };
	// PressHelper here just keeps the prev and curr arrays in check with the correct buttons
	Key  pressHelper[USED_KEYS]  = { Key::Z, Key::X, Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT };

	// This is a boolean to see if the down button is being pressed, aka does gravity = 1G or 1/2G? (true = 1/2G)
	bool faster = 0;

	bool running = 1;
	while (1) {
		// If the user has lost, then exit the loop you dummy
		if (loss)
			break;

        currTime = SDL_GetTicks();
        int elapsedTime = currTime - prevTime;
        lag += elapsedTime;

		// Handle events like button presses and clicking the close button
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
				break;
			}
			handleEvent(&e);
		}
		if (!running)
			break;

        //Do the game calculations here
        while (lag >= MS_PER_UPDATE) {
			// This gets the current buttons pressed, and also puts the previous frame's buttons into an array.
			// We do this so that you can push a button and have the game detect if it's the first frame it has been pushed,
			// which I then use to determine to either ignore the button or to make it do something
			for (int i = 0; i < USED_KEYS; i++) {
				prevPress[i] = currPress[i];
				currPress[i] = keyPressed((int) pressHelper[i]);
				// Count how many frames a key has been held down, for things like holding left/right to move automatically after a delay
				if (currPress[i])
					pressCounter[i]++;
				else if(pressCounter[i])
					pressCounter[i] = 0;
			}

			// Do stuff with the key presses!
			// 0 = Z, 1 = X
			if (currPress[0] && !prevPress[0]) {
				falling->setRot(falling->getRot() - 1);
			}
			if (currPress[1] && !prevPress[1]) {
				falling->setRot(falling->getRot() + 1);
			}
			// 2-5 = up, down, left, right
			// We only need to check this for the left and right keys, so 4 and 5
			for (int i = 4; i <= 5; i++) {
				if (currPress[i]) {
					// If this is the first frame of it being pressed
					if (!prevPress[i]) {
						i == 5 ? falling->move(1, 0) : falling->move(-1, 0);
					}
					// If it has been pressed before, but it has also been pressed long enough for the delay
					// Delay: 16 frames, then every 6 frames
					else if (pressCounter[i] >= 16) {
						// plus 2, so that pressCounter at 16 is divisible by 6
						if ((pressCounter[i] + 2) % 6 == 0)
							i == 5 ? falling->move(1, 0) : falling->move(-1, 0);
					}
				}
			}
			// Now, we need to check to see if someone pressed the down button
			if (currPress[3])
				// No matter how long they have been holding the down button, it always just sets the gravity to 1/2 of itself.
				faster = true;
			else
				faster = false;
			// If someone pressed up, rotate in one direction. cuz some losers like to play like that
			if (currPress[2] && !prevPress[2]) {
				falling->setRot(falling->getRot() + 1);
			}

			// fall twice as fast with down arrow pressed
			// Don't make the piece fall during the first 1 second
			if ((frames % gravity[level] == 0 && frames > 60) || (faster && (frames % 2 == 0) && frames > 60)) {

				// If the falling tetromino hits something, make it LAND!
				// (everything below this point is code to make the piece land and stay)
				if (!loss && !falling->move(0, 1)) {
					// Place the pieces of the falling into the gameboard, and init a new piece from NEXT
					for (int i = 0; i < 4; i++) {
						Point *t = &falling->blocks[i];
						gameBoardPlacements[t->x][t->y] = (falling->blockImage->x / 7) + 1; //because 0 is empty, every color is +1 from type
						// TODO: make the falling piece = next piece, then assign new next piece
//						printf("Placing %d\tX:%d\tY:%d\n", i, t->x, t->y);
					}
					// Add score for landing the piece
					score += 2 * (level + 1);

					tetScore[falling->type]++;

					// Here, set up the next piece and stuff
					origin->x = 5;
					origin->y = 1;
					falling->reinit(next->type);
					next->reinit(getRand());
					// Now, check to see if we need to clear any lines
					clearLines();
				}
			}
			// TODO: check to see if there is a full row filled, and then clear it and move everything on top down

			// Do we want to do input first, fall second? or fall, then input?
			// input first, so that it's a little more forgiving for when you want to move

			frames++;
			lag -= MS_PER_UPDATE;
        }

        //Render here
		// Renderer TODO: draw the next piece!
        render(window);

        prevTime = currTime;
    }

    //Don't let there be any memory leaks!
    deinitMain();
    return 0;
}

void deinitMain() {
	deinitHandler();
    unloadMedia();
    deinitGame();
	deinitRects();
    SDL_FreeSurface(windowSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	delete origin;
	delete falling;
	delete next;
}

void loadMedia() {
    background = loadImage((char*) "images/Background.bmp", windowSurface);
    blocks     = loadImage((char*) "images/Blocks.bmp",     windowSurface);
    numbers    = loadImage((char*) "images/Numbers.bmp",    windowSurface);
}

void initMedia() {
    SDL_Rect windowRect;
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = WINDOW_WIDTH;
    windowRect.h = WINDOW_HEIGHT;
    SDL_BlitScaled(background, NULL, windowSurface, &windowRect);
    SDL_UpdateWindowSurface(window);
}

void unloadMedia() {
    SDL_FreeSurface(background);
    SDL_FreeSurface(blocks);
    SDL_FreeSurface(numbers);
}