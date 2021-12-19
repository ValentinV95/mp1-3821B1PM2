#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 50
int perest = 0;
void check_array(double array[], int size) {
	for (int i = 1; i < size; i++) {
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

void createCounters(double *data, long int* counters, long int N) {
	unsigned char *bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short int i;
	
	memset(counters, 0, 256 * sizeof(double)*sizeof(long int)); //заполняем память нулями

	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++) {   
			counters[256 * i + *(bp++)]++;   //считаем сколько встречается одинаковых цифр в кажд разряде 
		}
	}
}

void radixPass(short int offset, long int N, double* source, double*dest, long int* count) {
	double*sp;
	long int s = 0, c, i, *cp = count;
	unsigned char *bp;
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
	for (i = N; i > 0; i--, bp += sizeof(double), sp++){
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

	long int * count;
	unsigned char i;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long int j = 0; j < N; j++) {
			in[j] = out[j];
			perest = perest + 1;
		}
	}

	count = counters + 256 * i;
	SignedRadixSort(i, N, in, out, count);
	for (long int j = 0; j < N; j++) {
		in[j] = out[j];
		perest = perest + 1;
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
	printf("source massive:\n");
	for (i = 0; i < M; i++){
		printf("a[%d] = ", i);
		a[i] = (double)(rand()) / RAND_MAX * (2000) - 1000;
		printf("%lf\n", a[i]);
	}
	printf("sorted massive\n");
	callradixsort(a, M);

	for (i = 0; i < M; i++){
		printf("a[%d] = %lf\n", i, a[i]);
	}
	printf("checking of correctness:\n");
	check_array(a, M);
	printf(" perestanovok = %d", perest);
	return 0;
}