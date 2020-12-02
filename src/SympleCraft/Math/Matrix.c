#include "SympleCraft/Math/Matrix.h"

#include <malloc.h>
#include <stdio.h>
#include <math.h>

Matrix CreateMatrix()
{
	Matrix matrix = malloc(4 * 4 * sizeof(float));
	if (!matrix)
		return NULL;

	for (unsigned int i = 0; i < 16; i++)
		matrix[i] = 0;
	*MatrixElement(matrix, 0, 0) = 1;
	*MatrixElement(matrix, 1, 1) = 1;
	*MatrixElement(matrix, 2, 2) = 1;
	*MatrixElement(matrix, 3, 3) = 1;

	return matrix;
}

void DeleteMatrix(const Matrix matrix)
{
	free(matrix);
}

Matrix TranslateMatrix(const Vector translation)
{
	Matrix matrix = CreateMatrix();

	*MatrixElement(matrix, 3, 0) = translation->x;
	*MatrixElement(matrix, 3, 1) = translation->y;
	*MatrixElement(matrix, 3, 2) = translation->z;

	return matrix;
}

Matrix RotateAxisMatrix(float angle, const Vector axis)
{
	Matrix matrix = CreateMatrix();

	float cos = cosf(angle);
	float sin = sinf(angle);
	float c = 1 - cos;

	*MatrixElement(matrix, 0, 0) = cos + axis->x * axis->x * c;
	*MatrixElement(matrix, 0, 1) = axis->x * axis->y * c - axis->z * sin;
	*MatrixElement(matrix, 0, 2) = axis->x * axis->z * c + axis->y * sin;
	*MatrixElement(matrix, 1, 0) = axis->y * axis->x * c + axis->z * sin;
	*MatrixElement(matrix, 1, 1) = cos + axis->y * axis->y * c;
	*MatrixElement(matrix, 1, 2) = axis->y * axis->z * c - axis->x * sin;
	*MatrixElement(matrix, 2, 0) = axis->z * axis->x * c - axis->y * sin;
	*MatrixElement(matrix, 2, 1) = axis->z * axis->y * c + axis->x * sin;
	*MatrixElement(matrix, 2, 2) = cos + axis->z * axis->z * c;

	return matrix;
}

Matrix RotateMatrix(const Vector rotation)
{
	Matrix rotXMatrix = RotateAxisMatrix(rotation->x, CreateVector3(1, 0, 0));
	Matrix rotYMatrix = RotateAxisMatrix(rotation->y, CreateVector3(0, 1, 0));
	Matrix rotZMatrix = RotateAxisMatrix(rotation->z, CreateVector3(0, 0, 1));

	Matrix matrix = MultiplyMatrix(rotXMatrix, MultiplyMatrix(rotYMatrix, rotZMatrix));
	DeleteMatrix(rotXMatrix);
	DeleteMatrix(rotYMatrix);
	DeleteMatrix(rotZMatrix);

	return matrix;
}

Matrix ScaleMatrix(const Vector scale)
{
	Matrix matrix = CreateMatrix();

	*MatrixElement(matrix, 0, 0) = scale->x;
	*MatrixElement(matrix, 1, 1) = scale->y;
	*MatrixElement(matrix, 2, 2) = scale->z;

	return matrix;
}

Matrix TransformMatrix(const Vector translation, const Vector rotation, const Vector scale)
{
	Matrix translationMatrix = TranslateMatrix(translation);
	Matrix rotationMatrix = RotateMatrix(rotation);
	Matrix scaleMatrix = ScaleMatrix(scale);

	Matrix matrix = MultiplyMatrix(translationMatrix, MultiplyMatrix(rotationMatrix, scaleMatrix));
	DeleteMatrix(translationMatrix);
	DeleteMatrix(rotationMatrix);
	DeleteMatrix(scaleMatrix);

	return matrix;
}

Matrix ViewMatrix(const Vector translation, const Vector rotation)
{
	Vector negative = CreateVector3(-translation->x, -translation->y, -translation->z);
	Matrix translationMatrix = TranslateMatrix(translation, rotation);
	DeleteVector(negative);
	
	Matrix rotationMatrix = RotateMatrix(rotation);
	Matrix matrix = MultiplyMatrix(translationMatrix, rotationMatrix);

	return matrix;
}

Matrix PerspectiveMatrix(float aspect, float fov, float near, float far)
{
	Matrix matrix = CreateMatrix();

	float range = far - near;
	float tan = tanf(fov / 2);

	*MatrixElement(matrix, 0, 0) = 1 / (aspect * tan);
	*MatrixElement(matrix, 1, 1) = 1 / tan;
	*MatrixElement(matrix, 2, 2) = -((far + near) / range);
	*MatrixElement(matrix, 2, 3) = -1;
	*MatrixElement(matrix, 3, 2) = -((2 * far * near) / range);
	*MatrixElement(matrix, 3, 3) = 0;

	return matrix;
}

Matrix OrthoMatrix(float left, float top, float right, float bottom, float near, float far)
{
	Matrix matrix = CreateMatrix();

	float range = far - near;

	*MatrixElement(matrix, 0, 0) = 2 / (right - left);
	*MatrixElement(matrix, 1, 1) = 2 / (top - bottom);
	*MatrixElement(matrix, 2, 2) = -2 / range;
	*MatrixElement(matrix, 3, 0) = -(right + left) / (right - left);
	*MatrixElement(matrix, 3, 1) = -(top + bottom) / (top - bottom);
	*MatrixElement(matrix, 3, 2) = -1;

	return matrix;
}


Matrix MultiplyMatrix(const Matrix left, const Matrix right)
{
	Matrix matrix = CreateMatrix();

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			*MatrixElement(matrix, i, j) =
				*MatrixElement(left, i, 0) * *MatrixElement(right, 0, j) +
				*MatrixElement(left, i, 1) * *MatrixElement(right, 1, j) +
				*MatrixElement(left, i, 2) * *MatrixElement(right, 2, j) +
				*MatrixElement(left, i, 3) * *MatrixElement(right, 3, j);
	return matrix;
}

float* MatrixElement(Matrix matrix, unsigned int x, unsigned int y)
{
	return &matrix[x + y * 4];
}


void PrintMatrix(const Matrix matrix)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		printf("%G", *MatrixElement(matrix, i, 0));
		for (unsigned int j = 1; j < 4; j++)
			printf(", %G", *MatrixElement(matrix, i, j));
		printf("\n");
	}
}