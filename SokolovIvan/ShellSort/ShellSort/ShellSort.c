#include "stdio.h"
#define N 10
int main()
{
	int MarcineCiur[9] = { 1,4,10,23,57,132,301,701,1750 };   // оптимально для N<4000
	float massiv[N];
	int i, j,l, step, zamena,sravnen=0,perestanov=0,shag=0;
	for (i = 0; i < N; i++)
	{
		scanf_s("%f", &massiv[i]);
	}
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
	for (i = 0; i < N; i++)
	{
		printf("%f ", massiv[i]);
	}
	printf("\nkolvo shagov = %d = const(MarcineCiur)   kolvo sravnenii = %d   kolvo perestanovok = %d",shag,sravnen,perestanov);
}