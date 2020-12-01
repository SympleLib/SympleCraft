#include "SympleCraft/Math/Matrix.h"

#include <malloc.h>
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

Matrix TranslateMatrix(Vector translation)
{
	Matrix matrix = CreateMatrix();

	*MatrixElement(matrix, 3, 0) = translation->x;
	*MatrixElement(matrix, 3, 1) = translation->y;
	*MatrixElement(matrix, 3, 2) = translation->z;

	return matrix;
}

Matrix RotateMatrix(float angle, Vector axis)
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

Matrix ScaleMatrix(Vector scale)
{
	Matrix matrix = CreateMatrix();

	*MatrixElement(matrix, 0, 0) = scale->x;
	*MatrixElement(matrix, 1, 1) = scale->y;
	*MatrixElement(matrix, 2, 2) = scale->z;

	return matrix;
}

Matrix TransformMatrix(Vector translation, Vector rotation, Vector scale)
{
	Matrix translationMatrix = TranslateMatrix(translation);
	Matrix rotXMatrix = RotateMatrix(rotation->x, CreateVector3(1, 0, 0));
	Matrix rotYMatrix = RotateMatrix(rotation->y, CreateVector3(0, 1, 0));
	Matrix rotZMatrix = RotateMatrix(rotation->z, CreateVector3(0, 0, 1));
	Matrix scaleMatrix = ScaleMatrix(scale);

	Matrix rotationMatrix = MultiplyMatrix(rotXMatrix, MultiplyMatrix(rotYMatrix, rotZMatrix));
	Matrix matrix = MultiplyMatrix(translationMatrix, MultiplyMatrix(rotationMatrix, scaleMatrix));
	DeleteMatrix(translationMatrix);
	DeleteMatrix(rotationMatrix);
	DeleteMatrix(scaleMatrix);
	DeleteMatrix(rotXMatrix);
	DeleteMatrix(rotYMatrix);
	DeleteMatrix(rotZMatrix);

	return matrix;
}


Matrix MultiplyMatrix(Matrix left, Matrix right)
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