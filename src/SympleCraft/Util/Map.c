#include <pch.h>
#include "SympleCraft/Util/Map.h"

Map CreateMap(long long keySize, long long valSize)
{
	Map map = malloc(sizeof(struct Map));
	assert(map);

	map->Keys = CreateList(keySize);
	map->Values = CreateList(valSize);

	return map;
}

void DeleteMap(const Map map)
{
	DeleteList(map->Keys);
	DeleteList(map->Values);
	free(map);
}

void MapInsert(Map map, const char* key, const char* val)
{
	size_t index = ListFindIndex(map->Keys, key);
	if (index == -1)
	{
		ListPushItem(map->Keys, key);
		ListPushItem(map->Values, val);
	}
	else
		ListSetItem(map->Values, index, val);
}

void MapRemove(Map map, const char* key)
{
	size_t index = ListFindIndex(map->Keys, key);
	assert(index != -1);
	ListRemoveItem(map->Keys, index);
	ListRemoveItem(map->Values, index);
}

long long MapKeyIndex(Map map, const char* key)
{
	return ListFindIndex(map->Keys, key);
}

long long MapValIndex(Map map, const char* val)
{
	return ListFindIndex(map->Values, val);
}