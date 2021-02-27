
#ifdef __cplusplus
extern "C" {
#endif


struct vec_t {
	float x, y, z;
};

struct vec_t vec_add(struct vec_t A, struct vec_t B);
struct vec_t vec_sub(struct vec_t A, struct vec_t B);
struct vec_t vec_mul(struct vec_t A, struct vec_t B);
struct vec_t vec_div(struct vec_t A, struct vec_t B);
struct vec_t vec_cross(struct vec_t A, struct vec_t B);
struct vec_t vec_scale(struct vec_t A, float t);
struct vec_t vec_rotate(struct vec_t A, struct vec_t Axis, float ang);
struct vec_t vec_normalize(struct vec_t A);
float vec_dot(struct vec_t A, struct vec_t B);
float vec_mag(struct vec_t A);

#ifdef __cplusplus
}
#endif
