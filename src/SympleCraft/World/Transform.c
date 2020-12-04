#include <pch.h>
#include "SympleCraft/World/Transform.h"

#include "SympleCraft/Math/Matrix.h"

Transform CreateTransform()
{
	Transform transform = malloc(sizeof(struct Transform));
	if (!transform)
		return NULL;

	transform->Translation = CreateVector();
	transform->Rotation = CreateVector();
	transform->Scale = CreateVector();

	return transform;
}

Transform CreateTransformFromTransform(const Transform other)
{
	Transform transform = malloc(sizeof(struct Transform));
	if (!transform)
		return NULL;

	memcpy_s(transform, sizeof(transform), other, sizeof(other));

	return transform;
}

Transform CreateTransformRef(const Vector translation, const Vector rotation, const Vector scale)
{
	Transform transform = malloc(sizeof(struct Transform));
	if (!transform)
		return NULL;

	transform->Translation = translation;
	transform->Rotation = rotation;
	transform->Scale = scale;

	return transform;
}

Transform CreateTransformVal(const Vector translation, const Vector rotation, const Vector scale)
{
	Transform transform = malloc(sizeof(struct Transform));
	if (!transform)
		return NULL;

	transform->Translation = CreateVectorFromVector(translation);
	transform->Rotation = CreateVectorFromVector(rotation);
	transform->Scale = CreateVectorFromVector(scale);

	return transform;
}

void DeleteTransform(const Transform transform)
{
	DeleteVector(transform->Translation);
	DeleteVector(transform->Rotation);
	DeleteVector(transform->Scale);
	free(transform);
}

Matrix TransformToMatrixRef(const Transform transform)
{
	Matrix matrix = TransformMatrix(transform->Translation, transform->Rotation, transform->Scale);
	DeleteTransform(transform);
	return matrix;
}

Matrix TransformToMatrix(const Transform transform)
{
	return TransformMatrix(transform->Translation, transform->Rotation, transform->Scale);
}

Matrix TransformViewMatrixRef(const Transform transform)
{
	Matrix matrix = ViewMatrix(transform->Translation, transform->Rotation);
	DeleteTransform(transform);
	return matrix;
}

Matrix TransformViewMatrix(const Transform transform)
{
	return ViewMatrix(transform->Translation, transform->Rotation);
}


Vector FindForward(const Matrix matrix)
{
	return CreateVector3(-*MatrixElement(matrix, 2, 0), -*MatrixElement(matrix, 2, 1), -*MatrixElement(matrix, 2, 2));
}

Vector FindRight(const Matrix matrix)
{
	return CreateVector3(*MatrixElement(matrix, 0, 0), *MatrixElement(matrix, 0, 1), *MatrixElement(matrix, 0, 2));
}

Vector FindUp(const Matrix matrix)
{
	return CreateVector3(*MatrixElement(matrix, 1, 0), *MatrixElement(matrix, 1, 1), *MatrixElement(matrix, 1, 2));
}