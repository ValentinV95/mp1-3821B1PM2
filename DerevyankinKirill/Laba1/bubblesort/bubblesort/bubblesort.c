#include <stdio.h>
#include <time.h>
#define SIZE 5

int srav = 0, per = 0;

void bubblesort(double mas[])
{
	srav++;
	for (int i = 0; i < SIZE - 1; i++)
	{
		srav += 2;
		for (int j = SIZE - 2; j > i - 1; j--)
		{
			srav += 2;
			if (mas[j] > mas[j + 1])
			{
				double tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = tmp;
				per++;
			}
		}
	}
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
	bubblesort(mas, SIZE);
	printf("Sorted array\n");
	sont(mas, SIZE);
	printf("Perestanovok %d\nSravneniy %d\n", per, srav);
}