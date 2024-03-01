// vector.c

#include "vector.h"
#include <math.h>


vec2_t vec2_rotate(vec2_t p, float a) {
	vec2_t q;
	q.x = p.x * cosf(a) - p.y * sinf(a);
	q.y = p.x * sinf(a) + p.y * cosf(a);
	return q;
}

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

void mat3_get_identity(mat3_t m) {
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
}

void mat3_translate(mat3_t m, float tx, float ty) {
	mat3_t n = {
		1, 0, tx,
		0, 1, ty,
		0, 0, 1
	};
	mat3_multiply(m, n, m);
}

void mat3_scale(mat3_t m, float sx, float sy) {
	mat3_t n = {
		sx, 0, 0,
		0, sy, 0,
		0, 0, 1
	};
	mat3_multiply(m, n, m);
}

void mat3_rotate(mat3_t m, float a) {
	mat3_t n = {
		cosf(a), -sinf(a), 0,
		sinf(a), cos(a), 0,
		0, 0, 1
	};
	mat3_multiply(m, n, m);
}

void mat3_multiply(mat3_t a, mat3_t b, mat3_t result) {
	// Store results in a temporary matrix before copying to results
	mat3_t tmp;

	// Store calculations in tmp first
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				tmp[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	// Copy results from tmp to result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = tmp[i][j];
		}
	}
}

vec2_t vec2_mat3_multiply(vec2_t a, mat3_t m) {
	vec2_t b;
	float w;
	b.x = m[0][0] * a.x + m[0][1] * a.y + m[0][2];
	b.y = m[1][0] * a.x + m[1][1] * a.y + m[1][2];
	w = m[2][0] * a.x + m[2][1] * a.y + m[2][2];
	return b;
}


matrix3_struct_t matrix3_identity() {
	matrix3_struct_t m = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	return m;
}

void matrix3_translate(matrix3_struct_t* m, float tx, float ty) {
	m->m02 += tx;
	m->m12 += ty;
}

void matrix3_scale(matrix3_struct_t* m, float sx, float sy) {
	m->m00 *= sx;
	m->m11 *= sy;
}

void matrix3_rotate(matrix3_struct_t* m, float a) {
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

vec2_t vec2_matrix3_multiply(vec2_t a, matrix3_struct_t m) {
	vec2_t b;
	b.x = m.m00 * a.x + m.m01 * a.y + m.m02;
	b.y = m.m10 * a.x + m.m11 * a.y + m.m12;
	float w = m.m20 * a.x + m.m21 * a.y + m.m22;

	//b.x = b.x / w;
	//b.y = b.y / w;
	return b;
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

vec3_t vec3_matrix4_multiply(vec3_t a, matrix4_t m) {
	vec3_t b;
	b.x = m.m00 * a.x + m.m01 * a.y + m.m02 * a.z + m.m03;
	b.y = m.m10 * a.x + m.m11 * a.y + m.m12 * a.z + m.m13;
	b.z = m.m20 * a.x + m.m21 * a.y + m.m22 * a.z + m.m23;
	float w = m.m30 * a.x + m.m31 * a.y + m.m32 * a.z + m.m33;

	//b.x = b.x / w;
	//b.y = b.y / w;
	//b.z = b.z / w;
	return b;
}


