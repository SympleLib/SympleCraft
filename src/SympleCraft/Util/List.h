#pragma once

typedef struct List
{
	unsigned long long Size, ElementSize, Capacity;
	char* Data;
} *List;

List CreateList(long long elementSize);
void DeleteList(const List list);

void ListPushItem(List list, const char* item);
void ListPushItems(List list, const char* item, long Count);
void ListRemoveItem(List list, long long index);
void ListShiftItem(List list);
void ListPopItem(List list);

char* ListGetItem(const List list, long long index);
void ListSetItem(List list, long long index, const char* item);
long long ListFindIndex(const List list, const char* item);