#include <stdio.h>
#include <stdlib.h>

void selectionSort(double* arr, int len)
{
	int i, j, minID;
	double tmp;
	for (i = 0; i < len - 1; i++)
	{
		minID = i;
		for (j = i + 1; j < len; j++)
		{
			if (arr[minID] > arr[j])
			{
				minID = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[minID];
		arr[minID] = tmp;
	}
}

void comb_sort(double array[], int size)
{
	double factor = 1.2473309;
	int step = size - 1;

	while (step >= 1)
	{
		for (int i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
			{
				double tmp = array[i];
				array[i] = array[i + step];
				array[i + step] = tmp;
			}
		}
		step /= factor;
	}
}

void merge(double* array1, double* array2, int l, int q, int r)
{
	int i = l, j = q + 1, k = l;
	for (; (i < q + 1) && (j < r + 1); )
	{
		if (array1[i] < array1[j])
		{
			array2[k] = array1[i];
			i++; k++;
		}
		else
		{
			array2[k++] = array1[j++];
		}
	}
	for (; i < q + 1; i++)
	{
		array2[k++] = array1[i];
	}
	for (; j < r + 1; j++)
	{
		array2[k++] = array1[j];
	}
	for (i = l; i < k; i++)
	{
		array1[i] = array2[i];
	}
}

void merge_sort(double* array1, double* array2, int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;
		merge_sort(array1, array2, l, q);
		merge_sort(array1, array2, q + 1, r);
		merge(array1, array2, l, q, r);

	}
}

void createCounters(double* data, int* counters, int N)
{
	unsigned char *bp = (unsigned char*)data;
	unsigned char *dataEnd = (unsigned char*)(data + N);
	int i;
	memset( counters, 0, 256*sizeof(double)*sizeof(int));

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256*i + *(bp++)]++;
		}
	}
}

void radixPass(short Offset, int N, double* source, double* dest, int* count)
{
	double* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

void sign(double* in, double* out, int N)
{
	int i, k;

	for (i = 0; i < N && out[i] >= 0; i++)
	{
	}
	k = i;
	for (i = N - 1; i >= k; i--)
	{
		in[N - i - 1] = out[i];
	}
	for (i = 0; i < k; i++)
	{
		in[N - k + i] = out[i];
	}
}

void radixSort(double* in, double* out, int* counters, int N)
{
	int* count;
	int j;
	unsigned short i;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}
	sign(in, out, N);

}

int main()
{
	char ans;
	int i,len;
	double a;
	double* arr1;
	double* arr2;
	double* arr3;
	
	printf("Specify the length of the array : ");
	scanf_s("%d",&len);
	getchar();
	
	arr1 = (double*)malloc(len * sizeof(double));

	do
	{
		printf("select the input method:\n");
		printf("\tq - generate automatically\n");
		printf("\te - enter yourself\n");
		scanf_s("%c", &ans);
		getchar();
	} while (ans != 'q' && ans != 'e');
	
	switch (ans)
	{
	case 'q':
		srand(999);
		for (i = 0; i < len; i++) {
			arr1[i] = rand()%1000000 + rand()%1000000/1000000.0;
		}
		break;
	case 'e':
		for (i = 0; i < len; i++) {
			scanf_s("%lf",&a);
			arr1[i] = a;
			getchar();
		}
	}


	do
	{
		printf("Output an array?\n");
		printf("\ty - yes\n");
		printf("\tn - no\n");
		scanf_s("%c", &ans);
		getchar();
	} while (ans != 'y' && ans != 'n');

	if (ans == 'y')
	{
		for (i = 0; i < len; i++)
			printf("array[%d] = %lf\n",i,arr1[i]);
		printf("\n");
	}

	do
	{
		printf("\nselect the sort type: \n");
		printf("\ts - selection sort\n");
		printf("\tc - comb sort\n");
		printf("\tm - merge sort\n");
		printf("\tr - radix sort\n");
		scanf_s("%c", &ans);
		getchar();
	} while (ans != 's' && ans != 'c' && ans != 'm' && ans != 'r');
	

	switch (ans)
	{
	case 's':
		selectionSort(arr1, len);
		break;
	case 'c':
		comb_sort(arr1, len);
		break;
	case 'm':
		arr2 = (double*)malloc(len * sizeof(double));
		merge_sort(arr1, arr2, 0, len - 1);
		free(arr2);	
	case 'r':
		arr2 = (double*)malloc(len * sizeof(double));
		arr3 = (int*)malloc(256 * sizeof(double) * sizeof(int));
		radixSort(arr1, arr2, arr3, len);
		free(arr2);
		free(arr3);
		break;
	}


	
	do
	{
		printf("Output a sorted array?\n");
		printf("\ty - yes\n");
		printf("\tn - no\n");
		scanf_s("%c", &ans);
		getchar();
	} while (ans != 'y' && ans != 'n');

	if (ans == 'y')
	{
		for (i = 0; i < len; i++)
			printf("array[%d] = %lf\n", i, arr1[i]);
		printf("\n");
	}

	return 0;
}
