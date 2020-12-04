#include "SympleCraft/Util/List.h"

#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>

List CreateList(long long elementSize)
{
	List list = malloc(sizeof(struct List));
	assert(list);

	list->Size = 0;
	list->Capacity = 0;
	list->ElementSize = elementSize;
	list->Data = malloc(0);

	return list;
}

void DeleteList(const List list)
{
	free(list->Data);
	free(list);
}

void ListPushItem(const List list, const char* item)
{
	if (list->Size + list->ElementSize > list->Capacity)
	{
		size_t newCapacity = list->Capacity + 10 * list->ElementSize;

		printf("Size: %zd, Wants: %zd, Needs: %zd, Has %zd!\n", list->Size, list->Size + list->ElementSize, newCapacity, list->Capacity);
		char* newData = malloc(newCapacity);
		assert(newData);
		memcpy_s(newData, newCapacity, list->Data, list->Capacity);
		free(list->Data);
		list->Data = newData;
		list->Capacity = newCapacity;
	}

	list->Size++;
	printf("Element Size: %zd\n", list->ElementSize);
	for (size_t i = 0; i < list->ElementSize; i++)
	{
		printf("Moving %zd to %zd\n", list->ElementSize - i - 1, list->Size * list->ElementSize - i - 1);
		list->Data[list->Size * list->ElementSize - i - 1] = item[list->ElementSize - i - 1];
	}
}

void ListPushItems(const List list, const char* item, long Count)
{
	for (size_t i = 0; i < Count; i++)
		ListPushItem(list, &item[i * list->ElementSize]);
}

void ListPopItem(const List list)
{
	list->Size--;
}