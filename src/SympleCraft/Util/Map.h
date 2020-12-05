#pragma once

#include "SympleCraft/Util/List.h"

typedef struct Map
{
	List Keys;
	List Values;
} *Map;

Map CreateMap(long long keySize, long long valSize);
void DeleteMap(const Map map);

void MapInsert(Map map, const char* key, const char* val);
void MapRemove(Map map, const char* key);

long long MapKeyIndex(Map map, const char* key);
long long MapValIndex(Map map, const char* val);