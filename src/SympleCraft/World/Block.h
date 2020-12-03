#pragma once

typedef enum BlockType
{
	GrassBlock
} BlockType;

typedef struct Block
{
	BlockType type;
} *Block;