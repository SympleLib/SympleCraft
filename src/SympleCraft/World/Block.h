#pragma once

typedef enum BlockType
{
	BlockType_Air,
	BlockType_Grass,
} BlockType;

typedef struct Block
{
	BlockType Type;
	int IsTransparent;
} *Block;