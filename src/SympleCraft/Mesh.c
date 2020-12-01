#include "SympleCraft/Mesh.h"

#include <malloc.h>
#include <stdio.h>
#include <gl/glew.h>

Mesh* CreateMesh(const float* vertices, const float* indices, long vertexCount, long indiceCount)
{
	Mesh* mesh = malloc(sizeof(Mesh));
	if (!mesh)
		return NULL;

	mesh->vCount = vertexCount;

	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	return mesh;
}

void SetMesh(Mesh* mesh, const float* vertices, const float* indices, long vertexCount, long indiceCount)
{
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void BindMesh(const Mesh* mesh)
{
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
}

void DeleteMesh(const Mesh* mesh)
{
	glDeleteVertexArrays(1, &mesh->vao);

	glDeleteBuffers(1, &mesh->ibo);
	free(mesh);
}