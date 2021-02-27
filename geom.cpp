#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <algorithm>

#include "vec.h"
#include "geom.h"
#include "cube.h"


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

void free_world(struct world_t WORLD) {
	
	for(unsigned long i = 0; i < WORLD.size; i++) {
		for(unsigned long j = 0; j < WORLD.size; j++) {
			free(WORLD.map[i][j]);
		}
		free(WORLD.map[i]);
	}
	free(WORLD.map);
}


struct obj_t make_obj(struct vec_t min, struct vec_t max, float *** map, float T, unsigned long depth, 
			unsigned long x, unsigned long y, unsigned long z) {
	
	
	struct obj_t rtn;
		
	rtn.box = (struct bound_box_t) {min, max};
	
	if (depth > 0) {
		
		float xMin = min.x; float xMax = max.x; float xMid = (xMin + xMax) / 2.0f;
		float yMin = min.y; float yMax = max.y; float yMid = (yMin + yMax) / 2.0f;
		float zMin = min.z; float zMax = max.z; float zMid = (zMin + zMax) / 2.0f;
		
		unsigned long d = 1 << (depth - 1);
		
		rtn.children_count = 8;
		rtn.children = (struct obj_t *) malloc(sizeof(struct obj_t) * 8);
		rtn.children[0] = make_obj((struct vec_t) {xMin, yMin, zMin}, (struct vec_t) {xMid, yMid, zMid}, map, T, depth-1, x,   y,   z);
		rtn.children[1] = make_obj((struct vec_t) {xMid, yMin, zMin}, (struct vec_t) {xMax, yMid, zMid}, map, T, depth-1, x+d, y,   z);
		rtn.children[2] = make_obj((struct vec_t) {xMin, yMid, zMin}, (struct vec_t) {xMid, yMax, zMid}, map, T, depth-1, x,   y+d, z);
		rtn.children[3] = make_obj((struct vec_t) {xMid, yMid, zMin}, (struct vec_t) {xMax, yMax, zMid}, map, T, depth-1, x+d, y+d, z);
		rtn.children[4] = make_obj((struct vec_t) {xMin, yMin, zMid}, (struct vec_t) {xMid, yMid, zMax}, map, T, depth-1, x,   y,   z+d);
		rtn.children[5] = make_obj((struct vec_t) {xMid, yMin, zMid}, (struct vec_t) {xMax, yMid, zMax}, map, T, depth-1, x+d, y,   z+d);
		rtn.children[6] = make_obj((struct vec_t) {xMin, yMid, zMid}, (struct vec_t) {xMid, yMax, zMax}, map, T, depth-1, x,   y+d, z+d);
		rtn.children[7] = make_obj((struct vec_t) {xMid, yMid, zMid}, (struct vec_t) {xMax, yMax, zMax}, map, T, depth-1, x+d, y+d, z+d);
		
		rtn.content_count = 0;
		rtn.content = NULL;
		
		return rtn;
		
	} else {
		
		rtn.children_count = 0;
		rtn.children = NULL;
		
		rtn.content_count = 0;
		rtn.content = NULL;
		
		marching_cube(map[x  ][y  ][z], 
					  map[x+1][y  ][z], 
					  map[x  ][y+1][z], 
					  map[x+1][y+1][z], 
					  map[x  ][y  ][z+1], 
					  map[x+1][y  ][z+1], 
					  map[x  ][y+1][z+1], 
					  map[x+1][y+1][z+1], 
					  T, 
					  &rtn.content, &rtn.content_count);
		
		struct vec_t delta = (struct vec_t){(max.x - min.x), (max.y - min.y), (max.z - min.z)};
		
		for(unsigned short i = 0; i < rtn.content_count; i++) {
			rtn.content[i].A = (struct vec_t) {min.x + delta.x * rtn.content[i].A.x,
											  min.y + delta.y * rtn.content[i].A.y,
											  min.z + delta.z * rtn.content[i].A.z};
			rtn.content[i].B = (struct vec_t) {min.x + delta.x * rtn.content[i].B.x,
											  min.y + delta.y * rtn.content[i].B.y,
											  min.z + delta.z * rtn.content[i].B.z};
			rtn.content[i].C = (struct vec_t) {min.x + delta.x * rtn.content[i].C.x,
											  min.y + delta.y * rtn.content[i].C.y,
											  min.z + delta.z * rtn.content[i].C.z};
			
		}
		
		return rtn;
	}

}

void free_obj(struct obj_t OBJ) {
	
	if(OBJ.children_count > 0) {
		for(unsigned short i = 0; i < OBJ.children_count; i++) {
			free_obj(OBJ.children[i]);
		}
		free(OBJ.children);
	}
	if(OBJ.content_count > 0) {
		free(OBJ.content);
	}
}



