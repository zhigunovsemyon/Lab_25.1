#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

typedef struct 
{
	struct part *head;
	struct part *tail;
}
queue;

queue *QueueInit(void);
void QueueFree(queue **);

uint8_t QueuePushToHead(int8_t, queue *);
uint8_t QueuePushToEnd(int8_t, queue *);

uint8_t QueuePullFromHead(int8_t *, queue *);
uint8_t QueuePullFromEnd(int8_t *, queue *);


#endif // !_QUEUE_H

