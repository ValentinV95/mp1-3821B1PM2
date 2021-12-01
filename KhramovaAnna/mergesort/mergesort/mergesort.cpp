#include <stdio.h>
#include <stdlib.h>
#define size 7
int merge(double a[], int low, int middle, int high) {

	int j = low;                 /*нижняя граница массива*/
	int k = middle + 1;          /*середина массива*/  
	int i = 0;                   /*индекс нового массива В*/
	int count = 0;
	double b[size] = {0};        /*в массив В сливаем элементы подмассивов*/

	while (j <= middle && k <= high) { /*если левая граница дошла до середины, то выходим из цикла*/
		count = count + 2;             /*считаем перестановки*/
		if (a[j] < a[k]) {             /*если правая граница дошла до конца, то выходим из цикла*/
			count++;                  
			b[i] = a[j];               /*элемент из левой половины меньше элемента из правой половины*/
			j++;                       /*тогда в новый массив записываем этот элемент из левой половины*/
		}
		else {
			count++;
			b[i] = a[k];
			k++;
		}
		i++;                       /*увеличиваем индекс нового массива b*/
	}
	while (j <= middle) {          /*если индекс k дошел до конца то элементы с индексом j могли еще не*/
		count++;
		b[i] = a[j];               /*закончиться, значит заполняем массив b оставшимися элементами*/
		j++;
		i++;
	}
	while (k <= high) {
		count++;
		b[i] = a[k];
		k++;
		i++;
	}
	for (int i = low; i <= high; i++) { /*переписываем элементы из получившегося массива b*/
		a[i] = b[i-low];                /*в массив а*/
	}
	return count;
}

int Mergesort(double a[], int l, int r) {
	if (l < r) {
		int count = 0;
		int q = l + (r-l)/2;     /*вычисляем середину массива*/
		Mergesort(a, l, q);      /*вызываем функцию рекурсивно и она сортирует две части массива,*/
		Mergesort(a, q + 1, r);  /*потом 4, пока не останется по одному элементу*/
		count = merge(a, l, q, r);       /*далее все одноэлементные массивы сливаем в 1*/
		return count;
	}
}

int main() {
	int i = 0; 
	double a[size]; int count = 0;
	for (i = 0; i < size; i++) {
		printf("a[%d] = ", i);
		scanf_s("%lf", &a[i]);
	}

	printf("sorted massive\n");
	count = Mergesort(a,0, size - 1); /*изначально левая граница равна 0 (началу массива), а правая размеру массива - 1*/
	for (int i = 0; i < size; i++) {
		printf("a[%d] = %lf\n", i, a[i]);
	}
	printf("the number of comparisons = %d", count);
	return 0;
}