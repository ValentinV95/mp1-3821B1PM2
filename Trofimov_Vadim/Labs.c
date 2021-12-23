# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int perm = 0, comp = 0;

void isSort(double a[], int size) {
	int i;
	for (i = 1; i < size; i++) {
		if (a[i] < a[i - 1]) {
			printf("sort order isn't correct!");
			exit(1);
		}
	}
}

double* Randomize(double a[], int size) {
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = (rand() % 2000+(rand()%1000) / 1000.0) - 1000.0 ; // задаём случайное дробное число
	}
	return a;
}

void createCounters(double* in, int* counters, int N) {
	unsigned char* bp = (unsigned char*)in;
	unsigned char* dataEnd = (unsigned char*)(in + N);
	unsigned short int i;

	memset(counters, 0, 256*sizeof(double)*sizeof(long int)); //заполняем память нулями

	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++) {
			counters[256 * i + *(bp++)]++; //считаем сколько встречается одинаковых цифр в кажд разряде
		}
	}
}

void radixPass(short int offset, int N, double* in, double* out, int* count) {
	double* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp; // вспомогательный массив, где находим сколько цифр было перед взятой цифрой
		*cp = s; // или с какой позиции начинаются числа с этой цифрой
		s += c;
	}
	bp = (unsigned char*)in + offset;
	sp = in;
	for (i = N; i > 0; --i, bp = bp + sizeof(double), ++sp) { //сама сортировка подсчетом
		cp = count + *bp; //взять адрес числа (позицию, на которой она находится)
		out[*cp] = *sp; //положить само число по этой позиции в дест
		(*cp)++; //прибавить 1 к текущему значению во вспомогательном массиве
	}
}

void SignedRadixSort(short int offset, int N, double* in, double* out, int* count) {
	double* sp;
	int s = 0, c, i, * cp = count, NumNeg = 0;
	unsigned char* bp;
	for (i = 128; i < 256; i++) {
		NumNeg = NumNeg + count[i];
	}
	s = NumNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
	}
	s = count[255] = 0; cp = count + 254;
	for (i = 254; i >= 128; i--, cp--) {
		*cp += s;
		s = *cp;
	}
	bp = (unsigned char*)in + offset;
	sp = in;
	for (i = N; i > 0; i--, bp += sizeof(double), sp++) {
		cp = count + *bp;
		if (*bp < 128)
		{
			out[*cp] = *sp;
			(*cp)++;
		}
		else
		{
			(*cp)--;
			out[*cp] = *sp;
		}
	}
}

void RadixSort(double* in, double* out, int* counters, int N) {
	int* count;
	unsigned char i;
	int j;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for ( j = 0; j < N; j++) {
			in[j] = out[j];
			perm++;
		}
	}

	count = counters + 256 * i;
	SignedRadixSort(i, N, in, out, count);
	for ( j = 0; j < N; j++) {
		in[j] = out[j];
		perm++;
	}
}

void callradixsort(double* in, int N) {
	double* out = (double*)malloc(N * sizeof(double));
	int* counters = (long*)malloc(sizeof(double) * 256 * sizeof(int));
	RadixSort(in, out, counters, N);
	free(out);
	free(counters);
}

void Selection(double a[],int size) {
	int i,j, min;
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
}

void Shell(double a[], int size) {
	int s, i, j;
	double tmp;
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
}

void merge(double a[], int left, int right) {
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
			perm++;
		}
		else {
			c[step] = a[j++];
			perm++;
		}
	}
	for (step = 0; step < right - left + 1; step++) {
		a[left + step] = c[step];      // переписываем отсортированный буфферный массив в исходный
	}
}

void main() {
	int size, variant,i,step;
	double* a = NULL,*b = NULL;
	printf("enter the size of the array\n");
	scanf_s(" %d", &size);
	a = (double*)malloc(size * sizeof(double));
	b = (double*)malloc(size * sizeof(double));
	Randomize(a, size);
	printf("enter a step of passage\n");
	scanf_s("%d", &step); 
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
				for (i = 2; i-1 < size;i+=step) {
					Randomize(a, i);
					Selection(a, i);
					isSort(a, i);
					//printf("%d;%d\n ", i, comp + perm);
					printf("%d: (%d_%d);%f\n ", i ,comp, perm, (comp+perm)/(float)(i*i));
					comp = 0; perm = 0;
				}
				system("pause");
				break;
			case 2:
				for (i = 2; i-1 < size; i += step) {
					Randomize(a, i);
					Shell(a, i);
					isSort(a,i);
					//printf("%d;%d\n ", i,comp + perm);
					printf("%d: (%d_%d);%f\n ", i, comp, perm, (comp + perm) / (float)(i * i));
					comp = 0; perm = 0;
				}
				system("pause");
				break;
			case 3:
				for (i = 2; i-1 < size; i += step) {
					Randomize(a, i);
					merge(a, 0, i - 1);
					isSort(a, i);
					//printf("%d;%d\n ", i, comp + perm);
					printf("%d: (%d_%d);%f\n ", i, comp, perm, (comp + perm) / (float)(i * log(i)));
					comp = 0; perm = 0;
				}
				system("pause");
				break;
			case 4:
				for (i = 2; i-1 < size; i += step) {
					Randomize(a, i);
					callradixsort(a, i);
					isSort(a, i);
					//printf("%d;%d\n ", i,comp + perm);
					printf("%d: (%d_%d);%f\n ", i, comp, perm, (comp + perm) / (float)(i));
					comp = 0, perm = 0;
				}
				system("pause");
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
				printf("enter a step of passage\n");
				scanf_s("%d", &step);
				break;
			case 0:
				break;
			default:
				printf("incorrent choice\n"); // проверка на ошибочные вводы
				system("pause");
				break;
			}
	} while (variant != 0);	
}