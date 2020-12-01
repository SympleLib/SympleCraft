#pragma once

#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Math/Matrix.h"

typedef unsigned int Shader;

Shader CreateShader(const char* vertFile, const char* fragFile);
void BindShader(Shader shader);
void DeleteShader(Shader shader);

int GetUniformLocation(Shader shader, const char* name);

void SetShaderUniformi(Shader shader, const char* name, int value);
void SetShaderUniformf(Shader shader, const char* name, float value);
void SetShaderUniformVec(Shader shader, const char* name, Vector vector);
void SetShaderUniformMat(Shader shader, const char* name, Matrix matrix);