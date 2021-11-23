#include "stdio.h"
#define N 10
int main()
{
	float massiv[N];
	int i, j, k, zamena, sravnen = 0,shag = 0;
	for (i = 0; i < N; i++)
	{
		scanf_s("%f", &massiv[i]);
	}
	for (i = 0; i < N - 1; i++)
	{
		k = 0;
		for (j = N - 2; j > i - 1; j--)
		{
			if (massiv[j] > massiv[j + 1])
			{
				zamena = massiv[j];
				massiv[j] = massiv[j + 1];
				massiv[j + 1] = zamena;
				k = 1;
			}
			sravnen++;
		}
		shag += 1;
		if (k == 0)
			break;
	}
	for (i = 0; i < N; i++)
	{
		printf("%f ", massiv[i]);
	}
	printf("\nkolvo shagov = %d   kolvo sravnenii = %d", shag, sravnen);
}