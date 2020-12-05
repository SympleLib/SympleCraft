#pragma once

#include "SympleCraft/Render/Mesh.h"
#include "SympleCraft/World/Block.h"
#include "SympleCraft/World/Transform.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

#define CHUNK_SIZE_XZ CHUNK_SIZE_X * CHUNK_SIZE_Z

typedef struct Chunk
{
	int X, Y;
	Block*** Blocks;
	Mesh Mesh;
	Transform Transform;
} *Chunk;

void GenerateChunkMap(int width, int height);

Chunk CreateChunk(int x, int y);
void DeleteChunk(const Chunk chunk);

void GenerateChunk(const Chunk chunk);
void GenerateChunkMesh(const Chunk chunk);