#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList LinkedList;

LinkedList* CreateLinkedList();
bool DestroyLinkedList(LinkedList* list);

bool AddToLinkedList(LinkedList* list, const void* data);
bool RemoveFromLinkedListAt(LinkedList* list, size_t index);

size_t GetLinkedListLength(const LinkedList* list);
void* GetLinkedListElementAt(const LinkedList* list, size_t index);