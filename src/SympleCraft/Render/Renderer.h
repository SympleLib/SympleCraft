#pragma once

#include "SympleCraft/Render/Camera.h"
#include "SympleCraft/Render/Mesh.h"
#include "SympleCraft/Render/Shader.h"

extern void (*SetBackgroundColor)(float red, float green, float blue, float alpha);

void Clear();
void Render(const Mesh mesh, const Shader shader);