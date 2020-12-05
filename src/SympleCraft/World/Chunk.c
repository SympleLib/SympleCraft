#include <pch.h>
#include "SympleCraft/World/Chunk.h"

#include <gl/glew.h>

#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Util/List.h"
#include "SympleCraft/Util/Noise.h"

static float** RandMap = NULL;
static float** ChunkMap = NULL;

void GenerateChunkMap(long long width, long long height)
{
	float** newRandMap = realloc(RandMap, width * CHUNK_SIZE_X * sizeof(float*));
	assert(newRandMap);
	free(RandMap);
	RandMap = newRandMap;
	assert(RandMap);

	float** newChunkMap = realloc(ChunkMap, width * CHUNK_SIZE_X * sizeof(float*));
	assert(newChunkMap);
	free(ChunkMap);
	ChunkMap = newChunkMap;
	assert(ChunkMap);

	srand(time(0));
	for (size_t i = 0; i < width * CHUNK_SIZE_X; i++)
	{
		RandMap[i] = malloc(height * CHUNK_SIZE_Z * sizeof(float));
		assert(RandMap[i]);

		ChunkMap[i] = malloc(height * CHUNK_SIZE_Z * sizeof(float));
		assert(ChunkMap[i]);

		for (size_t j = 0; j < height * CHUNK_SIZE_Z; j++)
			RandMap[i][j] = (float)rand() / (float)RAND_MAX;
	}

	GetNoise(width * CHUNK_SIZE_X, height * CHUNK_SIZE_Z, RandMap, 0, 0, 2, 0.00002, ChunkMap);
}

Chunk CreateChunk(int x, int y)
{
	Chunk chunk = malloc(sizeof(struct Chunk));
	if (!chunk)
		return NULL;

	chunk->X = x;
	chunk->Y = y;
	chunk->Mesh = CreateMesh(NULL, NULL, 0, 0);
	chunk->Transform = CreateTransformRef(CreateVector3(x * CHUNK_SIZE_X, 0, y * CHUNK_SIZE_Z), CreateVector(), CreateVector1(1));
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

void GenerateChunk(const Chunk chunk)
{
	for (int z = 0; z < CHUNK_SIZE_Z; z++)
		for (int x = 0; x < CHUNK_SIZE_X; x++)
		{
			int y = (int)(ChunkMap[x + chunk->X * CHUNK_SIZE_X][z + chunk->Y * CHUNK_SIZE_Z] * CHUNK_SIZE_Y);
			for (int by = 0; by < CHUNK_SIZE_Y; by++)
			{
				if (by > y)
				{
					chunk->Blocks[x][by][z]->Type = BlockType_Air;
					chunk->Blocks[x][by][z]->IsTransparent = true;
				}
				else
				{
					chunk->Blocks[x][by][z]->Type = BlockType_Grass;
					chunk->Blocks[x][by][z]->IsTransparent = false;
				}
			}
		}
}

static void BuildFace(List vertices, List indices, Vector bl, Vector up, Vector right)
{
	Vector tl = AddVector(bl, up);
	Vector br = AddVector(bl, right);
	Vector trR = AddVector(up, right);
	Vector tr = AddVector(bl, trR);

	unsigned int iStart = vertices->Size / 3;
	unsigned int indicesToPush[6] = {
		iStart + 0, iStart + 1, iStart + 2,
		iStart + 0, iStart + 2, iStart + 3,
	};

	ListPushItems(indices, &indicesToPush, 6);

	ListPushItems(vertices, &bl->values, 3);
	ListPushItems(vertices, &tl->values, 3);
	ListPushItems(vertices, &tr->values, 3);
	ListPushItems(vertices, &br->values, 3);

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
				if (!chunk->Blocks[i][j][l]->IsTransparent)
				{
					Vector bl = CreateVector3(i, j, l);
					Vector ibl = CreateVector3(i + 1, j + 1, l + 1);

					if (l == 0 || chunk->Blocks[i][j][l - 1]->IsTransparent)
						BuildFace(vertices, indices, bl, RightVector, UpVector);

					if (i == 0 || chunk->Blocks[i - 1][j][l]->IsTransparent)
						BuildFace(vertices, indices, bl, UpVector, ForwardVector);

					if (j == 0 || chunk->Blocks[i][j - 1][l]->IsTransparent)
						BuildFace(vertices, indices, bl, ForwardVector, RightVector);

					if (j == CHUNK_SIZE_Y - 1 || chunk->Blocks[i][j + 1][l]->IsTransparent)
						BuildFace(vertices, indices, ibl, LeftVector, BackwardVector);

					if (i == CHUNK_SIZE_X - 1 || chunk->Blocks[i + 1][j][l]->IsTransparent)
						BuildFace(vertices, indices, ibl, BackwardVector, DownVector);

					if (l == CHUNK_SIZE_Z - 1 || chunk->Blocks[i][j][l + 1]->IsTransparent)
						BuildFace(vertices, indices, ibl, DownVector, LeftVector);

					DeleteVector(ibl);
					DeleteVector(bl);
				}
			}
		}
	}

	SetMesh(chunk->Mesh, vertices->Data, indices->Data, vertices->Size / 3, indices->Size / 3);

	DeleteList(vertices);
	DeleteList(indices);
}