# include <stdio.h>
# include <stdlib.h>
# include <time.h>

double Randomize(double a[], int size) {
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = (double)rand() / (double)rand();
	}
	return *a;
}

void Selection(double a[],int size) {
	int i,j, min;
	double tmp;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (a[j] < a[min]) {
				min = j;					//Находим минимальный элемент в массиве
			}
		}
		if (min != i) {						// Ставим минимальный элемент в начало
			tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
	for (i = 0; i < size; i++) {
		printf("%lf /", a[i]);
	}
}

void Shell(double a[], int size) {

}

void Merge(double a[], int size) {

}

void Radix(double a[], int size) {

}

void main() {
	int i,size,variant, *a = NULL;
	printf("enter the size of the array");
	scanf(" %d", &size);
	a = (double*)malloc(size * sizeof(double));
	do
	{
		system("cls");
		printf("Select the sort type/n");
		printf("1.Selection/n");
		printf("2.Shell");
		printf("3.Merge");
		printf("4.Radix");
		printf("5.Randomize");
		printf("0.Exit");
		scanf(" %d", &variant);
			switch (variant)
			{
			case 1:
				Selection(&a, size);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 0:
				break;
			default:
				printf("incorrent choice"); // проверка на ошибочные вводы
				break;
			}
	} while (variant==0)
	
}
