#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void feelMas(double* m, double* cm)
{
	int i;

	for (i = 0; i < N; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0) * pow(-1.0, (rand() % 2));
		if (m[i] == -0.0)
		{
			m[i] = 0.0;
		}
		cm[i] = m[i];
	}
}

int cmp(const void* a, const void* b)
{
	double fa = *(const double*)a;
	double fb = *(const double*)b;
	return (fa > fb) - (fa < fb);
}

int main()
{
	int swap = 0, compare = 0, i = 0, j = 0, ident = 1;
	double mas[N], copymas[N], tmp = 0;

	srand(777);
	feelMas(&mas, &copymas);

	for (i = 0; i < N; i++)
	{
		compare++;
		for (j = 0; j < N; j++)
		{
			compare++;
			if (mas[i] < mas[j])
			{
				compare++;
				tmp = mas[i];
				mas[i] = mas[j];
				mas[j] = tmp;
				swap++;
			}
		}
	}

	qsort(&copymas, N, sizeof(double), cmp);

	for (i = 0; i < N; i++)
	{
		if (mas[i] != copymas[i])
		{
			ident = 0;
			break;
		}
	}

	if (ident)
	{
		printf_s("Sortiruet pravilno\n");
		printf_s("Dlina - %d\nSwap = %d\nCompare = %d\nSwap/slojnost - %lf\nCompare/slojnost - %lf\n", N, swap, compare, swap / (float)(N * N), compare / (float)(N * N));
	}
	else
	{
		printf("Sortiruet nepravilno\n");
	}

	return 0;
}