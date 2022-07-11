#include "linkedlist.h"

typedef struct Node
{
    void* data;
    struct Node* next;
    struct Node* previous;
} Node;

Node* CreateNewNode(void* data, Node* previous, Node* next)
{
    Node* new = (Node*)calloc(1, sizeof(Node));
    if (new == NULL)
    {
        return NULL;
    }
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

Node* GetNode(const LinkedList* list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->length)
    {
        return NULL;
    }
    if (list->first_node == NULL)
    {
        return NULL;
    }

    Node* current = list->first_node;
    for (size_t i = 0; i < index; i++)
    {
        if (current->next != NULL)
        {
            current = current->next;
        }
    }
    return current;
}

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

bool AddToLinkedList(LinkedList* list, void* data)
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
        Node* current = GetNode(list, list->length - 1);
        if (current == NULL)
        {
            return false;
        }
        current->next = CreateNewNode(data, current, NULL);
    }
    list->length++;
    return true;
}

bool InsertIntoLinkedList(LinkedList* list, void* data, size_t index)
{
    if (list == NULL)
    {
        return false;
    }
    if (index == 0 && list->first_node == NULL)
    {
        return AddToLinkedList(list, data);
    }
    if (index >= list->length)
    {
        return false;
    }

    Node* node = GetNode(list, index);
    if (node == NULL)
    {
        return false;
    }
    Node* temp = node->previous;
    node->previous = CreateNewNode(data, temp, node);
    if (index == 0)
    {
        list->first_node = node->previous;
    }
    if (temp != NULL)
    {
        temp->next = node->previous;
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
    if (index == 0) //If removing the first node, list->first_node should be updated.
    {
        //Previous node is always NULL. Just update the next node.
        Node* old_first_node = list->first_node;
        list->first_node = list->first_node->next;
        if (list->first_node != NULL) //list->first_node will be NULL after the previous line if the list has only one element.
        {
            list->first_node->previous = NULL;
        }
        free(old_first_node);
    }
    else
    {
        Node* current = GetNode(list, index);
        if (current == NULL)
        {
            return false;
        }
        if (current->previous != NULL)
        {
            current->previous->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->previous = current->previous;
        }
        free(current);
    }
    list->length--;
    return true;
}

bool ClearLinkedList(LinkedList* list)
{
    if (list == NULL)
    {
        return false;
    }
    while (list->length > 0)
    {
        bool result = RemoveFromLinkedListAt(list, 0);
        if (result == false)
        {
            return false;
        }
    }
    return true;
}

size_t GetLinkedListLength(const LinkedList* list)
{
    return list->length;
}

void* GetLinkedListElementAt(const LinkedList* list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->length)
    {
        return NULL;
    }

    Node* current = GetNode(list, index);
    return current->data;
}