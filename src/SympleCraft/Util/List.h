#pragma once

typedef struct List
{
	long long Size, Capacity, ElementSize;
	char* Data;
} *List;

List CreateList(long long elementSize);
void DeleteList(const List list);

void ListPushItem(const List list, char* item, long size);
void ListPopItem(const List list);