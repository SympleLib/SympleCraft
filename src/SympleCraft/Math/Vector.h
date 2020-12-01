#pragma once

typedef struct Vector
{
	union
	{
		float x, y, z, w;
		float r, g, b, a;
		float values[4];
	};
} *Vector;

Vector CreateVector4(float x, float y, float z, float w);
Vector CreateVector3(float x, float y, float z);
Vector CreateVector2(float x, float y);
Vector CreateVector1(float v);
Vector CreateVector();
void DeleteVector(const Vector vector);