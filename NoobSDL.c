/**
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 */


#include <SDL2/SDL.h>
#include "NoobSDL.h"



/* Init Function */

int init_NoobSDL(const size_t window_width, const size_t window_height, 
				 const size_t horizontal_resolution, const size_t vertical_resolution,
				 const char *Title) {
	
	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;
	
	HORIZONTAL_RESOLUTION = horizontal_resolution;
	VERTICAL_RESOLUTION = vertical_resolution;
	
	
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL INIT ERR: %s\n", SDL_GetError());
		
		return 1;
	}
	
	
	// Create main_window
	MAIN_WINDOW = SDL_CreateWindow(Title,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WINDOW_WIDTH,
					WINDOW_HEIGHT,
					0);

	// If failed to create window
	if (!MAIN_WINDOW) {
		printf("SDL CREATE WINDOW ERR: %s\n", SDL_GetError());
		SDL_Quit();
		
		return 1;
	}

	
	// Create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	MAIN_RENDERER = SDL_CreateRenderer(MAIN_WINDOW, -1, render_flags);

	// if failed to create renderer
	if (!MAIN_RENDERER) {
		printf("SDL CREATE RENDERER ERR: %s\n", SDL_GetError());
		SDL_DestroyWindow(MAIN_WINDOW);
		SDL_Quit();
	
		return 1;
	}
	
	
	// create SDL texture
	TEXTURE_BUFFER = SDL_CreateTexture(MAIN_RENDERER, 
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								HORIZONTAL_RESOLUTION,
							  	VERTICAL_RESOLUTION);
	
	SDL_SetTextureBlendMode(TEXTURE_BUFFER, SDL_BLENDMODE_NONE);
	
	SDL_LockTexture(TEXTURE_BUFFER, NULL, (void**)&PIX_BUF, &PITCH);
	
	return 0;
}

/* Quit function, does garbage cleanup */
void quit_NoobSDL() {
	// Cleanup and Exit
	SDL_UnlockTexture(TEXTURE_BUFFER);
	SDL_DestroyTexture(TEXTURE_BUFFER);
	SDL_DestroyRenderer(MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();
}


/* Render funciton, Draws texture buffer data to the window */

void render_NoobSDL() {
	
	// Prevent changes to texture
	SDL_UnlockTexture(TEXTURE_BUFFER);
	
	// write texture to the screen
	SDL_RenderCopy(MAIN_RENDERER, TEXTURE_BUFFER, NULL, NULL);
	
	// update screen
	SDL_RenderPresent(MAIN_RENDERER);
	
	// Allow changes to texture
	SDL_LockTexture(TEXTURE_BUFFER, NULL, (void**)&PIX_BUF, &PITCH);
	
}


/* Used to draw color to pixel at x,y */
void draw_pixel(const size_t x, const size_t y, const unsigned int color) {
	size_t z = HORIZONTAL_RESOLUTION * y + x;
	PIX_BUF[z] = color;
}

/* Draw every pixel to color */
void clear_screen(const unsigned int color) {
	
	size_t z = 0;
	while (z < HORIZONTAL_RESOLUTION * VERTICAL_RESOLUTION) {
		PIX_BUF[z] = color;
		z++;
	}
}


