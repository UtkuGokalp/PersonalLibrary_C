#include "linkedlist.h"

typedef struct Node
{
    const void* data;
    struct Node* next;
    struct Node* previous;
} Node;

Node* CreateNewNode(const void* data, Node* previous, Node* next)
{
    Node* new = (Node*)calloc(1, sizeof(Node));
    new->data = data;
    new->previous = previous;
    new->next = next;
    return new;
}

typedef struct LinkedList
{
    size_t length;
    Node* first_node;
} LinkedList;

LinkedList* CreateLinkedList()
{
    LinkedList* list = (LinkedList*)calloc(1, sizeof(LinkedList));
    if (list == NULL)
    {
        return NULL;
    }
    list->length = 0;
    list->first_node = NULL;
    return list;
}

bool DestroyLinkedList(LinkedList* list)
{
    if (list == NULL)
    {
        return false;
    }

    if (list->first_node != NULL)
    {
        Node* current = list->first_node;
        while (current != NULL)
        {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(list);
    return true;
}

bool AddToLinkedList(LinkedList* list, const void* data)
{
    if (list == NULL)
    {
        return false;
    }
    
    if (list->first_node == NULL)
    {
        list->first_node = CreateNewNode(data, NULL, NULL);
    }
    else
    {
        Node* current = list->first_node;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = CreateNewNode(data, current, NULL);
    }
    list->length++;
    return true;
}

bool RemoveFromLinkedListAt(LinkedList* list, size_t index)
{
    if (list == NULL)
    {
        return false;
    }
    if (index >= list->length)
    {
        return false;
    }
    if (list->first_node == NULL)
    {
        return false;
    }

    Node* current = list->first_node;
    for (size_t i = 0; i < index; i++)
    {
        if (current->next != NULL)
        {
            current = current->next;
        }
    }

    if (current->previous != NULL)
    {
        current->previous->next = current->next;
    }
    if (current->next != NULL)
    {
        current->next->previous = current->previous;
    }

    list->length--;
    return true;
}

size_t GetLinkedListLength(const LinkedList* list)
{
    return list->length;
}

void* GetLinkedListElementAt(const LinkedList* list, size_t index)
{
    if (index >= list->length)
    {
        return NULL;
    }

    size_t i = 0;
    Node* current = list->first_node;
    while (i < index)
    {
        current = current->next;
        i++;
    }
    return (void*)current->data;
}
