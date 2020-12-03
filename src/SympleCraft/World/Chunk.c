#include "SympleCraft/World/Chunk.h"

#include <malloc.h>

#include "SympleCraft/Util/List.h"

Chunk CreateChunk(int x, int y)
{
	Chunk chunk = malloc(sizeof(struct Chunk));
	if (!chunk)
		return NULL;

	chunk->X = x;
	chunk->Y = y;
	chunk->Mesh = CreateMesh(NULL, NULL, 0, 0);
	chunk->Blocks = malloc(CHUNK_SIZE_X * sizeof(Block**));
	if (!chunk->Blocks)
		return NULL;

	for (size_t i = 0; i < CHUNK_SIZE_X; i++)
	{
		chunk->Blocks[i] = malloc(CHUNK_SIZE_Y * sizeof(Block*));

		if (!chunk->Blocks[i])
			return NULL;

		for (size_t j = 0; j < CHUNK_SIZE_Z; j++)
		{
			chunk->Blocks[i][j] = malloc(CHUNK_SIZE_Z * sizeof(Block));

			if (!chunk->Blocks[i][j])
				return NULL;

			for (size_t l = 0; l < CHUNK_SIZE_Y; l++)
			{
				chunk->Blocks[i][j][l] = malloc(sizeof(struct Block));

				if (!chunk->Blocks[i][j][l])
					return NULL;
			}
		}
	}

	return chunk;
}

void DeleteChunk(const Chunk chunk)
{
	for (size_t i = 0; i < CHUNK_SIZE_X; i++)
	{
		for (size_t j = 0; j < CHUNK_SIZE_Y; j++)
		{
			for (size_t l = 0; l < CHUNK_SIZE_Z; l++)
			{
				free(chunk->Blocks[i][j][l]);
			}

			free(chunk->Blocks[i][j]);
		}

		free(chunk->Blocks[i]);
	}
	free(chunk->Blocks);
	free(chunk->Mesh);
	free(chunk);
}

void GenerateChunkMesh(const Chunk chunk)
{
	List vertices = CreateList(sizeof(float));
	List indices = CreateList(sizeof(unsigned int));

	for (size_t i = 0; i < CHUNK_SIZE_X; i++)
	{
		for (size_t j = 0; j < CHUNK_SIZE_Y; j++)
		{
			for (size_t l = 0; l < CHUNK_SIZE_Z; l++)
			{

			}
		}
	}

	SetMesh(chunk->Mesh, vertices->Data, indices->Data, vertices->Size, indices->Size / 3);

	DeleteList(vertices);
	DeleteList(indices);
}