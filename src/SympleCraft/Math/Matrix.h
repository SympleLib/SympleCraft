#pragma once

#include "SympleCraft/Math/Vector.h"

typedef float *Matrix;

Matrix CreateMatrix();
void DeleteMatrix(const Matrix matrix);

Matrix TranslateMatrix(Vector translation);
Matrix RotateMatrix(float angle, Vector axis);
Matrix ScaleMatrix(Vector scale);

Matrix TransformMatrix(Vector translation, Vector rotation, Vector scale);

Matrix MultiplyMatrix(Matrix left, Matrix right);

float* MatrixElement(Matrix matrix, unsigned int x, unsigned int y);