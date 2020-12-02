#pragma once

#include "SympleCraft/Math/Vector.h"

typedef float *Matrix;

Matrix CreateMatrix();
void DeleteMatrix(const Matrix matrix);

Matrix TranslateMatrix(const Vector translation);
Matrix RotateAxisMatrix(float angle, const Vector axis);
Matrix RotateMatrix(const Vector rotation);
Matrix ScaleMatrix(const Vector scale);

Matrix TransformMatrix(const Vector translation, const Vector rotation, const Vector scale);
Matrix ViewMatrix(const Vector translation, const Vector rotation);
Matrix PerspectiveMatrix(float aspect, float fov, float near, float far);
Matrix OrthoMatrix(float left, float top, float right, float bottom, float near, float far);

Matrix MultiplyMatrix(const Matrix left, const Matrix right);

float* MatrixElement(Matrix matrix, unsigned int x, unsigned int y);

void PrintMatrix(const Matrix matrix);