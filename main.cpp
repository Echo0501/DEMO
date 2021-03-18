/**
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 */

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

unsigned long hRes = 256;
unsigned long vRes = 256;

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

// Counts the number of triangles in an obj_t
void count_tri(struct obj_t * OBJ, unsigned long * sum) {
	
	if (OBJ == NULL) return;
	
	for(unsigned long i = 0; i < OBJ->children_count; i++) {
		count_tri(OBJ->children[i], sum);
	}
	*sum += OBJ->content_count;
}



int main(void) {
	
	printf("Hello, World!\n");
	
	
	// - - - - - - //
	// World Data  //
	// - - - - - - //
	
	// OpenSimplexNoise, for noisey world
	// This is the only cpp I've used, and only reason for me making main a .cpp file
	OpenSimplexNoise::Noise N = OpenSimplexNoise::Noise(time(NULL));
	struct vec_t scalar = {5.0, 5.0, 5.0};
	
	// Make the world!
	struct world_t WORLD = make_world(
		(struct vec_t){-10.0, -10.0, -10.0}, 		// MIN
		(struct vec_t){10.0, 10.0, 10.0}, 	// MAX
		6, 0.0f);	// Depth, Threshold
	
	// Fill the world!
	for(unsigned long k = 0; k < WORLD.size; k++) {
		for(unsigned long j = 0; j < WORLD.size; j++) {
			for(unsigned long i = 0; i < WORLD.size; i++) {
				
				// Determine xyz world coords from indexies
				float x = ((float)i / (float)WORLD.size);
				float y = ((float)j / (float)WORLD.size);
				float z = ((float)k / (float)WORLD.size);
				
				WORLD.map[i][j][k] = N.eval(x * scalar.x, y * scalar.y, z * scalar.z);
				//WORLD.map[i][j][k] = 0.0f;
				
			}
		}
	}
	
	// Make obj_t octtree to contain tiangle mesh of the world
	// Can be updated for every frame, although it only needs to be updated
	// when changes happen
	struct obj_t * BOOM = make_obj(WORLD.min, WORLD.max, WORLD.map, WORLD.T, WORLD.depth, 0, 0, 0);
	BOOM = prune_obj(BOOM);
	
	unsigned long tri_count = 0;
	count_tri(BOOM, &tri_count);
	printf("Tri count: %ld\n", tri_count);
	//free_obj(BOOM);
	
	
	// Make window
	if (init_NoobSDL(512, 512, hRes, vRes, "Demo Window")) {
		// if init has an error, exit program.
		return 1;
	}
	
	
	// - - - - - //
	// Threading //
	// - - - - - //
	workers = (pthread_t *) malloc(sizeof(pthread_t) * THREAD_COUNT);
	struct render_t * render_args = (struct render_t *) malloc(sizeof(struct render_t) * THREAD_COUNT);
	for(unsigned long i = 0; i < THREAD_COUNT; i++) {
		render_args[i] = (struct render_t) {i, BOOM};
	}
	
	// Values for input handling
	char loop = 1;
	char update_world = 0;
	
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
			axis.x -= camera_right.x;
			axis.y -= camera_right.y;
			axis.z -= camera_right.z;
		}
		if (look_down) {
			axis.x += camera_right.x;
			axis.y += camera_right.y;
			axis.z += camera_right.z;
		}
		if (look_left) {
			axis.x -= camera_up.x;
			axis.y -= camera_up.y;
			axis.z -= camera_up.z;
		}
		if (look_right) {
			axis.x += camera_up.x;
			axis.y += camera_up.y;
			axis.z += camera_up.z;
		}
		if (roll_right) {
			axis.x -= camera_look.x;
			axis.y -= camera_look.y;
			axis.z -= camera_look.z;
		}
		if (roll_left) {
			axis.x += camera_look.x;
			axis.y += camera_look.y;
			axis.z += camera_look.z;
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
			move_step.x += camera_look.x;
			move_step.y += camera_look.y;
			move_step.z += camera_look.z;
		}
		if (move_back) {
			move_step.x -= camera_look.x;
			move_step.y -= camera_look.y;
			move_step.z -= camera_look.z;
		}
		if (move_right) {
			move_step.x += camera_right.x;
			move_step.y += camera_right.y;
			move_step.z += camera_right.z;
		}
		if (move_left) {
			move_step.x -= camera_right.x;
			move_step.y -= camera_right.y;
			move_step.z -= camera_right.z;
		}
		if (move_up) {
			move_step.x += camera_up.x;
			move_step.y += camera_up.y;
			move_step.z += camera_up.z;
		}
		if (move_down) {
			move_step.x -= camera_up.x;
			move_step.y -= camera_up.y;
			move_step.z -= camera_up.z;
		}
		if (vec_mag(move_step) > 0.001f) {
			move_step = vec_normalize(move_step);
			camera_pos.x += move_step.x * MOVE_SPEED;
			camera_pos.y += move_step.y * MOVE_SPEED;
			camera_pos.z += move_step.z * MOVE_SPEED;
		}
		
		
		// Screen Rendering
		
		clear_screen(0xFF000000);
		
		
		if (update_world) {
			free_obj(BOOM);
			BOOM = make_obj(WORLD.min, WORLD.max, WORLD.map, WORLD.T, WORLD.depth, 0, 0, 0);
			BOOM = prune_obj(BOOM);
			update_world = 0;
		}
		
		if (1) { // Multithread or no?
			// MULTITHREAD RENDERING
			unsigned long i;
			for (i = 0; i < THREAD_COUNT; i++) {
				pthread_create(workers + i, NULL, partial_render, render_args + i);
			}

			for (i = 0; i < THREAD_COUNT; i++) {
				pthread_join(workers[i], NULL);
			}
		} else {
			// Single Thread Rendering
			for (unsigned long y = 0; y < VERTICAL_RESOLUTION; y++) {
				for (unsigned long x = 0; x < HORIZONTAL_RESOLUTION; x++) {

					float yaw = ((float) x - (HORIZONTAL_RESOLUTION - 1) * 0.5f) * (hFOV / HORIZONTAL_RESOLUTION);
					float pitch = ((float) y - (VERTICAL_RESOLUTION - 1) * 0.5f) * (vFOV / VERTICAL_RESOLUTION);

					struct vec_t axis = vec_normalize(vec_add(vec_scale(camera_up, yaw), vec_scale(camera_right, pitch)));

					float ang = sqrt(yaw*yaw + pitch*pitch);

					struct vec_t direction = vec_normalize(vec_rotate(camera_look, axis, ang));

					float dist = 1000.0f;
					unsigned int color = 0;

					cals_intersect_ray_obj((struct ray_t) {camera_pos, direction}, BOOM, &dist, &color);

					draw_pixel(x, y, color);

				}
			}
		}
		
		
		// Render to screen
		render_NoobSDL();
		
	}
	
	// Cleanup and program exit
	free(render_args);
	free(workers);
	quit_NoobSDL();
	free_obj(BOOM);
	free_world(WORLD);
	
	return 0;
}