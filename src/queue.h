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

#endif // !_QUEUE_H

