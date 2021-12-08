# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int perm = 0, comp = 0;

double* Randomize(double a[], int size) {
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = (double)rand() / (double)rand(); // задаём случайное дробное число
	}
	return a;
}

void Selection(double a[],int size) {
	int i,j, min, perm = 0,comp = 0;
	double tmp;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			comp++;
			if (a[j] < a[min]) {
				min = j;					//Находим минимальный элемент в массиве
			}
		}
		comp++;
		if (min != i) {						// Ставим минимальный элемент в начало
			tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
			perm++;
		}
	}
	for (i = 0; i < size; i++) {
		printf("%lf /", a[i]);
	}
	printf("Number of permition %d\n", perm);
	printf("Number of comparisons %d\n", comp);
	system("pause");
}

void Shell(double a[], int size) {
	int s, i, j;
	double tmp;
	perm = 0; comp = 0;
	for (s = size / 2; s > 0; s /= 2) {  //Выбираем шаг между элементами
		for (i = s; i < size; i++) {
			comp++;
			for (j = i - s; j >= 0 && a[j] > a[j + s]; j -= s) { //Сравниваем элементы и меняем нужные
				tmp = a[j];
				a[j] = a[j + s];
				a[j + s] = tmp;
				perm++;
			}
		}
	}

	for (i = 0; i < size; i++) {
		printf("%lf /", a[i]);
	}
	printf("Number of permition %d\n", perm);
	printf("Number of comparisons %d\n", comp);
	system("pause");
}

void Merge(double a[], int left,int mid, int right) {
	int size = right - left + 1, i = left, j = mid + 1, k = 0,f;
	double *tmp = (double*)malloc(size * sizeof(double));
	while (i <= mid && j <= right) {
		if (a[i] < a[j]) {
			tmp[k++] = a[i++];
		}
		else {
			tmp[k++] = a[j++];
		}
	}
		for (; i <= mid;) {
			tmp[k++] = a[i++];
		}
		for (; j <= right;) {
			tmp[k++] = a[j++];
		}
		for(f=0;f<=size;f++){
	    a[f]= tmp[f];
		printf("%lf", a[f]);
	}
	
}

void mergesort(double* a, int left, int right) {
	int mid = (left + right) / 2,i;  //найди и перепиши по- человечески
	if (left >= right) {
		return;
	}
	mergesort(a, left, mid);
	mergesort(a, mid + 1, right);

	Merge(a, left, mid, right);
}

void Radix(double a[], int size) {

}

void main() {
	int size, variant,i;
	double *a = NULL;
	printf("enter the size of the array\n");
	scanf_s(" %d", &size);
	a = (double*) malloc(size * sizeof(double));
	Randomize(a, size);
	do
	{
		system("cls");
		printf("Select the sort type\n");
		printf("1.Selection\n");
		printf("2.Shell\n");
		printf("3.Merge\n");
		printf("4.Radix\n");
		printf("5.Randomize array\n");
		printf("6.Change size\n");
		printf("0.Exit\n");
		scanf_s(" %d", &variant);
			switch (variant)
			{
			case 1:
				Selection(a, size);
				break;
			case 2:
				Shell(a, size);
				break;
			case 3:
				mergesort(a,0,size-1);
				printf("Number of permition %d\n", perm);
				printf("Number of comparisons %d\n", comp);
				for (i = 0; i < size; i++) {
					printf("%lf /", a[i]);
				}
				system("pause");
				break;
			case 4:
				Radix(a, size);
				break;
			case 5:
				Randomize(a, size);
				break;
			case 6:
				free(a);
				printf("enter the size of the array\n");
				scanf_s(" %d", &size);
				a = (double*)malloc(size * sizeof(double));
				Randomize(a, size);
				break;
			case 0:
				break;
			default:
				printf("incorrent choice"); // проверка на ошибочные вводы
				break;
			}
	} while (variant != 0);
	
}
