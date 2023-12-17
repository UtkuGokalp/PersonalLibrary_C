#pragma once

#include <stdlib.h>

//FIFO data structure
typedef struct Queue Queue;

//Value type to be used in the queue
#define QUEUE_VALUE_TYPE int

//Creates a queue with the given capacity and initializes all elements
Queue* CreateNewQueue(void);
//Destroys the given queue
void DestroyQueue(Queue* queue);
//Enqueues a value into the given queue
void Enqueue(Queue* queue, QUEUE_VALUE_TYPE value);
//Dequeues a value from the given queue
QUEUE_VALUE_TYPE Dequeue(Queue* queue);
//Returns the value at the given index without dequeueing. If index is greater than capacity, returns -1
QUEUE_VALUE_TYPE GetValue(const Queue* queue, size_t index);
//Returns the capacity of the given queue
size_t GetQueueCapacity(const Queue* queue);
//Returns the length (current amount of stored items) of the given queue
size_t GetQueueLength(const Queue* queue);
