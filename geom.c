/**
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 */

#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "vec.h"
#include "geom.h"
#include "cube.h"

// Makes a world from min, and max positions, a depth, and a threashold value
// Most of these values are used later
struct world_t make_world(struct vec_t min, struct vec_t max, unsigned long depth, float T) {
	struct world_t rtn = (struct world_t) {min, max, depth, (unsigned long)((1 << depth) + 1), NULL, T};
	rtn.map = (float ***) malloc(sizeof(float **) * rtn.size);
	for(unsigned long i = 0; i < rtn.size; i++) {
		rtn.map[i] = (float **) malloc(sizeof(float *) * rtn.size);
		for(unsigned long j = 0; j < rtn.size; j++) {
			rtn.map[i][j] = (float *) malloc(sizeof(float) * rtn.size);
			for(unsigned long k = 0; k < rtn.size; k++) {
				rtn.map[i][j][k] = 0.0f;
			}
		}
	}
	return rtn;
}

// Frees a world
void free_world(struct world_t WORLD) {
	
	for(unsigned long i = 0; i < WORLD.size; i++) {
		for(unsigned long j = 0; j < WORLD.size; j++) {
			free(WORLD.map[i][j]);
		}
		free(WORLD.map[i]);
	}
	free(WORLD.map);
}

// Makes an obj_t using min, max positions, a map of values, and x, y, z indexies
struct obj_t * make_obj(struct vec_t min, struct vec_t max, float *** map, float T, unsigned long depth, 
			unsigned long x, unsigned long y, unsigned long z) {
	
	
	struct obj_t * rtn = (struct obj_t *) malloc(sizeof(struct obj_t));
		
	rtn->box = (struct bound_box_t) {min, max};
	
	if (depth > 0) {
		
		float xMin = min.x; float xMax = max.x; float xMid = (xMin + xMax) * 0.5f;
		float yMin = min.y; float yMax = max.y; float yMid = (yMin + yMax) * 0.5f;
		float zMin = min.z; float zMax = max.z; float zMid = (zMin + zMax) * 0.5f;
		
		unsigned long d = 1 << (depth - 1);
		
		unsigned long x2 = x+d;
		unsigned long y2 = y+d;
		unsigned long z2 = z+d;
		
		rtn->children_count = 8;
		rtn->children = (struct obj_t **) malloc(sizeof(struct obj_t *) * 8);
		rtn->children[0] = make_obj((struct vec_t) {xMin, yMin, zMin}, (struct vec_t) {xMid, yMid, zMid}, map, T, depth-1, x,  y,  z);
		rtn->children[1] = make_obj((struct vec_t) {xMid, yMin, zMin}, (struct vec_t) {xMax, yMid, zMid}, map, T, depth-1, x2, y,  z);
		rtn->children[2] = make_obj((struct vec_t) {xMin, yMid, zMin}, (struct vec_t) {xMid, yMax, zMid}, map, T, depth-1, x,  y2, z);
		rtn->children[3] = make_obj((struct vec_t) {xMid, yMid, zMin}, (struct vec_t) {xMax, yMax, zMid}, map, T, depth-1, x2, y2, z);
		rtn->children[4] = make_obj((struct vec_t) {xMin, yMin, zMid}, (struct vec_t) {xMid, yMid, zMax}, map, T, depth-1, x,  y,  z2);
		rtn->children[5] = make_obj((struct vec_t) {xMid, yMin, zMid}, (struct vec_t) {xMax, yMid, zMax}, map, T, depth-1, x2, y,  z2);
		rtn->children[6] = make_obj((struct vec_t) {xMin, yMid, zMid}, (struct vec_t) {xMid, yMax, zMax}, map, T, depth-1, x,  y2, z2);
		rtn->children[7] = make_obj((struct vec_t) {xMid, yMid, zMid}, (struct vec_t) {xMax, yMax, zMax}, map, T, depth-1, x2, y2, z2);
		
		rtn->content_count = 0;
		rtn->content = NULL;
		
		return rtn;
		
	} else {
		
		rtn->children_count = 0;
		rtn->children = NULL;
		
		rtn->content_count = 0;
		rtn->content = NULL;
		
		marching_cube(map[x  ][y  ][z], 
					  map[x+1][y  ][z], 
					  map[x  ][y+1][z], 
					  map[x+1][y+1][z], 
					  map[x  ][y  ][z+1], 
					  map[x+1][y  ][z+1], 
					  map[x  ][y+1][z+1], 
					  map[x+1][y+1][z+1], 
					  T, 
					  &rtn->content, &rtn->content_count);
		
		struct vec_t delta = (struct vec_t){(max.x - min.x), (max.y - min.y), (max.z - min.z)};
		
		for(unsigned short i = 0; i < rtn->content_count; i++) {
			rtn->content[i].A = (struct vec_t) {min.x + delta.x * rtn->content[i].A.x,
											  min.y + delta.y * rtn->content[i].A.y,
											  min.z + delta.z * rtn->content[i].A.z};
			rtn->content[i].B = (struct vec_t) {min.x + delta.x * rtn->content[i].B.x,
											  min.y + delta.y * rtn->content[i].B.y,
											  min.z + delta.z * rtn->content[i].B.z};
			rtn->content[i].C = (struct vec_t) {min.x + delta.x * rtn->content[i].C.x,
											  min.y + delta.y * rtn->content[i].C.y,
											  min.z + delta.z * rtn->content[i].C.z};
			
		}
		
		return rtn;
	}

}

