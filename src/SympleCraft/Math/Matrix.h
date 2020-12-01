#pragma once

#include "SympleCraft/Math/Vector.h"

typedef float *Matrix;

Matrix CreateMatrix();
void DeleteMatrix(const Matrix matrix);

Matrix TranslateMatrix(const Vector translation);
Matrix RotateMatrix(float angle, const Vector axis);
Matrix ScaleMatrix(const Vector scale);

Matrix TransformMatrix(const Vector translation, const Vector rotation, const Vector scale);

Matrix MultiplyMatrix(const Matrix left, const Matrix right);

float* MatrixElement(Matrix matrix, unsigned int x, unsigned int y);

void PrintMatrix(const Matrix matrix);