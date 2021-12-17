#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10000
int compare = 0, swap = 0;

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
	int i = 0, j = 0, ident = 1, step = N - 1, flag = 1;
	double mas[N], copymas[N], tmp = 0, factor = 1.2473309;

	srand(777);
	feelMas(&mas, &copymas);

	while (step >= 1)
	{
		compare++;
		for (i = 0; i + step < N; i++)
		{
			compare++;
			if (mas[i] > mas[i + step])
			{
				compare++;
				tmp = mas[i];
				mas[i] = mas[i + step];
				mas[i + step] = tmp;
				swap++;
			}
		}
		step = step / factor;
	}

	for (i = 0; i < N - 1; i++)
	{
		compare++;
		for (j = N - 2; j > i - 1; j--)
		{
			compare++;
			if (mas[j] > mas[j + 1])
			{
				flag = 1;
				compare++;
				tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = tmp;
				swap++;
			}
		}

		if (flag == 0)
		{
			break;
		}
	}

	qsort(&copymas, N, sizeof(double), cmp);

	for (i = 0; i < N; i++)
	{
		if (mas[i] != copymas[i])
		{
			ident = 0;
			printf("%d\n", i);
			break;
		}
	}

	if (ident == 1)
	{
		printf_s("Sortiruet pravilno\n");
		printf_s("Dlina - %d\nPerestanovki = %d\nSravnenia = %d\nSravnenia/slojnost - %lf\nPerestanovki/slojnost - %lf\n", N, swap, compare, compare / (float)(N * N), swap / (float)(N * N));
	}
	else
	{
		printf("Sortiruet nepravilno\n");
		for (i = 0; i < N; i++)
		{
			printf("[%d]%lf %lf\n", i, mas[i], copymas[i]);
		}
	}

	return 0;
}