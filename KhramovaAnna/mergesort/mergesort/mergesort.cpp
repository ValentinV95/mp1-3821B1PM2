#include <stdio.h>
#include <stdlib.h>
#define size 700
int comp = 0;
int swap = 0;

void check_array(double array[], int n) {
	for (int i = 1; i < size; i++)
	{
		if (array[i - 1] > array[i]) {
			printf("\nSort is completed incorrectly\n");
			break;
		}
		else {
			printf("\nSort is correctly completed\n");
			break;
		}
	}
}

void merge(double a[], int low, int middle, int high) {

	int j = low;                 /*нижняя граница массива*/
	int k = middle + 1;          /*середина массива*/
	int i = 0;                   /*индекс нового массива В*/
	int count = 0;
	double b[size] = { 0 };        /*в массив В сливаем элементы подмассивов*/

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
		a[i] = b[i - low];    /*в массив а*/
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

int main() {
	int i = 0;
	double a[size];
	printf("source massive\n");
	for (i = 0; i < size; i++) {
		printf("a[%d] = ", i);
		a[i] = (double)(rand()) / RAND_MAX * (2000) - 1000;
		printf("%lf\n", a[i]);
	}

	printf("sorted massive\n");
	Mergesort(a, 0, size - 1); /*изначально левая граница равна 0 (началу массива), а правая размеру массива - 1*/
	for (int i = 0; i < size; i++) {
		printf("a[%d] = %lf\n", i, a[i]);
	}
	printf("Number of comparisons: %d\n", comp);
	printf("Number of swaps: %d\n", swap);
	printf("cheking of correctness\n");
	check_array(a, size);
	return 0;
}