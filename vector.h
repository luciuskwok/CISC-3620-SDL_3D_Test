// vector.h

#ifndef VECTOR_H
#define VECTOR_H

// Basic vector types

typedef struct {
	float x;
	float y;
} vec2_t;

typedef struct {
	float x;
	float y;
	float z;
} vec3_t;

// Matrix types

typedef struct {
	float m00; float m01; float m02;
	float m10; float m11; float m12;
	float m20; float m21; float m22;
} matrix3_t;

typedef struct {
	float m00; float m01; float m02; float m03;
	float m10; float m11; float m12; float m13;
	float m20; float m21; float m22; float m23;
	float m30; float m31; float m32; float m33;
} matrix4_t;


// Functions

vec2_t vec2_rotate(vec2_t p, float a);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_subtract(vec3_t a, vec3_t b);

matrix3_t matrix3_identity();
void matrix3_translate(matrix3_t *m, float tx, float ty);
void matrix3_scale(matrix3_t *m, float sx, float sy);
void matrix3_rotate(matrix3_t *m, float a);
matrix3_t matrix3_multiply(matrix3_t* a, matrix3_t* b);
vec2_t vec2_matrix3_multiply(vec2_t a, matrix3_t m);

matrix4_t matrix4_identity();
void matrix4_translate(matrix4_t *m, float tx, float ty, float tz);
void matrix4_scale(matrix4_t *m, float sx, float sy, float sz);
void matrix4_rotate(matrix4_t *m, float a);

#endif