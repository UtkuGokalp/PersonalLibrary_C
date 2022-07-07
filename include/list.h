#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;

List* CreateList();
//Frees the given list. Nothing is done if the list was NULL.
void DestroyList(List* list);
//Adds the given item to the list. Nothing is done if list was NULL.
void AddToList(List* list, void* value);
//Removes the element at the given index. Returns false in case of any error.
bool RemoveFromListAtIndex(List* list, size_t index);
//Removes the first found element with the given value. Returns false in case of any error.
bool RemoveFromList(List* list, void* value);
//Returns the length of the list. Returns -1 if list was NULL.
size_t GetListLength(const List* list);
//Returns the element at the given index. Returns NULL if index was out of bounds or if the list was NULL.
void* GetListElementAt(const List* list, size_t index);
