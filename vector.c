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
	m->m02 += tx;
	m->m12 += ty;
}

void matrix3_scale(matrix3_t* m, float sx, float sy) {
	m->m00 *= sx;
	m->m11 *= sy;
}

void matrix3_rotate(matrix3_t* m, float a) {
	m->m00 = cosf(a);
	m->m01 = -sinf(a);
	m->m02 = 0.0f;
	m->m10 = sinf(a);
	m->m11 = cosf(a);
	m->m12 = 0.0f;
	m->m20 = 0.0f;
	m->m21 = 0.0f;
	m->m22 = 1.0f;
}

vec2_t vec2_matrix3_multiply(vec2_t a, matrix3_t m) {
	a.x = m.m00 * a.x + m.m01 * a.y + m.m02;
	a.y = m.m10 * a.x + m.m11 * a.y + m.m12;
	float w = m.m20 * a.x + m.m21 * a.y + m.m22;

	a.x = a.x / w;
	a.y = a.y / w;
	return a;
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


