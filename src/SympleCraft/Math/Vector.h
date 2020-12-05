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

extern const Vector const ZeroVector;
extern const Vector const OneVector;
extern const Vector const XOneVector;

extern const Vector const ForwardVector;
extern const Vector const RightVector;
extern const Vector const UpVector;

extern const Vector const BackwardVector;
extern const Vector const LeftVector;
extern const Vector const DownVector;

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

float VectorMag(const Vector vector);
float VectorMagSqr(const Vector vector);
void NormalizeVector(Vector vector);
Vector NormalizedVector(const Vector vector);

void PrintVector(const Vector vector);
