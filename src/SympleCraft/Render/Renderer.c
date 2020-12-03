#include "SympleCraft/Render/Renderer.h"

#include <gl/glew.h>

static Vector faceCol, lineCol;

void (*SetBackgroundColor)(float red, float green, float blue, float alpha) = glClearColor;

void Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render(const Mesh mesh, const Shader shader)
{
	if (!faceCol)
		faceCol = CreateVector3(1, 1, 1);
	if (!lineCol)
		lineCol = CreateVector3(0, 1, 0);

	SetShaderUniformVec(shader, "uCol", faceCol);

	BindMesh(mesh);
	glDrawElements(GL_TRIANGLES, mesh->tCount * 3, GL_UNSIGNED_INT, 0);

	SetShaderUniformVec(shader, "uCol", lineCol);

	glDrawElements(GL_LINE_STRIP, mesh->tCount * 3, GL_UNSIGNED_INT, 0);
}