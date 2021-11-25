#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


float* createMas(int length)
{
	int i = 0;
	float* m = calloc(length, sizeof(float));

	for (i; i < length; i++)
	{
		m[i] = rand() % 1001 + (rand() % 1000) / 1000.0f;
	}

	//for (i = 0; i < length; i++)
	//{
	//	printf_s("%lf\n", m[i]);
	//}
	return m;
}

void main()
{
	int length = 100;
	int i = 0, j = 0;
	int swap = 0, compare = 0;
	float* mas = malloc(sizeof(float));
}