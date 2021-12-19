#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define M 500
int swap = 0;
int comp = 0;
int correct = 0;
int srt = 0;

void check_array(double array[], int size){
	for (int i = 1; i < size; i++){
		if (array[i - 1] > array[i]){
			printf("\nSort is completed incorrectly\n");
			break;
		} 
		else{
			printf("\nSort is correctly completed\n");
			break;
		}
	}
}

void InsertionSort(double array[], int size) {
	int i = 0;

	for (int i = 1; i < size; i++) {
		comp = comp + 1;
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {

			double tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
			swap = swap + 3;
			comp = comp + 2;
		}
	}
}

void Shell_sort(double array[], int size) {
	for (int step = size / 2; step > 0; step = step / 2) {
		for (int i = step; i < size; i++) {
			comp = comp + 1;
			for (int j = i - step; j >= 0 && array[j] > array[j + step]; j = j - step) {
				double tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
				swap = swap + 3;
				comp = comp + 2;
			}
		}
	}
}

void merge(double a[], int low, int middle, int high) {

	int j = low;                 /*нижняя граница массива*/
	int k = middle + 1;          /*середина массива*/
	int i = 0;                   /*индекс нового массива В*/
	double b[M] = { 0 };        /*в массив В сливаем элементы подмассивов*/

	while (j <= middle && k <= high) { /*если левая граница дошла до середины, то выходим из цикла*/
		comp = comp + 2;             /*считаем перестановки*/
		if (a[j] < a[k]) {             /*если правая граница дошла до конца, то выходим из цикла*/
			swap++;
			b[i] = a[j];               /*элемент из левой половины меньше элемента из правой половины*/
			j++;                       /*тогда в новый массив записываем этот элемент из левой половины*/
		}
		else {
			swap++;
			b[i] = a[k];
			k++;
		}
		i++;                       /*увеличиваем индекс нового массива b*/
	}
	while (j <= middle) {          /*если индекс k дошел до конца то элементы с индексом j могли еще не*/
		swap++;
		b[i] = a[j];               /*закончиться, значит заполняем массив b оставшимися элементами*/
		j++;
		i++;
	}
	while (k <= high) {
		swap++;
		b[i] = a[k];
		k++;
		i++;
	}
	for (int i = low; i <= high; i++) { /*переписываем элементы из получившегося массива b*/
		a[i] = b[i - low];  /*в массив а*/
		swap++;
	}
}

void Mergesort(double a[], int l, int r) {
	if (l < r) {
		int count = 0;
		int q = l + (r - l) / 2;     /*вычисляем середину массива*/
		Mergesort(a, l, q);      /*вызываем функцию рекурсивно и она сортирует две части массива,*/
		Mergesort(a, q + 1, r);  /*потом 4, пока не останется по одному элементу*/
		merge(a, l, q, r);       /*далее все одноэлементные массивы сливаем в 1*/
	}
}

void createCounters(double* data, long int* counters, long int N) {
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short int i;

	memset(counters, 0, 256 * sizeof(double) * sizeof(long int)); //заполняем память нулями

	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++) {
			counters[256 * i + *(bp++)]++;   //считаем сколько встречается одинаковых цифр в кажд разряде 
		}
	}
}

void radixPass(short int offset, long int N, double* source, double* dest, long int* count) {
	double* sp;
	long int s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;           // вспомогательный массив, где находим сколько цифр было перед взятой цифрой 
		*cp = s;           // или с какой позиции начинаются числа с этой цифрой
		s = s + c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp = bp + sizeof(double), ++sp) { //сама сортировка подсчетом
		cp = count + *bp; //взять адрес числа (позицию, на кот находится)
		dest[*cp] = *sp;  //положить само число по этой позиции в дест
		(*cp)++;          //прибавить 1 к текущему значению во вспомогательном массиве
	}
}

void SignedRadixSort(short int offset, long int N, double* source, double* dest, long int* count) {
	double* sp;
	long int s = 0, c, i, * cp = count, NumNeg = 0;
	unsigned char* bp;
	for (i = 128; i < 256; i++) {
		NumNeg = NumNeg + count[i];
	}
	s = NumNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;
		*cp = s;
		s = s + c;
	}
	s = count[255] = 0; cp = count + 254;
	for (i = 254; i >= 128; i--, cp--) {
		*cp += s;
		s = *cp;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; i--, bp += sizeof(double), sp++) {
		cp = count + *bp;
		if (*bp < 128)
		{
			dest[*cp] = *sp;
			(*cp)++;
		}
		else
		{
			(*cp)--;
			dest[*cp] = *sp;
		}
	}
}
void RadixSort(double* in, double* out, long int* counters, long int N) {

	long int* count;
	unsigned char i;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long int j = 0; j < N; j++) {
			in[j] = out[j];
			swap = swap + 1;
		}
	}

	count = counters + 256 * i;
	SignedRadixSort(i, N, in, out, count);
	for (long int j = 0; j < N; j++) {
		in[j] = out[j];
		swap = swap + 1;
	}
}

void callradixsort(double* in, long int N) {
	double* out = (double*)malloc(N * sizeof(double));
	long int* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long int));
	RadixSort(in, out, counters, N);
	free(out);
	free(counters);
}

int main() {
	double a[M];
	int i = 0;
	srand(0);
	printf("Source massive:\n");
	for (i = 0; i < M; i++) {
		printf("a[%d] = ", i);
		a[i] = (double)(rand()) / RAND_MAX * (2000) - 1000;
		printf("%lf\n", a[i]);
	}
	printf("choose the way how array will be sorted:\n");
	printf(" 1. InsertionSort\n ");
	printf("2. ShellSort\n ");
	printf("3. MergeSort\n ");
	printf("4. RadixSort\n ");
	printf("Enter the sorting number:\n ");
	scanf_s("%d", &srt);

	if (srt == 1) {
		printf("array will be sorted by insertion sort\n");
		InsertionSort(a, M);
		printf("\nSORTED MASSIVE:\n");
		for (i = 0; i < M; i++) {
			printf("a[%d] = %lf\n", i, a[i]);
		}
		check_array(a, M);
		printf("Number of comparisons: %d\n", comp);
		printf("Number of swaps: %d\n", swap);
	}
	if (srt == 2) {
		printf("array will be sorted by Shell sort\n");
		Shell_sort(a, M);
		printf("\nSORTED MASSIVE:\n");
		for (i = 0; i < M; i++) {
			printf("a[%d] = %lf\n", i, a[i]);
		}
		check_array(a, M);
		printf("Number of comparisons: %d\n", comp);
		printf("Number of swaps: %d\n", swap);
	}
	if (srt == 3) {
		printf("array will be sorted by merge sort\n");
		Mergesort(a, 0, M - 1);
		printf("\nSORTED MASSIVE:\n");
		for (i = 0; i < M; i++) {
			printf("a[%d] = %lf\n", i, a[i]);
		}
		check_array(a, M);
		printf("Number of comparisons: %d\n", comp);
		printf("Number of swaps: %d\n", swap);

	}
	if (srt == 4) {
		printf("array will be sorted by radix sort\n");
		callradixsort(a, M);
		printf("\nSORTED MASSIVE:\n");
		for (i = 0; i < M; i++) {
			printf("a[%d] = %lf\n", i, a[i]);
		}
		check_array( a,  M);
		printf("Number of swaps: %d\n", swap);
	}
	return 0;
}