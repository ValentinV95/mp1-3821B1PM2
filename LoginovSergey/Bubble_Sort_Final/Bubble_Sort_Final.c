#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void massiv(double* m, double* cm)
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

int com(const void* z, const void* p)
{
	double rch = *(const double*)z;
	double rzl = *(const double*)p;
	return (rch > rzl) - (rch < rzl);
}

int main()
{
	int swap = 0, compare = 0, i = 0, j = 0, id = 1;
	double mas[N], copymas[N], tmp = 0;

	srand(777);
	massiv(&mas, &copymas);

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

	qsort(&copymas, N, sizeof(double), com);

	for (i = 0; i < N; i++)
	{
		if (mas[i] != copymas[i])
		{
			id = 0;
			break;
		}
	}

	if (id)
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
