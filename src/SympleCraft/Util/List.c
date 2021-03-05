#include <pch.h>
#include "SympleCraft/Util/List.h"

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

void ListPushItem(List list, const char* item)
{
	if ((list->Size + 1) * list->ElementSize > list->Capacity)
	{
		size_t newCapacity = list->Capacity + 10 * list->ElementSize;

		char* newData = malloc(newCapacity);
		assert(newData);
		memcpy_s(newData, newCapacity, list->Data, list->Capacity);
		free(list->Data);
		list->Data = newData;
		list->Capacity = newCapacity;
	}

	list->Size++;
	for (size_t i = 0; i < list->ElementSize; i++)
		list->Data[list->Size * list->ElementSize - i - 1] = item[list->ElementSize - i - 1];
}

void ListPushItems(List list, const char* item, long Count)
{
	for (size_t i = 0; i < Count; i++)
		ListPushItem(list, &item[i * list->ElementSize]);
}

void ListRemoveItem(List list, long long index)
{
	assert(list->Size);
	bool skip = false;
	for (size_t i = 0; i < list->Size; i++)
	{
		if (i == index)
		{
			skip = true;
			continue;
		}
		list->Data[i] = list->Data[i + skip];
	}
	list->Size--;
}

void ListShiftItem(List list)
{
	assert(list->Size);
	for (size_t i = 1; i < list->Size; i++)
	{
		list->Data[i - 1] = list->Data[i];
	}
	ListPopItem(list);
}

void ListPopItem(List list)
{ list->Size--; }

char* ListGetItem(const List list, long long index)
{ return &list->Data[index * list->ElementSize]; }

void ListSetItem(List list, long long index, const char* item)
{
	char* litem = ListGetItem(list, index);
	for (size_t i = 0; i < list->ElementSize; i++)
		litem[i] = item[i];
}

long long ListFindIndex(const List list, const char* item)
{
	for (size_t i = 0; i < list->Size * list->ElementSize; i += list->ElementSize)
		if (list->Data[i] == item[0])
		{
			for (size_t j = 0; j < list->ElementSize; j++)
				if (list->Data[i + j] != item[j])
					return -1;
			return i / list->ElementSize;
		}
	return -1;
}