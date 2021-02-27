#include <stdlib.h>

#include "vec.h"
#include "geom.h"
#include "cube.h"

/*
For Marching Cubes:
*/
void marching_cube(float A, float B, float C, float D, 
				   float E, float F, float G, float H, 
				   float T,
				   struct triangle_t ** tri_list, unsigned short * tri_count) {

	unsigned char cube_index = 0x00;
	if (A > T) cube_index += 0x01;
	if (B > T) cube_index += 0x02;
	if (C > T) cube_index += 0x10;
	if (D > T) cube_index += 0x20;
	if (E > T) cube_index += 0x08;
	if (F > T) cube_index += 0x04;
	if (G > T) cube_index += 0x80;
	if (H > T) cube_index += 0x40;
	
	struct vec_t AB = {(T-A)/(B-A), 0.0, 0.0};
	struct vec_t AC = {0.0, (T-A)/(C-A), 0.0};
	struct vec_t AE = {0.0, 0.0, (T-A)/(E-A)};
	struct vec_t BD = {1.0, (T-B)/(D-B), 0.0};
	struct vec_t BF = {1.0, 0.0, (T-B)/(F-B)};
	struct vec_t CD = {(T-C)/(D-C), 1.0, 0.0};
	struct vec_t CG = {0.0, 1.0, (T-C)/(G-C)};
	struct vec_t DH = {1.0, 1.0, (T-D)/(H-D)};
	struct vec_t EF = {(T-E)/(F-E), 0.0, 1.0};
	struct vec_t EG = {0.0, (T-E)/(G-E), 1.0};
	struct vec_t FH = {1.0, (T-F)/(H-F), 1.0};
	struct vec_t GH = {(T-G)/(H-G), 1.0, 1.0};

	switch (cube_index) {
		case 0x00:
			*tri_count = 0;
			*tri_list = NULL;
			break;
		case 0x01:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			break;
		case 0x02:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			break;
		case 0x03:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AC, BF, 0xFF808080};
			break;
		case 0x04:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			break;
		case 0x05:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			break;
		case 0x06:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, EF, BD, 0xFF808080};
			break;
		case 0x07:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, FH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, BD, AC, 0xFF808080};
			break;
		case 0x08:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AE, EG, EF, 0xFF808080};
			break;
		case 0x09:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, EG, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, EG, AB, 0xFF808080};
			break;
		case 0x0A:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, BD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			break;
		case 0x0B:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, EG, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AC, EG, 0xFF808080};
			break;
		case 0x0C:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AE, FH, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, FH, AE, 0xFF808080};
			break;
		case 0x0D:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, FH, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AC, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, EG, FH, 0xFF808080};
			break;
		case 0x0E:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, BD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, EG, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, FH, BD, 0xFF808080};
			break;
		case 0x0F:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, AC, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, AC, EG, 0xFF808080};
			break;
		case 0x10:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {CD, CG, AC, 0xFF808080};
			break;
		case 0x11:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {CD, AE, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AE, CD, 0xFF808080};
			break;
		case 0x12:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			break;
		case 0x13:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, CG, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, AE, BF, 0xFF808080};
			break;
		case 0x14:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			break;
		case 0x15:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, CD, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, AB, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			break;
		case 0x16:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AB, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			break;
		case 0x17:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, FH, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, BD, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, CG, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, BD, CD, 0xFF808080};
			break;
		case 0x18:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, EG, EF, 0xFF808080};
			break;
		case 0x19:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, CD, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, EF, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AB, CD, 0xFF808080};
			break;
		case 0x1A:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, AB, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			break;
		case 0x1B:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, CG, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, CD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, EF, BF, 0xFF808080};
			break;
		case 0x1C:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, FH, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, EG, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, AC, CD, 0xFF808080};
			break;
		case 0x1D:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, EG, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, CD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AB, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, EG, CD, 0xFF808080};
			break;
		case 0x1E:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, CG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AB, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, AB, AE, 0xFF808080};
			break;
		case 0x1F:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, CG, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, EG, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, FH, 0xFF808080};
			break;
		case 0x20:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			break;
		case 0x21:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			break;
		case 0x22:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, DH, AB, 0xFF808080};
			break;
		case 0x23:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, AE, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, BF, DH, 0xFF808080};
			break;
		case 0x24:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			break;
		case 0x25:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, AB, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			break;
		case 0x26:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, CD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, AB, EF, 0xFF808080};
			break;
		case 0x27:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, FH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, EF, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, DH, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, CD, AC, 0xFF808080};
			break;
		case 0x28:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			break;
		case 0x29:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, EG, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AC, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			break;
		case 0x2A:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, BF, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			break;
		case 0x2B:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, BF, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, DH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AC, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, AC, DH, 0xFF808080};
			break;
		case 0x2C:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, AE, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, BF, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			break;
		case 0x2D:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AC, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, FH, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, EG, FH, 0xFF808080};
			break;
		case 0x2E:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, CD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, AB, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, EG, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, AB, AE, 0xFF808080};
			break;
		case 0x2F:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, CD, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, AC, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, AC, EG, 0xFF808080};
			break;
		case 0x30:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, CG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, CG, BD, 0xFF808080};
			break;
		case 0x31:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, AE, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, DH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, CG, AE, 0xFF808080};
			break;
		case 0x32:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, CG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, DH, CG, 0xFF808080};
			break;
		case 0x33:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, DH, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, DH, CG, 0xFF808080};
			break;
		case 0x34:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, CG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, DH, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, BF, EF, 0xFF808080};
			break;
		case 0x35:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, BF, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, DH, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, AE, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, CG, AE, 0xFF808080};
			break;
		case 0x36:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, AB, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, EF, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, DH, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, DH, EF, 0xFF808080};
			break;
		case 0x37:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, FH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, DH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, DH, CG, 0xFF808080};
			break;
		case 0x38:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, BD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AC, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, EG, EF, 0xFF808080};
			break;
		case 0x39:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, CG, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EF, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, CG, EG, 0xFF808080};
			break;
		case 0x3A:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, BF, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, DH, CG, 0xFF808080};
			break;
		case 0x3B:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, EF, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, BF, DH, 0xFF808080};
			break;
		case 0x3C:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, DH, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, BF, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, AE, EG, 0xFF808080};
			break;
		case 0x3D:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {DH, CG, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, AB, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, EG, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, AB, FH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EG, FH, AB, 0xFF808080};
			break;
		case 0x3E:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {EG, FH, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, AB, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, DH, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, AB, CG, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {DH, CG, AB, 0xFF808080};
			break;
		case 0x3F:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {EG, FH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, EG, DH, 0xFF808080};
			break;
		case 0x40:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {FH, GH, DH, 0xFF808080};
			break;
		case 0x41:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x42:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, AB, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x43:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, BD, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x44:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, GH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, GH, BF, 0xFF808080};
			break;
		case 0x45:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, GH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, AB, AC, 0xFF808080};
			break;
		case 0x46:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, GH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, EF, GH, 0xFF808080};
			break;
		case 0x47:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, BD, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, AC, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, EF, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, EF, AC, 0xFF808080};
			break;
		case 0x48:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, GH, DH, 0xFF808080};
			break;
		case 0x49:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, AB, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, EF, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, GH, DH, 0xFF808080};
			break;
		case 0x4A:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x4B:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, BD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, AC, EG, 0xFF808080};
			break;
		case 0x4C:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, AE, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, DH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, BF, AE, 0xFF808080};
			break;
		case 0x4D:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, EG, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, DH, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, EG, GH, 0xFF808080};
			break;
		case 0x4E:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, EG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AE, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, DH, BD, 0xFF808080};
			break;
		case 0x4F:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, DH, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, BD, AC, 0xFF808080};
			break;
		case 0x50:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, CG, AC, 0xFF808080};
			break;
		case 0x51:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, AE, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, CG, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, DH, FH, 0xFF808080};
			break;
		case 0x52:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, BD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			break;
		case 0x53:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, GH, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, BD, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, BD, CD, 0xFF808080};
			break;
		case 0x54:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, BF, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, DH, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, CG, AC, 0xFF808080};
			break;
		case 0x55:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EF, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, AB, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, CD, CG, 0xFF808080};
			break;
		case 0x56:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AB, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, EF, GH, 0xFF808080};
			break;
		case 0x57:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {CG, AE, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, BD, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, EF, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, BD, GH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EF, GH, BD, 0xFF808080};
			break;
		case 0x58:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, EG, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AC, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, GH, DH, 0xFF808080};
			break;
		case 0x59:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, CG, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, EF, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, CG, EG, 0xFF808080};
			break;
		case 0x5A:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, CG, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x5B:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BD, EF, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, EG, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, CD, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, EG, CD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {DH, FH, GH, 0xFF808080};
			break;
		case 0x5C:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, EG, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, DH, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, EG, GH, 0xFF808080};
			break;
		case 0x5D:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {DH, BF, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EG, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AB, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, EG, CD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AB, CD, EG, 0xFF808080};
			break;
		case 0x5E:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AB, DH, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, GH, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, AE, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, GH, AE, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AC, CD, CG, 0xFF808080};
			break;
		case 0x5F:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {GH, DH, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, CG, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, EG, BD, 0xFF808080};
			break;
		case 0x60:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {FH, CD, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, CD, FH, 0xFF808080};
			break;
		case 0x61:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, FH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BD, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			break;
		case 0x62:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, AB, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, GH, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, CD, AB, 0xFF808080};
			break;
		case 0x63:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, AE, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, BF, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, GH, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, BF, FH, 0xFF808080};
			break;
		case 0x64:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, CD, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, GH, CD, 0xFF808080};
			break;
		case 0x65:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, AB, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, CD, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, GH, CD, 0xFF808080};
			break;
		case 0x66:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, EF, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, EF, GH, 0xFF808080};
			break;
		case 0x67:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, AE, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, EF, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, EF, GH, 0xFF808080};
			break;
		case 0x68:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, CD, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, GH, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, EF, AE, 0xFF808080};
			break;
		case 0x69:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AC, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, BD, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, FH, GH, 0xFF808080};
			break;
		case 0x6A:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, EG, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, BF, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, BF, FH, 0xFF808080};
			break;
		case 0x6B:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {GH, CD, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, BF, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, AC, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, BF, EG, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AC, EG, BF, 0xFF808080};
			break;
		case 0x6C:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, GH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AE, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, BF, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, GH, AE, 0xFF808080};
			break;
		case 0x6D:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AC, EG, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, BF, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, GH, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, BF, CD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {GH, CD, BF, 0xFF808080};
			break;
		case 0x6E:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, EG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, GH, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, CD, 0xFF808080};
			break;
		case 0x6F:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {GH, CD, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, GH, AC, 0xFF808080};
			break;
		case 0x70:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, FH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AC, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, BD, FH, 0xFF808080};
			break;
		case 0x71:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, CG, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, FH, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BD, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, CG, FH, 0xFF808080};
			break;
		case 0x72:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, GH, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, FH, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, AC, AB, 0xFF808080};
			break;
		case 0x73:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, GH, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, CG, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, AE, 0xFF808080};
			break;
		case 0x74:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, GH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AC, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, GH, CG, 0xFF808080};
			break;
		case 0x75:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {EF, GH, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, BD, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, CG, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, BD, AE, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {CG, AE, BD, 0xFF808080};
			break;
		case 0x76:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, AC, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, AB, EF, 0xFF808080};
			break;
		case 0x77:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {CG, AE, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, CG, EF, 0xFF808080};
			break;
		case 0x78:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, GH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, AC, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, GH, CG, 0xFF808080};
			break;
		case 0x79:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {EF, AB, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, CG, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BD, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, CG, FH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BD, FH, CG, 0xFF808080};
			break;
		case 0x7A:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BF, AC, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, CG, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, FH, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, CG, FH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EF, AE, EG, 0xFF808080};
			break;
		case 0x7B:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EG, EF, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, GH, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, CG, BF, 0xFF808080};
			break;
		case 0x7C:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AC, BD, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, GH, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, BF, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, GH, AE, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BF, AE, GH, 0xFF808080};
			break;
		case 0x7D:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, BD, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, GH, CG, 0xFF808080};
			break;
		case 0x7E:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CG, AC, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, EG, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, GH, AB, 0xFF808080};
			break;
		case 0x7F:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {CG, EG, GH, 0xFF808080};
			break;
		case 0x80:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {CG, GH, EG, 0xFF808080};
			break;
		case 0x81:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AE, AB, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			break;
		case 0x82:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			break;
		case 0x83:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, AE, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			break;
		case 0x84:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {FH, BF, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, EG, CG, 0xFF808080};
			break;
		case 0x85:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, AB, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, EG, CG, 0xFF808080};
			break;
		case 0x86:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, BD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, FH, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, EG, CG, 0xFF808080};
			break;
		case 0x87:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {GH, EG, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, FH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, AC, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, BD, AC, 0xFF808080};
			break;
		case 0x88:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {CG, EF, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, EF, CG, 0xFF808080};
			break;
		case 0x89:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, AB, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, GH, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, EF, AB, 0xFF808080};
			break;
		case 0x8A:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, CG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			break;
		case 0x8B:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, GH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, AC, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, BD, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, CG, GH, 0xFF808080};
			break;
		case 0x8C:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, CG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AE, CG, 0xFF808080};
			break;
		case 0x8D:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, CG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, CG, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AC, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, AB, AC, 0xFF808080};
			break;
		case 0x8E:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, AE, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, CG, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, FH, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, FH, CG, 0xFF808080};
			break;
		case 0x8F:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, GH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, FH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, FH, BD, 0xFF808080};
			break;
		case 0x90:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {GH, AC, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, AC, GH, 0xFF808080};
			break;
		case 0x91:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, GH, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, CD, GH, 0xFF808080};
			break;
		case 0x92:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, GH, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AB, BF, 0xFF808080};
			break;
		case 0x93:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, CD, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, GH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AE, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, AE, GH, 0xFF808080};
			break;
		case 0x94:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, AC, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, EG, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, FH, BF, 0xFF808080};
			break;
		case 0x95:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, AB, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, CD, GH, 0xFF808080};
			break;
		case 0x96:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, EG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, GH, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, EF, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, FH, BD, 0xFF808080};
			break;
		case 0x97:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {FH, BD, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, AE, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, CD, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, AE, GH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {CD, GH, AE, 0xFF808080};
			break;
		case 0x98:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, EF, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, GH, EF, 0xFF808080};
			break;
		case 0x99:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, CD, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, GH, EF, 0xFF808080};
			break;
		case 0x9A:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, BD, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, CD, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, AE, AC, 0xFF808080};
			break;
		case 0x9B:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, BD, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, CD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, CD, GH, 0xFF808080};
			break;
		case 0x9C:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, BF, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, GH, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, CD, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, FH, BF, 0xFF808080};
			break;
		case 0x9D:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {FH, BF, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, AB, CD, 0xFF808080};
			break;
		case 0x9E:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {CD, GH, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, AE, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {GH, FH, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, AE, BD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {FH, BD, AE, 0xFF808080};
			break;
		case 0x9F:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {FH, BD, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, FH, CD, 0xFF808080};
			break;
		case 0xA0:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, GH, EG, 0xFF808080};
			break;
		case 0xA1:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			break;
		case 0xA2:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, AB, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, CD, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, GH, EG, 0xFF808080};
			break;
		case 0xA3:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, AE, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, DH, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, BF, DH, 0xFF808080};
			break;
		case 0xA4:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, BF, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, GH, EG, 0xFF808080};
			break;
		case 0xA5:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {GH, EG, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, BD, DH, 0xFF808080};
			break;
		case 0xA6:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CG, GH, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, CD, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, EF, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, AB, EF, 0xFF808080};
			break;
		case 0xA7:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AE, CD, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, DH, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, EF, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, DH, EF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EG, CG, GH, 0xFF808080};
			break;
		case 0xA8:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CG, EF, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, GH, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, CD, BD, 0xFF808080};
			break;
		case 0xA9:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, AC, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, AC, CG, 0xFF808080};
			break;
		case 0xAA:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, GH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, CG, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, DH, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, CD, AB, 0xFF808080};
			break;
		case 0xAB:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {GH, EF, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, AC, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, BF, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, AC, DH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BF, DH, AC, 0xFF808080};
			break;
		case 0xAC:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, BF, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, AE, CG, 0xFF808080};
			break;
		case 0xAD:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BF, GH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, CG, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, AB, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, CG, AB, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BD, DH, CD, 0xFF808080};
			break;
		case 0xAE:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {CD, AB, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, FH, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, AE, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {GH, FH, CG, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AE, CG, FH, 0xFF808080};
			break;
		case 0xAF:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CG, GH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, FH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, CD, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, AC, FH, 0xFF808080};
			break;
		case 0xB0:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, BD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, EG, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, AC, BD, 0xFF808080};
			break;
		case 0xB1:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, GH, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, GH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, DH, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, BD, DH, 0xFF808080};
			break;
		case 0xB2:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, EG, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, DH, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BF, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, GH, EG, 0xFF808080};
			break;
		case 0xB3:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {GH, EG, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, AE, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, AE, BF, 0xFF808080};
			break;
		case 0xB4:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, DH, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, DH, GH, 0xFF808080};
			break;
		case 0xB5:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AB, EG, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, GH, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BD, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, GH, BD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BF, EF, FH, 0xFF808080};
			break;
		case 0xB6:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {EG, AC, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, DH, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, AB, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, DH, EF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AB, EF, DH, 0xFF808080};
			break;
		case 0xB7:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {GH, EG, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {GH, AE, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, FH, AE, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, DH, AE, 0xFF808080};
			break;
		case 0xB8:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, AC, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EF, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, GH, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, AC, EF, 0xFF808080};
			break;
		case 0xB9:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, DH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, GH, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, GH, EF, 0xFF808080};
			break;
		case 0xBA:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BF, DH, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, AC, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, GH, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, AC, EF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {GH, EF, AC, 0xFF808080};
			break;
		case 0xBB:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, DH, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, BF, GH, 0xFF808080};
			break;
		case 0xBC:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BF, AE, GH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, GH, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, AC, GH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, GH, BD, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AC, BD, GH, 0xFF808080};
			break;
		case 0xBD:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, BF, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, AB, GH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, DH, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {DH, GH, AB, 0xFF808080};
			break;
		case 0xBE:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, AE, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, GH, FH, 0xFF808080};
			break;
		case 0xBF:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {FH, DH, GH, 0xFF808080};
			break;
		case 0xC0:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {EG, DH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, DH, EG, 0xFF808080};
			break;
		case 0xC1:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, DH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CG, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, AE, AB, 0xFF808080};
			break;
		case 0xC2:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, EG, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, BD, AB, 0xFF808080};
			break;
		case 0xC3:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {FH, CG, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, EG, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AC, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, AE, BF, 0xFF808080};
			break;
		case 0xC4:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, BF, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CG, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, DH, BF, 0xFF808080};
			break;
		case 0xC5:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, EF, EG, 0xFF808080};
			break;
		case 0xC6:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, CG, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, EF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AB, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, EG, CG, 0xFF808080};
			break;
		case 0xC7:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {CG, DH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, EF, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, BD, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, EF, AC, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {BD, AC, EF, 0xFF808080};
			break;
		case 0xC8:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, DH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AE, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, CG, DH, 0xFF808080};
			break;
		case 0xC9:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, EF, AB, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, DH, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, CG, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, EF, DH, 0xFF808080};
			break;
		case 0xCA:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BD, AB, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, AE, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, FH, EF, 0xFF808080};
			break;
		case 0xCB:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BD, AC, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, EF, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, CG, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, EF, DH, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {CG, DH, EF, 0xFF808080};
			break;
		case 0xCC:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, AE, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, CG, DH, 0xFF808080};
			break;
		case 0xCD:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, CG, BF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CG, DH, 0xFF808080};
			break;
		case 0xCE:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BD, AB, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, AE, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, AE, CG, 0xFF808080};
			break;
		case 0xCF:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, AC, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, BD, CG, 0xFF808080};
			break;
		case 0xD0:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, AC, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, FH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, EG, AC, 0xFF808080};
			break;
		case 0xD1:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, AB, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EG, AB, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {DH, FH, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EG, AE, AB, 0xFF808080};
			break;
		case 0xD2:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CD, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, FH, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {FH, CD, DH, 0xFF808080};
			break;
		case 0xD3:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {FH, EG, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, CD, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, AE, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, CD, BF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AE, BF, CD, 0xFF808080};
			break;
		case 0xD4:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, DH, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AC, DH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, EG, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, DH, AC, 0xFF808080};
			break;
		case 0xD5:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AB, CD, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, EG, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, DH, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, EG, BF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {DH, BF, EG, 0xFF808080};
			break;
		case 0xD6:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AB, EF, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, DH, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, EG, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, DH, AC, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EG, AC, DH, 0xFF808080};
			break;
		case 0xD7:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, CD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, EG, AE, 0xFF808080};
			break;
		case 0xD8:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, DH, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, DH, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, CD, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, AC, CD, 0xFF808080};
			break;
		case 0xD9:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {DH, FH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EF, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CD, EF, AB, 0xFF808080};
			break;
		case 0xDA:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AE, FH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, DH, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, AC, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CD, DH, AC, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AB, BF, BD, 0xFF808080};
			break;
		case 0xDB:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {DH, FH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {DH, EF, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, BD, EF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, CD, EF, 0xFF808080};
			break;
		case 0xDC:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AC, CD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, DH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AE, DH, BF, 0xFF808080};
			break;
		case 0xDD:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, CD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, AB, DH, 0xFF808080};
			break;
		case 0xDE:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AC, CD, DH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, DH, AE, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, AB, DH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AB, AE, DH, 0xFF808080};
			break;
		case 0xDF:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {BD, CD, DH, 0xFF808080};
			break;
		case 0xE0:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, EG, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, FH, EG, 0xFF808080};
			break;
		case 0xE1:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BD, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, FH, EG, 0xFF808080};
			break;
		case 0xE2:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {BF, FH, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EG, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, CD, AB, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, CD, EG, 0xFF808080};
			break;
		case 0xE3:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AE, BF, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, CD, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, FH, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, CD, EG, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {FH, EG, CD, 0xFF808080};
			break;
		case 0xE4:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, EG, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, EG, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EF, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BD, BF, EF, 0xFF808080};
			break;
		case 0xE5:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BD, CG, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, EG, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, BF, EG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, EG, BF, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {AB, AC, AE, 0xFF808080};
			break;
		case 0xE6:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EG, CG, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, CD, AB, 0xFF808080};
			break;
		case 0xE7:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EG, CG, CD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, CD, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, AE, CD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AE, EF, CD, 0xFF808080};
			break;
		case 0xE8:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, BD, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, CG, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EF, AE, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {CG, CD, BD, 0xFF808080};
			break;
		case 0xE9:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {BD, FH, CG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, CG, CD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, EF, CG, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, CG, AB, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {EF, AB, CG, 0xFF808080};
			break;
		case 0xEA:
			*tri_count = 5;
			*tri_list = malloc(sizeof(struct triangle_t) * 5);
			(*tri_list)[0] = (struct triangle_t) {AE, CG, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, FH, EF, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, CD, FH, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, FH, AB, 0xFF808080};
			(*tri_list)[4] = (struct triangle_t) {CD, AB, FH, 0xFF808080};
			break;
		case 0xEB:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, FH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, CG, CD, 0xFF808080};
			break;
		case 0xEC:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {CD, BD, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {CG, BF, AE, 0xFF808080};
			break;
		case 0xED:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {CD, BD, BF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CD, BF, CG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, AC, BF, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {AC, CG, BF, 0xFF808080};
			break;
		case 0xEE:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {CD, AB, AE, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {CG, CD, AE, 0xFF808080};
			break;
		case 0xEF:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {CD, AC, CG, 0xFF808080};
			break;
		case 0xF0:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, FH, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {FH, EG, AC, 0xFF808080};
			break;
		case 0xF1:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AE, AB, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {EG, BD, FH, 0xFF808080};
			break;
		case 0xF2:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {AB, BF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, FH, AC, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AC, FH, EG, 0xFF808080};
			break;
		case 0xF3:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AE, BF, FH, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EG, AE, FH, 0xFF808080};
			break;
		case 0xF4:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {BF, EF, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BF, EG, BD, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BD, EG, AC, 0xFF808080};
			break;
		case 0xF5:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {AE, AB, BD, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AE, BD, EG, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {BF, EF, BD, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {EF, EG, BD, 0xFF808080};
			break;
		case 0xF6:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {AB, EF, EG, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AC, AB, EG, 0xFF808080};
			break;
		case 0xF7:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AE, EF, EG, 0xFF808080};
			break;
		case 0xF8:
			*tri_count = 3;
			*tri_list = malloc(sizeof(struct triangle_t) * 3);
			(*tri_list)[0] = (struct triangle_t) {EF, AE, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AC, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {FH, AC, BD, 0xFF808080};
			break;
		case 0xF9:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BD, FH, EF, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {AB, BD, EF, 0xFF808080};
			break;
		case 0xFA:
			*tri_count = 4;
			*tri_list = malloc(sizeof(struct triangle_t) * 4);
			(*tri_list)[0] = (struct triangle_t) {EF, AE, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {EF, AC, FH, 0xFF808080};
			(*tri_list)[2] = (struct triangle_t) {AB, BF, AC, 0xFF808080};
			(*tri_list)[3] = (struct triangle_t) {BF, FH, AC, 0xFF808080};
			break;
		case 0xFB:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {BF, FH, EF, 0xFF808080};
			break;
		case 0xFC:
			*tri_count = 2;
			*tri_list = malloc(sizeof(struct triangle_t) * 2);
			(*tri_list)[0] = (struct triangle_t) {BF, AE, AC, 0xFF808080};
			(*tri_list)[1] = (struct triangle_t) {BD, BF, AC, 0xFF808080};
			break;
		case 0xFD:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AB, BD, BF, 0xFF808080};
			break;
		case 0xFE:
			*tri_count = 1;
			*tri_list = malloc(sizeof(struct triangle_t) * 1);
			(*tri_list)[0] = (struct triangle_t) {AB, AE, AC, 0xFF808080};
			break;
		case 0xFF:
			*tri_count = 0;
			*tri_list = NULL;
			break;
	}	
}




