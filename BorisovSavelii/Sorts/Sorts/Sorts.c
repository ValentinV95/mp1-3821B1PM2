#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

uint comparisons = 0;
uint transfers = 0;

void inserts_Sort(float* array_1, uint size_inserts)
{
	float tmp;
	int i, j;
	for (i = 1; ++comparisons && i < size_inserts; i++)
	{
		for (j = i; ++comparisons && j > 0; j--)
		{
			if (++comparisons && array_1[j - 1] > array_1[j])
			{
				tmp = array_1[j - 1];
				array_1[j - 1] = array_1[j];
				array_1[j] = tmp;
				transfers += 2;
			}
		}
	}
}

void Shell_Sort(float* array_2, uint size_Shell)
{
	int step, i, j;
	float tmp;
	for (step = size_Shell / 2; ++comparisons && step > 0; step /= 2)
	{
		for (i = step; ++comparisons && i < size_Shell; i++)
		{
			for (j = i - step; (++comparisons && j >= 0) && (++comparisons && array_2[j] > array_2[j + step]); j -= step)
			{
				tmp = array_2[j];
				array_2[j] = array_2[j + step];
				array_2[j + step] = tmp;
				transfers += 2;
			}
		}
	}
}

void merge_Sort(float* array_3, int first, int end, uint size_merge)
{
	int sep = (first + end) / 2;
	int i = first;
	int j = sep + 1;
	int step;
	float* add = (float*)malloc(size_merge * sizeof(float));
	if (++comparisons && first < end)
	{
		merge_Sort(array_3, first, sep, size_merge);
		merge_Sort(array_3, sep + 1, end, size_merge);

		for (step = 0; ++comparisons && step < end - first + 1; step++)
		{
			if (++comparisons && (j > end) || (++comparisons && (i <= sep)) && (++comparisons && (array_3[i] < array_3[j])))
			{
				add[step] = array_3[i];
				i++;
				transfers++;
			}

			else
			{
				add[step] = array_3[j];
				j++;
				transfers++;
			}
		}

		for (step = 0;  ++comparisons && step < end - first + 1; step++)
		{
			array_3[first + step] = add[step];
			transfers++;
		}
	}
}

void radixPass(short Offset, float* sourse, float* dest, int* count, uint size_pass)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; ++comparisons && i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = size_pass; ++comparisons && i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		transfers++;
	}
}

int* createCounters(float* data, int* counters, uint size_CC)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + size_CC);
	ushort i;

	memset(counters, 0, 256 * sizeof(float) * sizeof(int));

	while (++comparisons && bp != dataEnd)
	{
		for (i = 0; ++comparisons && i < sizeof(float); i++)
		{
			counters[256 * i + *(bp++)]++;
			transfers++;
		}
	}

	return counters;
}

void signedRadixLastPass(float* sourse, float* dest, uint size_RLP)
{
	int i;
	int numNeg = 0;

	for (i = 0; ++comparisons && i < size_RLP; i++)
	{
		if (++comparisons && sourse[i] < 0)
		{
			numNeg++;
		}
	}

	for (i = 0; ++comparisons && i < numNeg; i++)
	{
		dest[i] = sourse[size_RLP - 1 - i];
		transfers++;
	}

	for (i = 0; ++comparisons && i < size_RLP - numNeg; i++)
	{
		dest[i + numNeg] = sourse[i];
		transfers++;
	}

	for (i = 0; ++comparisons && i < size_RLP; i++)
	{
		sourse[i] = dest[i];
		transfers++;
	}
}

void radix_Sort(float* array_4, float* out_array_4, int* in_counters, uint size_radix)
{
	int* count;
	ushort i;
	int j;
	
	int* counters = createCounters(array_4, in_counters, size_radix);

	for (i = 0; ++comparisons && i < sizeof(float); i++)
	{
		count = counters + 256 * i;
		radixPass(i, array_4, out_array_4, count, size_radix);

		for (j = 0; ++comparisons && j < size_radix; j++)
		{
			array_4[j] = out_array_4[j];
			transfers++;
		}
	}

	signedRadixLastPass(array_4, out_array_4, size_radix);
}

int compare(const void* a, const void* b)
{
	float c_a = *(const float*)a;
	float c_b = *(const float*)b;
	return (c_a > c_b) - (c_a < c_b);
}

void check(float* array_check, uint size_check)
{
	qsort(array_check, size_check, sizeof(int), compare);
}

int main()
{
	uint size = 10000;
	ushort select;
	ushort count_check = 0;
	int z, cha, i, checkk;
	float* array = (float*)malloc(size * sizeof(float));
	float* check_array = (float*)malloc(size * sizeof(float));
	float* out_array = (float*)malloc(size * sizeof(float));
	int* main_counters = (int*)malloc(256 * sizeof(float) * sizeof(int));
	
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	for (z = 0; z < size; z++)   
	{
		array[z] = ((float)rand()) / 100;

	}

	for (z = 0; z < size; z++)
	{
		if (z % 2 != 0 && array[z] > 0.00f)
		{
			array[z] *= -1;
		}
	}

	for (cha = 0; cha < size; cha++)
	{
		check_array[cha] = array[cha];
	}
	check(check_array, size);

	printf("\n\nВыбор сортировки:\n\n1. Inserts\n2. Shell\n3. Merge\n4. Radix\n\nНомер сортировки: ");

	scanf_s("%hu", &select);  

	switch (select)
	{
	case 1: inserts_Sort(array, size);
		break;

	case 2: Shell_Sort(array, size);
		break;

	case 3: merge_Sort(array, 0, size - 1, size);
		break;

	case 4:
	{
		for (i = 0; i < size; i++)
		{
			out_array[i] = 0;
		}
		radix_Sort(array, out_array, main_counters, size);
	}
	break;

	default:
	{
		printf("Error\n");
		exit(select);
	}
	break;
	}

	printf("\n\nКоличество сравнений: %d\n\nКоличество присваиваний: %d", comparisons, transfers);

	
	for (checkk = 0; checkk < size; checkk++)
	{
		if (check_array[checkk] != array[checkk])
		{
			count_check++;
			break;
		}
	}

	printf("\n\nПроверка сортировки: ");

	if (count_check != 0)
		printf("Сортировка НЕкорректна\n");
	else
		printf("Сортировка корректна\n");

	return 0;
}
