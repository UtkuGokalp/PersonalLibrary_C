#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;

List* CreateList();
void DestroyList(List* list);
void AddToList(List* list, void* value);
//Removes the element at the given index. Returns false if index was out of bounds.
bool RemoveFromListAtIndex(List* list, size_t index);
//Removes the first found element with the given value. Returns false if there was no such element.
bool RemoveFromList(List* list, void* value);
size_t GetListLength(const List* list);
//Returns the element at the given index. Returns NULL if index was out of bounds.
void* GetListElementAt(const List* list, size_t index);