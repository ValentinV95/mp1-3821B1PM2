#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#define k 10

#define uint unsigned int
#define uchar unsigned char
#define ushort unsigned short int 

long assig, compare;

int comp(const void* i, const void* j)
{
	float r1 = *(const float*)i;
	float r2 = *(const float*)j;
	return(r1 > r2) - (r1 < r2);

}

void rands(float* arr, int l) {
	int i;
	srand(time(NULL));
	for (i = 0; i < l; i++) {
		arr[i] = pow((float)(-1.0), (float)rand()) * ((rand() % 1000) + ((rand() % 1000) / (float)1000));
	}
}

void cout(float* arr, int i) {
	int j;
	for (j = 0; j < i; j++) {
		printf("%f ", arr[j]);
	}
	printf("\n");
	printf("\n");
}


void createCounters(float* data, long* counters, long N) {
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);
	ushort i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(long));
	while (bp != dataEnd) {
		compare++;
		for (i = 0;i < sizeof(float);i++) {
			counters[256 * i + *(bp++)]++;
			compare++;
			assig++;
		}
	}
}

void radixPass(short Offset, long N, float* source, float* dest, long* count) {
	float* sp;
	long s = 0, c, i, * cp = count;
	uchar* bp;
	for (i = 256;i > 0;--i, ++cp) {
		c = *cp; *cp = s; s += c;
		compare++;
		assig += 3;
	}
	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(uint), ++sp) {
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		compare++;
		assig += 3;
	}
}





void radixSort(float* in, float* out, long* counters, long N) {
	long* count;
	ushort i;
	long j;
	int numNeg, l = 0;
	createCounters(in, counters, N);
	for (i = 0; i < sizeof(float); i++) {
		compare++;
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (j = 0; j < N; j++) {
			in[j] = out[j];
			compare++;
			assig++;
		}
	}
	numNeg = 0; i = N - 1;
	while (in[i] < 0) {
		out[l] = in[i];
		i--;l++;numNeg++;
		compare++;
		assig++;
	}
	for (i = 0;i < N - numNeg;i++) {
		out[l] = in[i];
		l++;
		compare++;
		assig++;
	}
	for (j = 0; j < N; j++) {
		in[j] = out[j];
		compare++;
		assig++;
	}
}


int main() {
	float a[k];
	float b[k];
	float a2[k];
	int c[sizeof(float) * 256];
	int m, r, f = 0;
	rands(a, k);
	cout(a, k);
	for (r = 0; r < k; r++) a2[r] = a[r];
	radixSort(a, b, c, k);
	cout(a, k);
	qsort(a2, k, sizeof(float), comp);
	for (m = 0; m < k; m++) {
		if (a[m] != a2[m])  f = 1;
	}
	if (f == 0) printf("Sort is correct\n\n");
	printf("Quantity of elements: %d\n", k);
	printf("Quantity of compares and assignments: %d\n", compare + assig);
	printf("%d;%d", k, compare + assig);

}