struct obj_t * prune_obj(struct obj_t * OBJ) {
	
	if (OBJ == NULL) return NULL;
	
	if (OBJ->children_count > 0) {
		for(int i = 0; i < 8; i++) {
			OBJ->children[i] = prune_obj(OBJ->children[i]);
			if (OBJ->children[i] == NULL) {
				OBJ->children_count--;
			}
		}
	}
	
	if (OBJ->children_count == 0 && OBJ->content_count == 0) {
		free_obj(OBJ);
		return NULL;
	} else {
		return OBJ;
	}
}

// frees a obj_t
void free_obj(struct obj_t * OBJ) {
	
	if (OBJ == NULL) return;
	
	if(OBJ->children_count > 0) {
		for(unsigned short i = 0; i < 8; i++) {
			free_obj(OBJ->children[i]);
		}
		free(OBJ->children);
	}
	if(OBJ->content_count > 0) {
		free(OBJ->content);
	}
	free(OBJ);
}

// makes a color darker by using color_scale value
unsigned int shadow_color(const unsigned int color, const float color_scale) {

	float a = (float)((color >> 24) & 0xFF) * color_scale;
	float r = (float)((color >> 16) & 0xFF) * color_scale;
	float g = (float)((color >> 8) & 0xFF) * color_scale;
	float b = (float)((color >> 0) & 0xFF) * color_scale;

	return ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | ((unsigned int)b);

}


