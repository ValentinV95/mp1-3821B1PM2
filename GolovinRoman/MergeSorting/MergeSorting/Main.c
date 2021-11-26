#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

int set_walue = 0, compare = 0;

float* createMas(int length)
{
	int i = 0;
	float* m = calloc(length, sizeof(float));

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

float *merge(float *a,int n,float *b,int m)
{
	int i = 0,j =0, l = 0;
	float *c = malloc(sizeof(float)*(m+n));

	while((i < n) && (j < m))
	{
		compare += 2;
		if (a[i]<b[j])
		{
			c[l++] = a[i++];
		}
		else
		{
			c[l++] = b[j++];
		}
		compare++;
		set_walue++;
	}

	for (;i<n;i++)
	{
		compare++;
		set_walue++;
		c[l++] = a[i];
	}

	for (; j < m; j++)
	{
		compare++;
		set_walue++;
		c[l++] = b[j];
	}

	return c;
}

float* mergeSort(float *sortable, int left, int right)
{
	if (left<right)
	{
		int q = (left+right) / 2;

		int lright = right - (q+1)+1, lleft = q-left+1;

		float* l_mas = malloc(sizeof(float)* lleft);
		float* r_mas = malloc(sizeof(float)* lright);

		l_mas = mergeSort(sortable,left,q);
		r_mas = mergeSort(sortable,q+1, right);

		return merge(l_mas, lleft,r_mas, lright);
	}

	return &sortable[left];
}


void main()
{
	int length = 10;
	int i = 0, j = 0;
	extern set_walue, compare;
	float *mas = malloc(sizeof(float)*2);

	srand(3589138759761531);

	while (length < 1000)
	{
		mas = createMas(length);
		mas = mergeSort(mas, 0, length - 1);

		printf("%d;%d;%d;%lf\n",length,set_walue,compare,length*log((double)length));

		set_walue = 0;
		compare = 0;
		length += 10;

		free(mas);
		mas = NULL;
	}


	//printf_s("\nMas after sort\n");
	//for (int i = 0; i < length; i++)
	//{
	//	printf_s("%lf\n",mas[i]);
	//}
}