#include "SympleCraft/Transform.h"

#include <malloc.h>
#include <memory.h>

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