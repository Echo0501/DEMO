/**
 * Made by Duncan McCloud
 * duncmccl@udel.edu
 */

#ifdef __cplusplus
extern "C" {
#endif

struct bound_box_t {
	struct vec_t A; 
	struct vec_t B;
};

struct ray_t {
	struct vec_t Origin;
	struct vec_t Direction;
};


struct triangle_t {
	struct vec_t A;
	struct vec_t B;
	struct vec_t C;
	
	unsigned int color;
};

struct world_t {
	struct vec_t min;
	struct vec_t max;
	
	unsigned long depth;
	
	unsigned long size;
	float *** map;
	
	float T;
};

struct obj_t {
	
	struct bound_box_t box;
	
	struct obj_t ** children;
	unsigned short children_count;
	
	struct triangle_t * content;
	unsigned short content_count;
	
};


struct world_t make_world(struct vec_t min, struct vec_t max, unsigned long depth, float T);
void free_world(struct world_t WORLD);

struct obj_t * make_obj(struct vec_t min, struct vec_t max, float *** map, float T, unsigned long depth, unsigned long x, unsigned long y, unsigned long z);
struct obj_t * prune_obj(struct obj_t * OBJ);
void free_obj(struct obj_t * OBJ);

void cals_intersect_ray_tri(const struct ray_t RAY, const struct triangle_t * TRI, float * dist, unsigned int * color);
void cals_intersect_ray_obj(const struct ray_t RAY, const struct obj_t * OBJ, float * dist, unsigned int * color);

#ifdef __cplusplus
}
#endif