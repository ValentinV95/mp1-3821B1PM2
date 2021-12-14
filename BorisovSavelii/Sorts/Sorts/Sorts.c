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
	for (int i = 1; ++comparisons && i < size_inserts; i++)
	{
		for (int j = i; ++comparisons && j > 0; j--)
		{
			if (++comparisons && array_1[j - 1] > array_1[j])
			{
				float tmp = array_1[j - 1];
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
	if (++comparisons && first < end)
	{
		int sep = (first + end) / 2;

		merge_Sort(array_3, first, sep, size_merge);
		merge_Sort(array_3, sep + 1, end, size_merge);

		int i = first;
		int j = sep + 1;

		float* add = malloc(size_merge * sizeof(float));

		for (int step = 0; ++comparisons && step < end - first + 1; step++)
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

		for (int step = 0;  ++comparisons && step < end - first + 1; step++)
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
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	uint size;

	printf("Количество элементов в массиве: ");
	scanf_s("%d", &size);

	float* array = malloc(size * sizeof(float));       

	for (int z = 0; z < size; z++)   
	{
		array[z] = ((float)rand()) / 100;

	}

	for (int z = 0; z < size; z++)
	{
		if (z % 2 != 0 && array[z] > 0.01f)
		{
			array[z] *= -1;
		}
	}


	float* check_array = malloc(size * sizeof(float));
	for (int cha = 0; cha < size; cha++)
	{
		check_array[cha] = array[cha];
	}
	check(check_array, size);

	printf("\n\nВыбор сортировки:\n\n1. Inserts\n2. Shell\n3. Merge\n4. Radix\n\nНомер сортировки: ");

	ushort select;
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
		float* out_array = malloc(size * sizeof(float));

		for (int i = 0; i < size; i++)
		{
			out_array[i] = 0;
		}
		int* main_counters = malloc(256 * sizeof(float) * sizeof(int));

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

	ushort count_check = 0;
	for (int check = 0; check < size; check++)
	{
		if (check_array[check] != array[check])
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
