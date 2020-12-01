#include "SympleCraft/Renderer.h"

#include <gl/glew.h>

void (*SetBackgroundColor)(float red, float green, float blue, float alpha) = glClearColor;

void Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render(const Mesh* mesh)
{
	BindMesh(mesh);
	glDrawElements(GL_TRIANGLES, mesh->vCount * 2, GL_UNSIGNED_INT, 0);
}