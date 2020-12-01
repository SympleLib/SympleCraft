#include "SympleCraft/Math/Vector.h"

#include <malloc.h>

Vector CreateVector()
{
	Vector vector = malloc(sizeof(Vector));
	if (!vector)
		return NULL;

	return vector;
}

Vector CreateVector4(float x, float y, float z, float w)
{
	Vector vector = CreateVector();
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->w = w;
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

void DeleteVector(const Vector vector)
{
	free(vector);
}