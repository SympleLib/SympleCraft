#pragma once

typedef struct Mesh
{
	unsigned int vao, ibo;
	int vCount;
} Mesh;

Mesh* CreateMesh(const float* vertices, const float* indices, long vertexCount, long indiceCount);
void SetMesh(Mesh* mesh, const float* vertices, const float* indices, long vertexCount, long indiceCount);
void BindMesh(const Mesh* mesh);
void DeleteMesh(const Mesh* mesh);