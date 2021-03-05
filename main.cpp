#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include <SDL2/SDL.h>

#include "vec.h"
#include "geom.h"
#include "cube.h"
#include "NoobSDL.h"

#include "OpenSimplexNoise.h"





// - - - - //
// Global  //
// - - - - //
struct vec_t camera_pos = {0.0,0.0,0.0};
struct vec_t camera_look = {0.0, 0.0, 1.0};
struct vec_t camera_up = {0.0, 1.0, 0.0};
struct vec_t camera_right = {1.0, 0.0, 0.0};

float hFOV = M_PI / 2.0f;
float vFOV = M_PI / 2.0f;

unsigned long hRes = 128;
unsigned long vRes = 128;

float MOVE_SPEED = 0.2f;
float LOOK_SPEED = (M_PI * 0.025f);




// Multi Thread stuff
pthread_t * workers;
unsigned long THREAD_COUNT = 6;
#define THREAD_STEP (VERTICAL_RESOLUTION / THREAD_COUNT)

struct render_t {
	unsigned long id;
	struct obj_t * BANG;
};

/* Used for multithreaded rendering */
void *partial_render(void *varg) {
	
	struct render_t * carg = (struct render_t *) varg;
	
	unsigned long starty = THREAD_STEP * (carg->id);
	unsigned long endy = THREAD_STEP + starty;
	
	for (unsigned long y = starty; y < endy; y++) {
		for (unsigned long x = 0; x < HORIZONTAL_RESOLUTION; x++) {
			
			float yaw = ((float) x - (HORIZONTAL_RESOLUTION - 1) * 0.5f) * (hFOV / HORIZONTAL_RESOLUTION);
			float pitch = ((float) y - (VERTICAL_RESOLUTION - 1) * 0.5f) * (vFOV / VERTICAL_RESOLUTION);

			struct vec_t axis = vec_normalize(vec_add(vec_scale(camera_up, yaw), vec_scale(camera_right, pitch)));

			float ang = sqrt(yaw*yaw + pitch*pitch);

			struct vec_t direction = vec_normalize(vec_rotate(camera_look, axis, ang));

			float dist = 1000.0f;
			unsigned int color = 0;
			
			cals_intersect_ray_obj((struct ray_t) {camera_pos, direction}, carg->BANG, &dist, &color);
			
			draw_pixel(x, y, color);
			
		}
	}
	
	pthread_exit(NULL);
}


void count_tri(struct obj_t obj, unsigned long * sum) {
	
	for(unsigned long i = 0; i < obj.children_count; i++) {
		count_tri(obj.children[i], sum);
	}
	*sum += obj.content_count;
}



