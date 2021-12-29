#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#define arrsize 10
int N;

void bubble_sort(float mas[], int* swap, int* check);
void quick_sort(float mas[], int a, int* swap, int* check);
void merge_sort(float mas[], int l, int r, int* swap, int* check);
void random(float mas[]);
void createCounters(float data[], long counters[], int* swap, int* check);
void signedradixPass(float source[], float out[], int* swap, int* check);
void radixPass(short Offset, float source[], float dest[], long count[], int* swap, int* check);
void RadixSort(float in[], float out[], long counters[], int* swap, int* check);


void main() {
	srand(time(0));
	int n;
	float mas[arrsize], secondary[arrsize];
	long counters[sizeof(float) * 256];
	int swap = 0;
	int check = 0;
	random(mas);

	printf("vvedite cufru sortirovki\n");
	printf(" 1 - bubblesort\n 2 - quicksort\n 3 - mergesort\n 4 - radixsort");
	scanf_s("%d", &N);
	if (N == 1) {
		bubble_sort(mas, &swap, &check);
		printf("bubble_sort\n");
		for (n = 0; n <= arrsize - 1; n++) printf("%lf\n", mas[n]);
	}
	else if (N == 2) {
		quick_sort(mas, arrsize - 1, &swap, &check);
		printf("quick_sort\n");
		for (n = 0; n <= arrsize - 1; n++) printf("%lf\n", mas[n]);
	}
	else if (N == 3) {
		merge_sort(mas, 0, arrsize - 1, &swap, &check);
		printf("merge_sort\n");
		for (n = 0; n <= arrsize - 1; n++) printf("%lf\n", mas[n]);
	}
	else if (N == 4) {
		RadixSort(mas,secondary,counters,&swap,&check);
		printf("radixsort\n");
		for (n = 0; n <= arrsize - 1; n++) printf("%lf\n", mas[n]);
	}


	printf("\n\n\n");
	printf("swap = %i\n", swap);
	printf("check = %i\n", check);
}



void bubble_sort(float mas[], int* swap, int* check) {
	int k, j;
	float vrem;
	for (k = 0; k < arrsize - 1; k++) {
		*check += 1;
		for (j = arrsize - 1; j > k; j--) {
			*check += 1;
			if (mas[j - 1] > mas[j]) {
				*check += 1;
				*swap += 3;
				vrem = mas[j - 1];
				mas[j - 1] = mas[j];
				mas[j] = vrem;

			}
		}
	}


}


void quick_sort(float mas[], int r, int* swap, int* check) {
	int k = 0;
	int size = r;
	float tmp = 0;
	float c = mas[r / 2];
	while (k <= r) {
		*check += 1;
		while (mas[k] < c) {
			*check += 1;
			k++;
		}
		while (mas[r] > c) {
			*check += 1;
			r--;
		}
		if (k <= r) {
			*check += 1;
			tmp = mas[k];
			mas[k] = mas[r];
			mas[r] = tmp;
			*swap += 3;
			k++; r--;
		}
	}
	if (r > 0) { quick_sort(mas, r, swap, check); *check += 1; }

	if (size > k) { quick_sort(mas + k, size - k, swap, check); *check += 1; }

}


void merge_sort(float mas[], int l, int r, int* swap, int* check) {

	if (l == r) return;
	*check += 1;
	int mid = (l + r) / 2;
	merge_sort(mas, l, mid, swap, check);
	merge_sort(mas, mid + 1, r, swap, check);
	int i = l;
	int j = mid + 1;
	float* tmp = (float*)malloc(r * sizeof(float));
	for (int step = 0; step < r - l + 1; step++)
	{
		*check += 1;
		if ((j > r) || ((i <= mid) && (mas[i] < mas[j])))
		{
			*check += 3;
			*swap += 1;
			tmp[step] = mas[i];
			i++;
		}
		else
		{
			tmp[step] = mas[j];
			*swap += 1;
			j++;
		}
	}

	for (int step = 0; step < r - l + 1; step++) {
		mas[l + step] = tmp[step];
		*check += 1;
		*swap += 1;
	}
}



void createCounters(float data[], long counters[], int* swap, int* check) {

	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + arrsize);
	unsigned short int i;

	memset(counters, 0, 256 * sizeof(float) * sizeof(long));

	while (bp != dataEnd) {

		*check += 1;
		for (i = 0; i < sizeof(float); i++) {

			*check += 1;
			counters[256 * i + *(bp++)]++;
		}
	}
}

void signedradixPass(float source[], float out[], int* swap, int* check) {

	unsigned int i, j, index;
	i = 0;
	index = 0;
	while (source[i++] > 0)
		*check += 1;
	for (j = arrsize - 1; j >= i - 1; j--) {

		*check += 1;
		source[index++] = out[j];
		*swap += 1;
	}
	for (j = 0; j < i - 1; j++) {

		*check += 1;
		source[index++] = out[j];
		*swap += 1;
	}
}

void radixPass(short Offset, float source[], float dest[], long count[], int* swap, int* check) {

	float* sp;
	unsigned char* bp;
	long s, c, i, * cp = count;

	s = 0;
	for (i = 256; i > 0; --i, ++cp) {

		*check += 1;
		c = *cp;
		*cp = s;
		*swap += 2;
		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	*swap += 1;
	for (i = arrsize; i > 0; --i, bp += sizeof(float), ++sp) {

		*check += 1;
		cp = count + *bp;
		dest[*cp] = *sp;
		*swap += 2;
		(*cp)++;
	}
}

void RadixSort(float in[], float out[], long counters[], int* swap, int* check) {
	long* count;
	unsigned short int i;
	createCounters(in, counters, swap, check);

	for (i = 0; i < sizeof(float); i++)
	{
		*check += 1;
		count = counters + 256 * i;
		radixPass(i, in, out, count, swap, check);
		for (long j = 0; j < arrsize; j++)
		{
			*check += 1;
			in[j] = out[j];
			*swap += 1;
		}
	}
	count = counters + 256 * i;
	signedradixPass(in, out, swap, check);
}


void random(float arr[])
{
	srand(time(0));
	int n;
	for (n = 0; n < arrsize; n++)
	{
		arr[n] = rand() % 1000 - 500;
	}
	printf("\n");
}