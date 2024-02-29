// vector.c

#include "vector.h"


vec3_t vec3_add(vec3_t a, vec3_t b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

vec3_t vec3_subtract(vec3_t a, vec3_t b) {
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

matrix3_t matrix3_identity() {
	matrix3_t m = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	return m;
}

void matrix3_translate(matrix3_t* m, float tx, float ty) {

}

void matrix3_scale(matrix3_t* m, float sx, float sy) {

}

void matrix3_rotate(matrix3_t* m, float a) {

}

matrix4_t matrix4_identity() {
	matrix4_t m = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return m;
}

void matrix4_translate(matrix4_t* m, float tx, float ty, float tz) {

}

void matrix4_scale(matrix4_t* m, float sx, float sy, float sz) {

}

void matrix4_rotate(matrix4_t* m, float a) {

}


