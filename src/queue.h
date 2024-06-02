#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

struct part
{
	int8_t num;
	struct part *next;
};

typedef struct 
{
	struct part *head;
	struct part *tail;
}
queue;

queue *QueueInit(void);
void QueueFree(void);

uint8_t QueuePushToHead(int8_t);
uint8_t QueuePushToEnd(int8_t);

int8_t QueuePullFromHead(int8_t);
int8_t QueuePullFromEnd(int8_t);


#endif // !_QUEUE_H

