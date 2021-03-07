/**
 * Header file for NoobSDL
 * 
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 * 
 * Call init with size of window, and resolution.
 * Write pixels with draw_pixel()
 * then call render_NoobSDL()
 * 
 */

#ifndef NOOBSDL
#define NOOBSDL

#ifdef __cplusplus
extern "C" {
#endif


unsigned int * PIX_BUF;
int PITCH;

size_t WINDOW_WIDTH;
size_t WINDOW_HEIGHT;

size_t HORIZONTAL_RESOLUTION;
size_t VERTICAL_RESOLUTION;

SDL_Window * MAIN_WINDOW;
SDL_Renderer * MAIN_RENDERER;

SDL_Texture * TEXTURE_BUFFER;


int init_NoobSDL(const size_t window_width, const size_t window_height, 
				 const size_t horizontal_resolution, const size_t vertical_resolution,
				 const char *Title);

void quit_NoobSDL();

void clear_screen(const unsigned int color);

void draw_pixel(const size_t x, const size_t y, const unsigned int color); // Color : BGRA

void render_NoobSDL();

#ifdef __cplusplus
}
#endif


#endif

