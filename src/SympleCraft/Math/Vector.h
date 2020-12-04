#pragma once

typedef struct Vector
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		float values[4];
	};
} *Vector;

extern const Vector* const ForwardVector;
extern const Vector* const RightVector;
extern const Vector* const UpVector;

Vector CreateVector4(float x, float y, float z, float w);
Vector CreateVector3(float x, float y, float z);
Vector CreateVector2(float x, float y);
Vector CreateVector1(float v);
Vector CreateVector();
Vector CreateVectorFromVector(const Vector other);
void DeleteVector(const Vector vector);

Vector AddVector(const Vector left, const Vector right);
Vector SubVector(const Vector left, const Vector right);
Vector MulVector(const Vector vector, float val);
Vector DivVector(const Vector vector, float val);

void PrintVector(const Vector vector);
