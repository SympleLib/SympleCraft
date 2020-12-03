#pragma once

#include "SympleCraft/Math/Vector.h"

typedef struct Transform
{
	Vector Translation, Rotation, Scale;
} *Transform;

typedef float* Matrix;

Transform CreateTransform();
Transform CreateTransformFromTransform(const Transform other);
Transform CreateTransformRef(const Vector translation, const Vector rotation, const Vector scale);
Transform CreateTransformVal(const Vector translation, const Vector rotation, const Vector scale);
void DeleteTransform(const Transform transform);

Matrix TransformViewMatrixRef(const Transform transform);
Matrix TransformToMatrixRef(const Transform transform);
Matrix TransformViewMatrix(const Transform transform);
Matrix TransformToMatrix(const Transform transform);

Vector FindForward(const Matrix matrix);
Vector FindRight(const Matrix matrix);
Vector FindUp(const Matrix matrix);