#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <process.h>
#include <math.h>

float* createMas(int length)
{
	int i = 0;
	float* m = malloc(sizeof(float) * length);

	for (i; i < length; i++)
	{
		m[i] = rand() % 1001 + (rand() % 1000) / 1000.0f;
	}

	//for (i = 0; i < length; i++)
	//{
	//	printf_s("%f\n", m[i]);
	//}

	return m;
} 

void main()
{
	int compare = 0, swap = 0,length = 10;
	int step, i, j;
	float tmp = 0;
	float *m = createMas(10);
		
	srand(time(NULL));

	while (length < 10000)
	{

		//printf("%d\n",rand()+time(NULL));
		srand(time(NULL) + rand());

		compare = 0;
		swap = 0;
		for (step = length / 2; step > 0; step /= 2)
		{
			compare++;
			for (i = step; i < length; i++)
			{
				compare++;
				for (j = i - step; j >= 0 && m[j] > m[j + step]; j -= step)
				{
					compare += 2;
					tmp = m[j];
					m[j] = m[j + step];
					m[j + step] = tmp;
					swap++;
				}
			}
		}
			
		//printf_s("\nMas %d\n",length/10);
		//for (i = 0; i < length; i++)
		//{
		//	printf_s("%f\n", m[i]);
		//}

		printf("%d;%d;%d;%lf\n", length, swap, compare, 2*length*log((double)length));

		free(m);
		m = NULL;
		length += 10;
		m = createMas(length);
	}
}