#include <pch.h>
#include "SympleCraft/Math/Vector.h"

#include <math.h>

const Vector const ZeroVector = &(struct Vector) { 0, 0, 0, 0 };
const Vector const OneVector = &(struct Vector) { 1, 1, 1, 1 };
const Vector const XOneVector = &(struct Vector) { -1, -1, -1, -1 };

const Vector const ForwardVector = &(struct Vector) { 0, 0, 1, 1 };
const Vector const RightVector = &(struct Vector) { 1, 0, 0, 1 };
const Vector const UpVector = &(struct Vector) { 0, 1, 0, 1 };

const Vector const BackwardVector = &(struct Vector) { 0, 0, -1, 1 };
const Vector const LeftVector = &(struct Vector) { -1, 0, 0, 1 };
const Vector const DownVector = &(struct Vector) { 0, -1, 0, 1 };

Vector CreateVector4(float x, float y, float z, float w)
{
	Vector vector = malloc(sizeof(struct Vector));
	if (!vector)
		return NULL;

	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->w = w;

	return vector;
}
Vector CreateVector3(float x, float y, float z)
{
	return CreateVector4(x, y, z, 1);
}
Vector CreateVector2(float x, float y)
{
	return CreateVector4(x, y, 1, 1);
}
Vector CreateVector1(float v)
{
	return CreateVector4(v, v, v, v);
}

Vector CreateVector()
{
	Vector vector = malloc(sizeof(struct Vector));
	if (!vector)
		return NULL;

	vector->values[0] = 0;
	vector->values[1] = 0;
	vector->values[2] = 0;
	vector->values[3] = 0;

	return vector;
}

Vector CreateVectorFromVector(const Vector other)
{
	Vector vector = malloc(sizeof(struct Vector));
	if (!vector)
		return NULL;

	memcpy_s(vector, sizeof(vector), other, sizeof(other));

	return vector;
}

void DeleteVector(const Vector vector)
{
	free(vector);
}

Vector AddVector(const Vector left, const Vector right)
{
	return CreateVector4(left->x + right->x, left->y + right->y, left->z + right->z, left->w + right->w);
}

Vector SubVector(const Vector left, const Vector right)
{
	return CreateVector4(left->x - right->x, left->y - right->y, left->z - right->z, left->w - right->w);
}

Vector MulVector(const Vector vector, float val)
{
	return CreateVector4(vector->x * val, vector->y * val, vector->z * val, vector->w * val);
}

Vector DivVector(const Vector vector, float val)
{
	return CreateVector4(vector->x / val, vector->y / val, vector->z / val, vector->w / val);
}

float VectorMag(const Vector vector)
{
	return sqrtf(VectorMagSqr(vector));
}

float VectorMagSqr(const Vector vector)
{
	return vector->x * vector->x + vector->y * vector->y + vector->z * vector->z + vector->w * vector->w;
}

void NormalizeVector(Vector vector)
{
	float mag = VectorMag(vector);
	vector->x /= mag;
	vector->y /= mag;
	vector->z /= mag;
	vector->w /= mag;
}

Vector NormalizedVector(const Vector vector)
{
	return DivVector(vector, VectorMag(vector));
}

void PrintVector(const Vector vector)
{
	printf("{ x: %G, y: %G, z: %G, w: %G }\n", vector->values[0], vector->values[1], vector->values[2], vector->values[3]);
}