int main(void) {
	
	srand(time(NULL));
	
	printf("Hello, World!\n");
	
	
	// - - - - - - //
	// World Data  //
	// - - - - - - //
	
	// Random World Values data stuff
	OpenSimplexNoise::Noise N = OpenSimplexNoise::Noise(time(NULL));
	struct vec_t scalar = {10.0, 10.0, 10.0};
	
	
	struct world_t WORLD = make_world(
		(struct vec_t){-25.0, -25.0, -25.0}, 		// MIN
		(struct vec_t){25.0, 25.0, 25.0}, 	// MAX
		6, 0.0f);	// Depth, Threshold
	for(unsigned long k = 0; k < WORLD.size; k++) {
		for(unsigned long j = 0; j < WORLD.size; j++) {
			for(unsigned long i = 0; i < WORLD.size; i++) {
				
				// Determine normalized xyz
				float x = ((float)i / (float)WORLD.size);
				float y = ((float)j / (float)WORLD.size);
				float z = ((float)k / (float)WORLD.size);
				
				WORLD.map[i][j][k] = N.eval(x * scalar.x, y * scalar.y, z * scalar.z);
				//WORLD.map[i][j][k] = 0.0f;
				
			}
		}
	}
	
	struct obj_t BOOM = make_obj(WORLD.min, WORLD.max, WORLD.map, WORLD.T, WORLD.depth, 0, 0, 0);
	unsigned long tri_count = 0;
	count_tri(BOOM, &tri_count);
	printf("Tri count: %ld\n", tri_count);
	free_obj(BOOM);
	
	
	
	
	
	
	if (init_NoobSDL(512, 512, hRes, vRes, "Demo Window")) {
		// if init has an error, exit program.
		return 1;
	}
	
	
	// - - - - - //
	// Threading //
	// - - - - - //
	workers = (pthread_t *) malloc(sizeof(pthread_t) * THREAD_COUNT);
	struct render_t * render_args = (struct render_t *) malloc(sizeof(struct render_t) * THREAD_COUNT);
	
	
	char loop = 1;
	
	char look_up = 0;
	char look_down = 0;
	char look_right = 0;
	char look_left = 0;
	char roll_right = 0;
	char roll_left = 0;
	
	char move_up = 0;
	char move_down = 0;
	char move_forward = 0;
	char move_back = 0;
	char move_right = 0;
	char move_left = 0;
	
	
	// Main Loop
	while(loop) {
		
		// Basic Event Handling
		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {
			switch (evt.type) {
				case SDL_QUIT:
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch (evt.key.keysym.sym) {
						case SDLK_LEFT:
							look_left = 1;
							break;
						case SDLK_RIGHT:
							look_right = 1;
							break;
						case SDLK_UP:
							look_up = 1;
							break;
						case SDLK_DOWN:
							look_down = 1;
							break;
						case SDLK_e:
							roll_right = 1;
							break;
						case SDLK_q:
							roll_left = 1;
							break;
						case SDLK_w:
							move_forward = 1;
							break;
						case SDLK_a:
							move_left = 1;
							break;
						case SDLK_s:
							move_back = 1;
							break;
						case SDLK_d:
							move_right = 1;
							break;
						case SDLK_SPACE:
							move_up = 1;
							break;
						case SDLK_LSHIFT:
							move_down = 1;
							break;
						
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					switch (evt.key.keysym.sym) {
						case SDLK_LEFT:
							look_left = 0;
							break;
						case SDLK_RIGHT:
							look_right = 0;
							break;
						case SDLK_UP:
							look_up = 0;
							break;
						case SDLK_DOWN:
							look_down = 0;
							break;
						case SDLK_e:
							roll_right = 0;
							break;
						case SDLK_q:
							roll_left = 0;
							break;
						case SDLK_w:
							move_forward = 0;
							break;
						case SDLK_a:
							move_left = 0;
							break;
						case SDLK_s:
							move_back = 0;
							break;
						case SDLK_d:
							move_right = 0;
							break;
						case SDLK_SPACE:
							move_up = 0;
							break;
						case SDLK_LSHIFT:
							move_down = 0;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		
		// Looking around
		struct vec_t axis = (struct vec_t) {0,0,0};
		if (look_up) {
			axis = vec_sub(axis, camera_right);
		}
		if (look_down) {
			axis = vec_add(axis, camera_right);
		}
		if (look_left) {
			axis = vec_sub(axis, camera_up);
		}
		if (look_right) {
			axis = vec_add(axis, camera_up);
		}
		if (roll_right) {
			axis = vec_sub(axis, camera_look);
		}
		if (roll_left) {
			axis = vec_add(axis, camera_look);
		}
		if (vec_mag(axis) > 0.001f) {
			axis = vec_normalize(axis);
			camera_look = vec_rotate(camera_look, axis, LOOK_SPEED);
			camera_up = vec_rotate(camera_up, axis, LOOK_SPEED);
			camera_right = vec_rotate(camera_right, axis, LOOK_SPEED);
		}
		
		// Moving around
		struct vec_t move_step = (struct vec_t) {0,0,0};
		if (move_forward) {
			move_step = vec_add(move_step, camera_look);
		}
		if (move_back) {
			move_step = vec_sub(move_step, camera_look);
		}
		if (move_right) {
			move_step = vec_add(move_step, camera_right);
		}
		if (move_left) {
			move_step = vec_sub(move_step, camera_right);
		}
		if (move_up) {
			move_step = vec_add(move_step, camera_up);
		}
		if (move_down) {
			move_step = vec_sub(move_step, camera_up);
		}
		if (vec_mag(move_step) > 0.001f) {
			camera_pos = vec_add(camera_pos, vec_scale(vec_normalize(move_step), MOVE_SPEED));
		}
		
		
		// Screen Rendering
		
		clear_screen(0xFF000000);
		
		struct obj_t BANG = make_obj(WORLD.min, WORLD.max, WORLD.map, WORLD.T, WORLD.depth, 0, 0, 0);
		
		// MULTITHREAD RENDERING
		unsigned long i;
		for (i = 0; i < THREAD_COUNT; i++) {
			render_args[i] = (struct render_t) {i, &BANG};
			pthread_create(workers + i, NULL, partial_render, render_args + i);
		}
		
		for (i = 0; i < THREAD_COUNT; i++) {
			pthread_join(workers[i], NULL);
		}
		
		render_NoobSDL();
		
		// Free Bang
		free_obj(BANG);
		
	}
	
	
	// Cleanup threading
	free(render_args);
	free(workers);
	
	// Free World
	free_world(WORLD);
	
	quit_NoobSDL();
	
	return 0;
}