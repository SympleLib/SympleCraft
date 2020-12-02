#pragma once

#include "SympleCraft/Render/Mesh.h"

extern void (*SetBackgroundColor)(float red, float green, float blue, float alpha);

void Clear();
void Render(const Mesh mesh);