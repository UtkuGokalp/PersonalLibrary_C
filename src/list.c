#include "list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

static const size_t INITIAL_CAPACITY = 4;

typedef struct List
{
    void** values;
    size_t capacity;
    size_t length;
} List;

List* CreateList()
{
    List* list = (List*)calloc(1, sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }
    list->capacity = INITIAL_CAPACITY;
    list->length = 0;
    list->values = NULL;
    return list;
}

void DestroyList(List* list)
{
    if (list == NULL)
    {
        return;
    }
    
    if (list->values != NULL)
    {
        free(list->values);
    }
    free(list);
}

void AddToList(List* list, void* value)
{
    if (list == NULL)
    {
        return;
    }
    
    if (list->values == NULL)
    {
        list->values = calloc(list->capacity, sizeof(void*));
    }
    else
    {
        if (list->length == list->capacity)
        {
            list->values = realloc(list->values, sizeof(void*) * list->capacity * 2);
            list->capacity *= 2;
        }
    }
    *(list->values + list->length) = value;
    list->length++;
}

bool RemoveFromListAtIndex(List* list, size_t index)
{
    if (list == NULL)
    {
        return false;
    }

    if (index >= list->length)
    {
        return false;
    }
    
    for (size_t i = index; i < list->length - 1; i++)
    {
        list->values[i] = list->values[i + 1];
    }

    list->length--;
    return true;
}

bool RemoveFromList(List* list, void* value)
{
    if (list == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < list->length; i++)
    {
        if (list->values[i] == value)
        {
            RemoveFromListAtIndex(list, i);
            return true;
        }
    }
    return false;
}

size_t GetListLength(const List* list)
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->length;
}

void* GetListElementAt(const List* list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->length)
    {
        return NULL;
    }
    return list->values[index];
}
