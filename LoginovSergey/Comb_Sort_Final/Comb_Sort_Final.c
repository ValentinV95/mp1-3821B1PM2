#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10000
int compare = 0, swap = 0;

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

int cmp(const void* z, const void* p)
{
	double rch = *(const double*)z;
	double rzl = *(const double*)p;
	return (rch > rzl) - (rch < rzl);
}

int main()
{
	int i = 0, j = 0, id = 1, shag = N - 1, flag = 1;
	double mas[N], copymas[N], tmp = 0, factor = 1.2473309;

	srand(777);
	massiv(&mas, &copymas);

	while (shag >= 1)
	{
		compare++;
		for (i = 0; i + shag < N; i++)
		{
			compare++;
			if (mas[i] > mas[i + shag])
			{
				compare++;
				tmp = mas[i];
				mas[i] = mas[i + shag];
				mas[i + shag] = tmp;
				swap++;
			}
		}
		shag = shag / factor;
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
			id = 0;
			printf("%d\n", i);
			break;
		}
	}

	if (id == 1)
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
