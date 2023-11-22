#include "queue.h"

#define INITIAL_QUEUE_CAPACITY  4

#define QUEUE_VALUE_TYPE int

typedef struct Queue
{
    size_t capacity;
    QUEUE_VALUE_TYPE* values;
    QUEUE_VALUE_TYPE* dequeuePointer;
    QUEUE_VALUE_TYPE* enqueuePointer;
} Queue;

Queue* CreateNewQueue(void)
{
	Queue* queue = (Queue*)calloc(1, sizeof(Queue));
	if (queue == NULL)
	{
		return NULL;
	}
	queue->capacity = INITIAL_QUEUE_CAPACITY;
	queue->values = (QUEUE_VALUE_TYPE*)calloc(queue->capacity, sizeof(QUEUE_VALUE_TYPE));
	if (queue->values == NULL)
	{
		free(queue);
		return NULL;
	}
	queue->enqueuePointer = queue->dequeuePointer = queue->values;
	return queue;
}

void DestroyQueue(Queue* queue)
{
	if (queue != NULL)
	{
	    if (queue->values != NULL)
	    {
	    	free(queue->values);
	    }
		free(queue);
	}
}

void EnlargeQueue(Queue* queue)
{
	//allocate new memory for values
	QUEUE_VALUE_TYPE* newValues = (QUEUE_VALUE_TYPE*)calloc(GetQueueCapacity(queue) * 2, sizeof(QUEUE_VALUE_TYPE));
	//copy the values to the new memory
	for (size_t i = 0; i < GetQueueCapacity(queue); i++)
	{
		newValues[i] = queue->values[i];
	}
	int dequeuePtrOffset = queue->dequeuePointer - queue->values;
	int enqueuePtrOffset = queue->enqueuePointer - queue->values;
	//free the old values pointer
	free(queue->values);
	//change the pointer to newly allocated memory
	queue->values = newValues;
	//change the enqueue and dequeue pointers
	queue->dequeuePointer = queue->values + dequeuePtrOffset;
	queue->enqueuePointer = queue->values + enqueuePtrOffset;
	//update the queue capacity
	queue->capacity *= 2;
}

QUEUE_VALUE_TYPE GetValue(const Queue* queue, size_t index)
{
	if (index < GetQueueCapacity(queue) - (queue->dequeuePointer - queue->values))
	{
		return *(queue->dequeuePointer + index);
	}
	return 0;
}

void Enqueue(Queue* queue, QUEUE_VALUE_TYPE value)
{

	if (queue->enqueuePointer + 1 > queue->values + GetQueueCapacity(queue)) //Queue capacity is exceeded
	{
		EnlargeQueue(queue);
	}
	*queue->enqueuePointer = value;
    queue->enqueuePointer++;
}

QUEUE_VALUE_TYPE Dequeue(Queue* queue)
{
    QUEUE_VALUE_TYPE value = *queue->dequeuePointer;
    if (queue->dequeuePointer + 1 <= queue->enqueuePointer)
    {
    	queue->dequeuePointer++;
    }
    return value;
}

size_t GetQueueCapacity(const Queue* queue)
{
	return queue->capacity;
}


