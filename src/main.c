#include "queue.h"
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

	fclose(source);
	return 0;
}