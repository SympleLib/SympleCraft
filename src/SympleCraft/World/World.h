#pragma once

#include "SympleCraft/Util/Map.h"
#include "SympleCraft/Render/Shader.h"

typedef struct World
{
	Map Chunks;
} *World;

World CreateWorld(long long cx, long long cy);
void DeleteWorld(const World world);

void RenderWorld(const World world, const Shader shader);
void WorldGenerateChunk(World world, int x, int y);