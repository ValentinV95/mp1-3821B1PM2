#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


float *createMas(int length)
{
	int i = 0;
	float *m = calloc(length,sizeof(float));

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

int main()
{
	int length = 100;
	int i = 0, j = 0;
	int swap = 0, compare = 0;
	float *mas = malloc(sizeof(float));

	srand(1005483580247);

	while (length<1000)
	{
		mas = createMas(length);

		swap = 0;
		compare = 0;
		for (i=0; i < length; i++)
		{
			compare += 1;
			for (j = 0; j < length; j++)
			{
				compare++;
				if (mas[i] > mas[j])
				{
					float tmp = mas[i];
					mas[i] = mas[j];
					mas[j] = tmp;

					swap +=3;
				}
			}
		}

		printf("%d;%d;%d;%d;%d\n",length,swap,compare,length*length,length*3);
		length += 5;

		free(mas);
		mas = NULL;
	}

	free(mas);
	mas = NULL;
	return 0;
}


