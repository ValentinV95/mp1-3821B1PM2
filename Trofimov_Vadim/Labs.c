# include <stdio.h>
# include <stdlib.h>
# include <time.h>
#define uint  unsigned int
int perm = 0, comp = 0, assign = 0;

/*double compare(const void* x1, const void* x2) {
	return (*(double*)x1 - *(double *)x2);
}

void isSort(double a[], int size) {
	int i;
	double *b = NULL;
	b = (double*)malloc(size * sizeof(double));
	for (i = 0; i < size; i++) {
		b[i] = a[i];
	}
	qsort(b, size, sizeof(double),compare );
	for (i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			print("Not sorted");
			break;
		}
	}
	for (i = 0; i < size; i++) {
		print("%lf", a[i]);
	}
}
*/
double* Randomize(double a[], int size) {
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = (rand() % 2001+(rand()%2000) / 1000.0) - 1000.0 ; // задаём случайное дробное число
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

void merge(double* a, int left, int right) {
	int mid = (right-left) / 2 + left;
	int i = left;
	int j = mid + 1;
	int step = 0;
	double *c = (double*)malloc(right * sizeof(double));
	if (left >= right) return; // если границы массива схлопнулись, выходим из подпрограммы 
	merge(a, left, mid); merge(a, mid + 1, right); // рекурсивно разбиваем массив на подмассивы
	for (step; step < right - left + 1; step++) {
		comp += 3;
		if ((j > right) || ((i <= mid) && (a[i] < a[j]))) { // сортируем элементы массива сравнением двух половин
			c[step] = a[i++];
			assign++;
		}
		else {
			c[step] = a[j++];
			assign++;
		}
	}
	for (step = 0; step < right - left + 1; step++) {
		a[left + step] = c[step];      // переписываем отсортированный буфферный массив в исходный
	}
}

int* createCounters(uint* data, int size) {
	
}

void signedRadixSort(short Offset, long N, double in[], double out[], int size) {

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
				perm = 0; comp = 0;
				merge(a,0,size-1);
				printf("Number of permition %d\n", perm);
				printf("Number of comparisons %d\n", comp);
				for (i = 0; i < size; i++) {
					printf("%lf /", a[i]);
				}
				system("pause");
				break;
			case 4:
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