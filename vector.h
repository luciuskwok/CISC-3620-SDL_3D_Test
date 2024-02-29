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
} matrix3x3_t;

typedef struct {
	float m00; float m01; float m02; float m03;
	float m10; float m11; float m12; float m13;
	float m20; float m21; float m22; float m23;
	float m30; float m31; float m32; float m33;
} matrix4x4t;


// Functions


#endif