unsigned int shadow_color(const unsigned int color, const float color_scale) {

	float a = (float)((color >> 24) & 0xFF);
	float r = (float)((color >> 16) & 0xFF);
	float g = (float)((color >> 8) & 0xFF);
	float b = (float)((color >> 0) & 0xFF);

	a *= color_scale;
	r *= color_scale;
	g *= color_scale;
	b *= color_scale;

	return ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | ((unsigned int)b);

}



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



void ray_box(const struct ray_t RAY, const struct bound_box_t Box, float * tMin, float * tMax) {	
	// Determine if RAY hits bound box
	
	*tMin = -10000000.0f;
	*tMax = 10000000.0f;
	
	// CALCULATE X-AXIS INTERSECTION
	if (RAY.Direction.x == 0.0) {
		if (RAY.Origin.x < Box.A.x || RAY.Origin.x > Box.B.x) {
			// Misses Box of Obj
			*tMin = 10000000.0f;
			*tMax = -10000000.0f;
			return;
		}
	} else {
		
		float t1 = (Box.A.x - RAY.Origin.x) / RAY.Direction.x;
		float t2 = (Box.B.x - RAY.Origin.x) / RAY.Direction.x;
		
		if (t1 < t2) {
			if (t2 < *tMax) *tMax = t2;
			if (t1 > *tMin) *tMin = t1;	
		} else {
			if (t1 < *tMax) *tMax = t1;
			if (t2 > *tMin) *tMin = t2;
		}
	}
	
	// CALCULATE Y-AXIS INTERSECTION
	if (RAY.Direction.y == 0.0) {
		if (RAY.Origin.y < Box.A.y || RAY.Origin.y > Box.B.y) {
			// Misses Box of Obj
			*tMin = 10000000.0f;
			*tMax = -10000000.0f;
			return;
		}
	} else {
		
		float t1 = (Box.A.y - RAY.Origin.y) / RAY.Direction.y;
		float t2 = (Box.B.y - RAY.Origin.y) / RAY.Direction.y;
		
		if (t1 < t2) {
			if (t2 < *tMax) *tMax = t2;
			if (t1 > *tMin) *tMin = t1;	
		} else {
			if (t1 < *tMax) *tMax = t1;
			if (t2 > *tMin) *tMin = t2;
		}
	}
	
	// CALCULATE Z-AXIS INTERSECTION
	if (RAY.Direction.z == 0.0) {
		if (RAY.Origin.z < Box.A.z || RAY.Origin.z > Box.B.z) {
			// Misses Box of Obj
			*tMin = 10000000.0f;
			*tMax = -10000000.0f;
			return;
		}
	} else {
		
		float t1 = (Box.A.z - RAY.Origin.z) / RAY.Direction.z;
		float t2 = (Box.B.z - RAY.Origin.z) / RAY.Direction.z;
		
		if (t1 < t2) {
			if (t2 < *tMax) *tMax = t2;
			if (t1 > *tMin) *tMin = t1;	
		} else {
			if (t1 < *tMax) *tMax = t1;
			if (t2 > *tMin) *tMin = t2;
		}
	}
}

struct rayboxtmp_t {
	int index;
	float min_dist;
	float max_dist;
};
bool compar(const struct rayboxtmp_t A, const struct rayboxtmp_t B) {
	return A.min_dist < B.min_dist;
}


// Calculates the best intersetion between obj_t and a ray.
void cals_intersect_ray_obj(const struct ray_t RAY, const struct obj_t * OBJ, float * dist, unsigned int * color) {
	
	if (OBJ->children_count > 0) {
		struct rayboxtmp_t  dist_list[8];

		for(int i = 0; i < 8; i++) {
			dist_list[i].index = i;
			ray_box(RAY, OBJ->children[i].box, &(dist_list[i].min_dist), &(dist_list[i].max_dist));
		}
		
		//qsort(dist_list, 8, sizeof(struct rayboxtmp_t), compar);
		std::sort(dist_list, dist_list+8, compar);
		
		// Recursive Calls to children Obj
		for(int i = 0; i < 8; i++) {
			if (dist_list[i].min_dist < dist_list[i].max_dist && dist_list[i].min_dist < *dist && dist_list[i].max_dist > 0.0f) {
				cals_intersect_ray_obj(RAY, OBJ->children + (dist_list[i].index), dist, color);
			}
		}
	} else {
		// Calls to check triangle contents
		for(unsigned short i = 0; i < OBJ->content_count; i++) {
			cals_intersect_ray_tri(RAY, OBJ->content + i, dist, color);
		}
	}
	
}