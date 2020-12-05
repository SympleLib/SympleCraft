#include <pch.h>
#include "SympleCraft/World/World.h"

#include "SympleCraft/Render/Renderer.h"
#include "SympleCraft/World/Chunk.h"

World CreateWorld(long long cx, long long cy)
{
	World world = malloc(sizeof(struct World));
	assert(world);

	GenerateChunkMap(cx, cy);
	world->Chunks = CreateMap(sizeof(struct Vector), sizeof(struct Chunk));

	return world;
}

void DeleteWorld(const World world)
{
	for (size_t i = 0; i < world->Chunks->Values->Size; i++)
		DeleteChunk(ListGetItem(world->Chunks->Values, i));
	DeleteMap(world->Chunks);
	free(world);
}

void RenderWorld(const World world, const Shader shader)
{
	for (size_t i = 0; i < world->Chunks->Values->Size; i++)
	{
		Chunk chunk = (Chunk)ListGetItem(world->Chunks->Values, i);
		Matrix model = TransformToMatrix(chunk->Transform);
		SetShaderUniformMat(shader, "uModel", model);
		Render(chunk->Mesh, shader);
		DeleteMatrix(model);
	}
}

void WorldGenerateChunk(World world, int x, int y)
{
	Vector chunkPosVec = CreateVector2(x, y);
	Chunk chunk = CreateChunk(x, y);
	GenerateChunk(chunk);
	GenerateChunkMesh(chunk);
	MapInsert(world->Chunks, chunkPosVec, chunk);
	DeleteVector(chunkPosVec);
}