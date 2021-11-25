#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, j, minID;
	double a[10], tmp;
	srand(777);
	for (i = 0; i < 10; i++)
	{
		a[i] = rand()%1000000 + (rand() % 1000000) / 1000000.0;
		printf("a[%d]%lf\n",i,a[i]);
	}

	printf("Sort:\n");

	for (i = 0; i < 10 - 1; i++)
	{
		minID = i;
		for (j = i + 1; j < 10; j++)
		{
			if (a[minID] > a[j])
			{
				minID = j;
			}
		}
		tmp = a[i];
		a[i] = a[minID];
		a[minID] = tmp;
	}

	for (i = 0; i < 10; i++)
	{
		printf("a[%d]%lf\n", i, a[i]);
	}
	
}