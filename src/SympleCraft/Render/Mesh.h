#pragma once

typedef struct Mesh
{
	unsigned int vao, vbo, ibo;
	int tCount;
} *Mesh;

Mesh CreateMesh(const float* vertices, const float* indices, long long vertexCount, long long triangleCount);
void SetMesh(Mesh mesh, const float* vertices, const float* indices, long long vertexCount, long long triangleCount);
void BindMesh(const Mesh mesh);
void DeleteMesh(const Mesh mesh);