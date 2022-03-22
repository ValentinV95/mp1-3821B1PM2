#include <stdio.h>
#include <time.h>
#define SIZE 5

int per = 0, srav = 0;

void combsort(double mas[])
{
	double factor = 1.2473309;
	int step = SIZE - 1;
	while (step >= 1)
	{
		srav += 2;
		for (int i = 0; i + step < SIZE; i++)
		{
			srav += 2;
			if (mas[i] > mas[i + step])
			{
				double tmp = mas[i];
				mas[i] = mas[i + step];
				mas[i + step] = tmp;
				per++;
			}
		}
		step /= factor;
	}
	srav++;
}

void rands(double array[], int b)
{
	int i;
	srand(time(0));
	for (i = 0; i < b; i++)
	{
		array[i] = rand() % 1000000 + (rand() % 1000000) / 1000000.0;
	}
}

void sont(double array[], int i)
{
	int j;
	for (j = 0; j < i; j++)
	{
		printf("%lf ", array[j]);
	}
	printf("\n\n");
}

int main()
{
	double mas[SIZE];
	printf("Unsoretd array\n");
	rands(mas, SIZE);
	sont(mas, SIZE);
	combsort(mas, SIZE);
	printf("Sorted array\n");
	sont(mas, SIZE);
	printf("Perestanovok %d\nSravneniy %d\n", per, srav);
}