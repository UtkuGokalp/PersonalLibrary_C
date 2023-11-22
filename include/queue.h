#pragma once

#include <stdlib.h>

//FIFO data structure
typedef struct Queue Queue;

//Creates a queue with the given capacity and initializes all elements
Queue* CreateNewQueue(void);
//Destroys the given queue
void DestroyQueue(Queue* queue);
//Enqueues a value into the given queue
void Enqueue(Queue* queue, int value);
//Dequeues a value from the given queue
int Dequeue(Queue* queue);
//Returns the value at the given index without dequeueing. If index is greater than capacity, returns -1
int GetValue(const Queue* queue, size_t index);
//Returns the capacity of the given queue
size_t GetQueueCapacity(const Queue* queue);