// Calculates if a ray intersects with a triangle.
// if it does, and it is closer than current value if dist, write new values in
void cals_intersect_ray_tri(const struct ray_t RAY, const struct triangle_t * TRI, float * dist, unsigned int * color) {
	
	// Calc intersect between Ray and triangle
	
	struct vec_t AB = (struct vec_t) {(TRI->B.x - TRI->A.x), (TRI->B.y - TRI->A.y), (TRI->B.z - TRI->A.z)};
	struct vec_t AC = (struct vec_t) {(TRI->C.x - TRI->A.x), (TRI->C.y - TRI->A.y), (TRI->C.z - TRI->A.z)};
	
	struct vec_t N = (struct vec_t){(AB.y * AC.z) - (AB.z * AC.y), 
									(AB.z * AC.x) - (AB.x * AC.z), 
									(AB.x * AC.y) - (AB.y * AC.x)};
	
	float nMag = 1.0f / sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
	
	N.x *= nMag;
	N.y *= nMag;
	N.z *= nMag;
	
	// Check if ray hits outside of triangle
	float nn = ((N.x * RAY.Direction.x) + (N.y * RAY.Direction.y) + (N.z * RAY.Direction.z));
	if (nn >= 0.0f) return;
	
	float t = (((TRI->A.x - RAY.Origin.x) * N.x) + ((TRI->A.y - RAY.Origin.y) * N.y) + ((TRI->A.z - RAY.Origin.z) * N.z)) / ((RAY.Direction.x * N.x) + (RAY.Direction.y * N.y) + (RAY.Direction.z * N.z));
	
	if (t < *dist && t > 0.0f)  {
		
		struct vec_t x = (struct vec_t) {(RAY.Origin.x + (RAY.Direction.x * t)), (RAY.Origin.y + (RAY.Direction.y * t)), (RAY.Origin.z + (RAY.Direction.z * t))};
		struct vec_t dx = (struct vec_t){(x.x - TRI->A.x), (x.y - TRI->A.y), (x.z - TRI->A.z)};
		
		// Calculate U and V
		float d00 = (AB.x * AB.x) + (AB.y * AB.y) + (AB.z * AB.z);
		float d01 = (AB.x * AC.x) + (AB.y * AC.y) + (AB.z * AC.z);
		float d02 = (AB.x * dx.x) + (AB.y * dx.y) + (AB.z * dx.z);
		float d11 = (AC.x * AC.x) + (AC.y * AC.y) + (AC.z * AC.z);
		float d12 = (AC.x * dx.x) + (AC.y * dx.y) + (AC.z * dx.z);

		float denom = 1.0f / (d01*d01 - d00*d11);
		float u = (d12*d01 - d02*d11) * denom;
		float v = (d02*d01 - d12*d00) * denom;
		
		if (u > 0.0f && v > 0.0f && u + v < 1.0f) {
			*dist = t;
			
			float color_scale = nn > 0.0 ? nn : nn * -1.0;
			*color = shadow_color(TRI->color, color_scale);
		}
	}
}

// Calcualtes the distance between the intersect of a Ray and a box.
// Writes the values into tMin, and tMax
void ray_box(const struct ray_t RAY, const struct bound_box_t Box, float * tMin, float * tMax) {	
	// Determine if RAY hits bound box
	
	float t1 = (Box.A.x - RAY.Origin.x) / RAY.Direction.x;
	float t2 = (Box.B.x - RAY.Origin.x) / RAY.Direction.x;
	
	float t3 = (Box.A.y - RAY.Origin.y) / RAY.Direction.y;
	float t4 = (Box.B.y - RAY.Origin.y) / RAY.Direction.y;
	
	float t5 = (Box.A.z - RAY.Origin.z) / RAY.Direction.z;
	float t6 = (Box.B.z - RAY.Origin.z) / RAY.Direction.z;
	
	float tmpMin;
	float tmpMax;
	
	if (t1 < t2) {
		tmpMin = t1;
		tmpMax = t2;
	} else {
		tmpMin = t2;
		tmpMax = t1;
	}
	if (t3 < t4) {
		if (t3 > tmpMin) tmpMin = t3;
		if (t4 < tmpMax) tmpMax = t4;
	} else {
		if (t4 > tmpMin) tmpMin = t4;
		if (t3 < tmpMax) tmpMax = t3;
	}
	if (t5 < t6) {
		if (t5 > tmpMin) tmpMin = t5;
		if (t6 < tmpMax) tmpMax = t6;
	} else {
		if (t6 > tmpMin) tmpMin = t6;
		if (t5 < tmpMax) tmpMax = t5;
	}
	
	*tMin = tmpMin;
	*tMax = tmpMax;
	
}

