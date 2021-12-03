#include "stdio.h"
#include "stdlib.h"
//необходимые библиотеки
#include "malloc.h"
#include "math.h"


#define uchar unsigned char
#define ushort unsigned short //подключение беззнаковых типов данных
#define ufloat unsigned float
#define C 1364                //максимальная длинна массивов при которой в стеке используется 16380 байт <analize:stecksize "16384"


int zam = 0;
int srv = 0;
//глобальные переменные для подсчета сравнений и перестановок
int sravnen = 0;
int perestanovok = 0;

//функция слияния
void merge(float array[], float second[], int l, int q, int r)
{
	int xl = l, xr = q + 1, k, ks;

	for (k = l; k <= r; k++, srv++)
	{
		ks = 0;
		if (xl == q + 1) { second[k] = array[xr++]; ks = 1; }
		else if (xr == r + 1) { second[k] = array[xl++]; ks = 2; }
		else if (array[xl] < array[xr]) { second[k] = array[xl++]; ks = 3; }
		else second[k] = array[xr++];
		srv += ks;
	}
	for (k = l; k <= r; k++, zam++, srv++) array[k] = second[k];
}
void mergesort(float array[], float second[], int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;
		mergesort(array, second, l, q);
		mergesort(array, second, q + 1, r);
		merge(array, second, l, q, r);
	}
	srv++;
}

//функция сортировки пузырьком
void bubsort(float massiv[], int n)
{
	int i, j, k, sravnen = 0, shag = 0, perestanovok = 0;
	float zamena;
	for (i = 0; i < n - 1; i++)
	{
		k = 0;
		for (j = n - 2; j > i - 1; j--)
		{
			if (massiv[j] > massiv[j + 1])
			{
				zamena = massiv[j];
				massiv[j] = massiv[j + 1];
				massiv[j + 1] = zamena;
				k = 1;
				perestanovok += 1;
			}
			sravnen++;
		}
		shag += 1;
		if (k == 0)
			break;
	}
}

//функция сортировки Шелла с последовательностью Марцина Циура
void shellsort(float massiv[], int N)
{
	int MarcineCiur[9] = { 1,4,10,23,57,132,301,701,1750 };
	int i, j, l, step, sravnen = 0, perestanov = 0, shag = 0;
	float zamena;
	for (i = 0; i < N; i++)

		for (l = 8; l >= 0; l--)
		{
			step = MarcineCiur[l];
			for (i = step; i < N; i++)
			{
				for (j = i - step, sravnen += 1; j >= 0 && massiv[j] > massiv[j + step]; j -= step)
				{
					zamena = massiv[j];
					massiv[j] = massiv[j + step];
					massiv[j + step] = zamena;
					perestanov += 1;
				}
			}
			shag += 1;
		}
}

//функция поразрядной сортировки
void radixPass(short Offset, int N, float* sourse, float* dest, int* count)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp, srv++)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, bp += sizeof(float), ++sp, srv++)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}
int* createCounters(float* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	ushort i;

	int* counters = malloc(256 * sizeof(float) * sizeof(int));
	for (i = 0; i < 256 * sizeof(float); i++, srv++)
	{
		counters[i] = 0;
	}
	srv++;
	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(float); i++, srv++)
		{
			counters[256 * i + *(bp++)]++;
		}
		srv++;
	}

	return counters;
}
void radixSort(float* in, float* out, int N)
{
	int* count;
	ushort i;
	int j;

	int* counters = createCounters(in, N);

	for (i = 0; i < sizeof(float); i++, srv++)
	{
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);

		for (j = 0; j < N; j++, srv++)
		{
			in[j] = out[j];
		}
	}
}
void signedRadixSort(float* in, float* out, int N, float* res)
{
	int i, j, numneg = N, kneg;
	radixSort(in, out, N);
	for (i = 0; i < N; i++, srv++)
	{
		srv++;
		if (out[i] < 0)
		{
			numneg = i;
			break;
		}
	}
	kneg = N - numneg;
	for (i = 0, j = N - 1; i < kneg; i++, j--, srv++) res[i] = out[j];
	for (i = kneg; i < N; i++, srv++) res[i] = out[i - kneg];
}



int main()
{
	float b[C];
	float a[C];                         //пустые массивы в которые будем пихать числа из scanf-а
	float c[C];							//третий только для поразрядной
	int i, f, N = 10;

	//ниже представлена менюшка с выбором сортировки, затем выбором длинны массива(хотя длинна каждого массива уже 1364 -_-;)

	printf("change the sort method\n\n\n1) radix \n2) merge \n3) bubble \n4) shell \n\njust input the number of sort method ");
	scanf_s("%d", &f);
	if (f == 1)//поразрядная сортировка 
	{
		printf("\ninput size of massiv (remember that its scanf (<1364)) ");
		scanf_s("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf_s("%f", &a[i]);
		}
		printf("\n");

		signedRadixSort(a, b, N, c);

		for (i = 0; i < N; i++)
		{
			printf_s("%f ", c[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", srv, zam);
	}
	if (f == 2)//сортировка слияния
	{
		printf("\ninput size of massiv (remember that its scanf (<1364)) ");
		scanf_s("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf_s("%f", &a[i]);
		}
		printf("\n");

		mergesort(a, b, 0, N - 1);

		for (i = 0; i < N; i++)
		{
			printf_s("%f ", a[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", srv, zam);
	}
	if (f == 3)//сортировка пузырьком
	{
		printf("\ninput size of massiv (remember that its scanf (<1364)) ");
		scanf_s("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf_s("%f", &a[i]);
		}
		printf("\n");

		bubsort(a, N);

		for (i = 0; i < N; i++)
		{
			printf_s("%f ", a[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sravnen, perestanovok);
	}
	if (f == 4)//сортировка Шелла
	{
		printf("\ninput size of massiv (remember that its scanf (<1364)) ");
		scanf_s("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf_s("%f", &a[i]);
		}
		printf("\n");

		shellsort(a, N);

		for (i = 0; i < N; i++)
		{
			printf_s("%f ", a[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sravnen, perestanovok);
	}
}
//P.S работает хорошо если не писать -0, выскакивает только одно предупреждение : Предупреждение	C6011	Разыменование пустого указателя "counters"
