#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList LinkedList;

LinkedList* CreateLinkedList();
bool DestroyLinkedList(LinkedList* list);

bool AddToLinkedList(LinkedList* list, void* data);
bool RemoveFromLinkedListAt(LinkedList* list, size_t index);
bool InsertIntoLinkedList(LinkedList* list, void* data, size_t index);
bool ClearLinkedList(LinkedList* list);

size_t GetLinkedListLength(const LinkedList* list);
void* GetLinkedListElementAt(const LinkedList* list, size_t index);