#include "queue.h" /*<stdio.h> <malloc.h> <stdint.h>*/

struct part
{
	int8_t num;
	struct part *next;
};

struct queue
{
	struct part *head;
	struct part *tail;
};

queue *QueueInit(void)
{
	return (queue *)calloc(1, sizeof(queue));
};

void QueueFree(queue **qptr)
{
	if (!(*qptr)->head)
	{
		free(*qptr);
		*qptr = NULL;
		return;
	}

	struct part *tmp = (*qptr)->head;
	(*qptr)->head = (*qptr)->head->next;
	free(tmp);
	return QueueFree(qptr);
};

uint8_t QueuePushToHead(int8_t num, queue *q)
{
	struct part *buf = (struct part *)malloc(sizeof(struct part));
	if (!buf)
		return -1;

	buf->num = num;

	if (!q->head)
	{
		q->head = q->tail = buf;
		buf->next = NULL;
		return 0;
	}

	buf->next = q->head;
	q->head = buf;
	return 0;
};

uint8_t QueuePushToEnd(int8_t num, queue *q)
{
	struct part *buf = (struct part *)malloc(sizeof(struct part));
	if (!buf)
		return -1;

	buf->num = num;
	buf->next = NULL;

	if (!q->tail)
	{
		q->head = q->tail = buf;
		buf->next = NULL;
		return 0;
	}

	q->tail->next = buf;
	q->tail = buf;
	return 0;
};

uint8_t QueuePullFromHead(int8_t *ret, queue *q)
{
	if (!q->head)
		return 1;

	*ret = q->head->num;
	struct part *tmp = q->head;
	q->head = q->head->next;
	free(tmp);
	return 0;
};

uint8_t QueuePullFromEnd(int8_t *ret, queue *q)
{
	if (!q->tail)
		return 1;

	*ret = q->tail->num;
	struct part *pre_tail = q->head;
	if (!pre_tail->next)
	{
		free(pre_tail);
		q->head = q->tail = NULL;
		return 0;
	}

	while (pre_tail->next->next)
		pre_tail = pre_tail->next;

	free(pre_tail->next);
	pre_tail->next = NULL;
	q->tail = pre_tail;
	return 0;
};

int16_t QueueIncreaseCmp(int8_t a, int8_t b)
{
	return a - b;
}

int16_t QueueDecreaseCmp(int8_t a, int8_t b)
{
	return b - a;
}

void QueueBubbleSort(queue *q, int16_t(cmp)(int8_t, int8_t))
{
	uint16_t flag = 0;

	if (!q->head)
		return;
	if (!q->head->next)
		return;

	if (flag)
		QueueBubbleSort(q, cmp);
}
