#include <pch.h>
#include "SympleCraft/Render/Mesh.h"

#include <gl/glew.h>

static GLuint StoreBuffer(const float* buffer, size_t count, int index, int size)
{
	printf("Buffer: %p %zd, at %i, %d\n", buffer, count, index, size);

	GLuint bufferID = 0;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
	assert(bufferID);
	return bufferID;
}

Mesh CreateMesh(const float* vertices, const float* indices, long long vertexCount, long long triangleCount)
{
	Mesh mesh = malloc(sizeof(struct Mesh));
	assert(mesh);

	mesh->tCount = triangleCount;

	if (!(vertices && indices))
		return mesh;

	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	mesh->vbo = StoreBuffer(vertices, vertexCount * 3, 0, 3);

	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleCount * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	return mesh;
}

void SetMesh(Mesh mesh, const float* vertices, const float* indices, long long vertexCount, long long triangleCount)
{
	if (mesh->vao)
	{
		glDeleteVertexArrays(1, &mesh->vao);

		glDeleteBuffers(1, &mesh->vbo);
		glDeleteBuffers(1, &mesh->ibo);
	}

	mesh->tCount = triangleCount;

	if (!(vertices && indices))
		return;

	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	mesh->vbo = StoreBuffer(vertices, vertexCount * 3, 0, 3);

	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleCount * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void BindMesh(const Mesh mesh)
{
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
}

void DeleteMesh(const Mesh mesh)
{
	glDeleteVertexArrays(1, &mesh->vao);

	glDeleteBuffers(1, &mesh->ibo);
	free(mesh);
}