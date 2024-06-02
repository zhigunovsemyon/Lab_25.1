#include "queue.h"/*<stdio.h> <malloc.h> <stdint.h>*/

/* Дан файл из целых чисел.Используя очередь,
за один просмотр файла напечатать сначала все отрицательные числа,
затем все положительные числа, сохраняя исходный порядок в каждой группе */
int main(int argc, const char *args[])
{
	if (argc < 2)
	{
		puts("Не было передано имя файла!");
		return 1;
	}

	FILE *source = fopen(args[1], "rt");
	if (!source)
	{
		perror(args[1]);
		return 1;
	}

	queue *q_positive = QueueInit();
	queue *q_negative = QueueInit();

	for (int8_t buf;												//Буфер
		fscanf(source, "%hhd", &buf) > 0;							//Чтение из файла в буфер
		QueuePushToEnd(buf, (buf < 0) ? q_negative : q_positive));	//Добавление из буфера в очередь

	fclose(source);

	puts("Очередь положительных чисел:");
	for (int8_t buf;				//Буфер
		!QueuePullFromHead(&buf, q_positive); 	//Чтение из очереди в буфер
		printf("%hhd ", buf));		//Вывод из буфера на экран
	putchar('\n');

	puts("Очередь отрицательных чисел :");
	for (int8_t buf;						   // Буфер
		 !QueuePullFromHead(&buf, q_negative); // Чтение из очереди в буфер
		 printf("%hhd ", buf)); // Вывод из буфера на экран
	putchar('\n');

	QueueFree(&q_positive);
	QueueFree(&q_negative);
	return 0;
}