const unsigned int search_order[48][8] = {
	{7,6,5,4,3,2,1,0},
	{6,7,4,5,2,3,0,1},
	{5,4,7,6,1,0,3,2},
	{4,5,6,7,0,1,2,3},
	{3,2,1,0,7,6,5,4},
	{2,3,0,1,6,7,4,5},
	{1,0,3,2,5,4,7,6},
	{0,1,2,3,4,5,6,7},
	{7,6,3,2,5,4,1,0},
	{6,7,2,3,4,5,0,1},
	{5,4,1,0,7,6,3,2},
	{4,5,0,1,6,7,2,3},
	{3,2,7,6,1,0,5,4},
	{2,3,6,7,0,1,4,5},
	{1,0,5,4,3,2,7,6},
	{0,1,4,5,2,3,6,7},
	{7,5,6,4,3,1,2,0},
	{6,4,7,5,0,2,3,1},
	{5,7,4,6,1,3,0,2},
	{4,6,5,7,0,2,1,3},
	{3,1,2,0,7,5,6,4},
	{2,0,3,1,6,4,7,5},
	{1,3,0,2,5,7,4,6},
	{0,2,1,3,4,6,5,7},
	{7,5,3,1,6,4,2,0},
	{6,4,0,2,7,5,3,1},
	{5,7,1,3,4,6,0,2},
	{4,6,0,2,5,7,1,3},
	{3,1,7,5,2,0,6,4},
	{2,0,6,4,3,1,7,5},
	{1,3,5,7,0,2,4,6},
	{0,2,6,4,1,3,5,7},
	{7,3,6,2,5,1,4,0},
	{6,2,7,3,4,0,5,1},
	{5,1,4,0,7,3,6,2},
	{4,0,5,1,6,2,7,3},
	{3,7,2,6,1,5,0,4},
	{2,6,3,7,0,4,1,5},
	{1,5,0,4,3,7,2,6},
	{0,4,1,5,2,6,3,7},
	{7,3,5,1,6,2,4,0},
	{6,2,4,0,7,3,5,1},
	{5,1,7,3,4,0,6,2},
	{4,0,6,2,5,1,7,3},
	{3,7,1,5,2,6,0,4},
	{2,6,0,4,3,7,1,5},
	{1,5,3,7,0,4,2,6},
	{0,4,2,6,1,5,3,7}
};

// Calculates the best intersetion between obj_t and a ray.
// Recursive call to either more calc_ray_obj, or calc_ray_triangle
// Returns values by writting them to pointers, dist and color.
void cals_intersect_ray_obj(const struct ray_t RAY, const struct obj_t * OBJ, float * dist, unsigned int * color) {
	
	if (OBJ == NULL) return;
	
	float tmp_min = 1.0;
	float tmp_max = -1.0;
	
	ray_box(RAY, OBJ->box, &tmp_min, &tmp_max);
	
	if (tmp_max < 0.0 || tmp_max < tmp_min || tmp_min > *dist) return;
	
	if (OBJ->children_count > 0) {
		
		struct vec_t dir = RAY.Direction;

		float x = dir.x;
		float y = dir.y;
		float z = dir.z;

		float x2 = x*x;
		float y2 = y*y;
		float z2 = z*z;

		unsigned short state = 0;

		if (x >= 0.0) state |= 1;
		if (y >= 0.0) state |= 2;
		if (z >= 0.0) state |= 4;

		if (x2 >= y2 && x2 >= z2) {
			if (y2 >= z2) {
				state |= 0;
			} else {
				state |= 8;
			}
		} else if (y2 >= x2 && y2 >= z2) {
			if (x2 >= z2) {
				state |= 16;
			} else {
				state |= 24;
			}
		} else if (z2 >= x2 && z2 >= y2) {
			if (x2 >= y2) {
				state |= 32;
			} else {
				state |= 40;
			}
		}
		
		for(unsigned int i = 0; i < 8; i++) {
			cals_intersect_ray_obj(RAY, OBJ->children[search_order[state][i]], dist, color);
		}
		
	} else {
		// Calls to check triangle contents
		for(unsigned short i = 0; i < OBJ->content_count; i++) {
			cals_intersect_ray_tri(RAY, OBJ->content + i, dist, color);
		}
	}
}