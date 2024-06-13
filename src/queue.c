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

int8_t QueuePushToHead(int8_t num, queue *q)
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

int8_t QueuePushToEnd(int8_t num, queue *q)
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

int8_t QueuePullFromHead(int8_t *ret, queue *q)
{
	if (!q->head)
		return 1;

	*ret = q->head->num;
	struct part *tmp = q->head;
	q->head = q->head->next;
	free(tmp);
	return 0;
};

int8_t QueuePullFromEnd(int8_t *ret, queue *q)
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

int8_t QueueIncreaseCmp(int8_t arg1, int8_t arg2)
{
	// Если arg1 > arg2 == 1 - 0, возврат 1
	// Если arg1 < arg2 == 0 - 1, возврат -1
	// Если arg1 = arg2 == 0 - 0, возврат 0
	return (arg1 > arg2) - (arg1 < arg2);
}

int8_t QueueDecreaseCmp(int8_t arg1, int8_t arg2)
{
	// Если arg1 < arg2 == 1 - 0, возврат 1
	// Если arg1 > arg2 == 0 - 1, возврат -1
	// Если arg1 = arg2 == 0 - 0, возврат 0
	return (arg1 < arg2) - (arg1 > arg2);
}

static void SwapValue(int8_t *a, int8_t *b)
{
	int8_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void QueueBubbleSort(queue *q, int8_t(cmp)(int8_t, int8_t))
{
	uint16_t flag = 0;

	if (!q->head)
		return;
	if (!q->head->next)
		return;

	struct part *a = q->head, 
			*b = q->head->next;

	while(b /*!= NULL*/)
	{
		// Если сортировщик вернул >0, элементы меняются местами, поднимается флаг
		if (0 < cmp(a->num, b->num))
		{
			flag++;
			SwapValue(&a->num, &b->num);
		}

		a = b;
		b = a->next;
	}
	
	if (flag)
		QueueBubbleSort(q, cmp);
}
