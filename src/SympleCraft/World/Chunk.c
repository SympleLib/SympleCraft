#include "SympleCraft/World/Chunk.h"

#include <malloc.h>
#include <stdio.h>

#include "SympleCraft/Math/Vector.h"
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

		for (size_t j = 0; j < CHUNK_SIZE_Y; j++)
		{
			chunk->Blocks[i][j] = malloc(CHUNK_SIZE_Z * sizeof(Block));

			if (!chunk->Blocks[i][j])
				return NULL;

			for (size_t l = 0; l < CHUNK_SIZE_Z; l++)
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

static void BuildFace(List vertices, List indices, Vector bl, Vector up, Vector right)
{
	Vector tl = AddVector(bl, up);
	Vector br = AddVector(bl, right);
	Vector trR = AddVector(tl, br);
	Vector tr = AddVector(bl, trR);

	unsigned int iStart = vertices->Size;
	unsigned int indicesToPush[6] = {
		iStart + 0, iStart + 1, iStart + 2,
		iStart + 0, iStart + 2, iStart + 3,
	};

	ListPushItems(vertices, &bl->values, 3);
	ListPushItems(vertices, &tl->values, 3);
	ListPushItems(vertices, &tr->values, 3);
	ListPushItems(vertices, &br->values, 3);

	ListPushItems(indices, &indicesToPush, 6);

	DeleteVector(tl);
	DeleteVector(br);
	DeleteVector(trR);
	DeleteVector(tr);
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
				Vector bl = CreateVector3(i, j, l);

				BuildFace(vertices, indices, bl, UpVector, RightVector);

				DeleteVector(bl);
			}
		}
	}

	SetMesh(chunk->Mesh, vertices->Data, indices->Data, vertices->Size, indices->Size / 3);

	DeleteList(vertices);
	DeleteList(indices);
}