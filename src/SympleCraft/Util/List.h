#pragma once

typedef struct List
{
	unsigned long long Size, ElementSize, Capacity;
	char* Data;
} *List;

List CreateList(long long elementSize);
void DeleteList(const List list);

void ListPushItem(const List list, const char* item);
void ListPushItems(const List list, const char* item, long Count);
void ListPopItem(const List list);