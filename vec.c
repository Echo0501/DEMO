/**
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 */

#include <math.h>

#include "vec.h"

// This is just for simple vector calculations.
// Most functions are quite simple.
// Its best to not use thess, as direct formulas run faster

struct vec_t vec_add(struct vec_t A, struct vec_t B) {
	return (struct vec_t){A.x + B.x, A.y + B.y, A.z + B.z};
}

struct vec_t vec_sub(struct vec_t A, struct vec_t B) {
	return (struct vec_t){A.x - B.x, A.y - B.y, A.z - B.z};
}

struct vec_t vec_mul(struct vec_t A, struct vec_t B) {
	return (struct vec_t){A.x * B.x, A.y * B.y, A.z * B.z};
}

struct vec_t vec_div(struct vec_t A, struct vec_t B) {
	return (struct vec_t){A.x / B.x, A.y / B.y, A.z / B.z};
}

struct vec_t vec_cross(struct vec_t A, struct vec_t B) {
	return (struct vec_t){(A.y * B.z) - (A.z * B.y), 
						  (A.z * B.x) - (A.x * B.z), 
						  (A.x * B.y) - (A.y * B.x)};
}

float vec_dot(struct vec_t A, struct vec_t B) {
	return (A.x * B.x + A.y * B.y + A.z * B.z);
}

struct vec_t vec_scale(struct vec_t A, float t) {
	return (struct vec_t) {A.x * t, A.y * t, A.z * t};
}

struct vec_t vec_normalize (struct vec_t A) {
	float t = 1.0f / sqrt((A.x * A.x) + (A.y * A.y) + (A.z * A.z));
	return (struct vec_t) {A.x * t, A.y * t, A.z * t};
}

struct vec_t vec_rotate(struct vec_t A, struct vec_t B, float angle) {
	
	// Rotate using rotation matrix.
	// See wikipedia for how it works.
	return (struct vec_t) {((cos(angle) + B.x*B.x*(1.0f - cos(angle)))*A.x + (B.x*B.y*(1.0f - cos(angle)) - B.z*sin(angle))*A.y + (B.x*B.z*(1.0f - cos(angle)) + B.y*sin(angle))*A.z),
						 ((B.y*B.x*(1.0f - cos(angle)) + B.z*sin(angle))*A.x + (cos(angle) + B.y*B.y*(1.0f - cos(angle)))*A.y + (B.y*B.z*(1.0f - cos(angle)) - B.x*sin(angle))*A.z),
						 ((B.z*B.x*(1.0f - cos(angle)) - B.y*sin(angle))*A.x + (B.z*B.y*(1.0f - cos(angle)) + B.x*sin(angle))*A.y + (cos(angle) + B.z*B.z*(1.0f - cos(angle)))*A.z)};
	
}

float vec_mag(struct vec_t A) {
	return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
}
