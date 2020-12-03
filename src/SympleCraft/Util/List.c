#include "SympleCraft/Util/List.h"

#include <malloc.h>

List CreateList(long long elementSize)
{
	List list = malloc(sizeof(struct List));
	if (!list)
		return NULL;

	list->Size = 0;
	list->Capacity = 0;
	list->ElementSize = elementSize;
	list->Data = NULL;

	return list;
}

void DeleteList(const List list)
{
	free(list->Data);
	free(list);
}

void ListPushItem(const List list, char* item)
{
	if (list->Size + list->ElementSize > list->Capacity)
	{
		char* newData = malloc(list->Capacity + 10 * list->ElementSize);
		if (!newData)
			return;
		for (long long i = 0; i < list->Capacity; i++)
			newData[i] = list->Data[i];
		free(list->Data);
		list->Data = newData;
		list->Capacity += 10 * list->ElementSize;
	}

	for (long long i = 0; i < list->ElementSize; i++)
	{
		list->Data[(list->Size - 1) * list->ElementSize + i] = item[i];
	}
	list->Size++;
}

void ListPopItem(const List list)
{
	list->Size--;
}