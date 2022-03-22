#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i; const int n = 100;
	double A[100], j, sinus1, sinus2, sinus3, cosinus1, cosinus2, cosinus3, expon1, expon2, expon3, ln1, ln2, ln3, k, x, prov;

	for (j = -10; j < 10; j += 0.1)
	{
		x = j; k = 1;
		printf("%.1lf \n", x);

		//sin(x)
		A[0] = x;
		for (i = 1; i < n; i++)
		{
			k = k + 2;
			A[i] = A[i - 1] * x * x / k / (k - 1) * (-1);
		}

        //1
		sinus1 = A[0];
		for (i = 1; i < n; i++)
		{
			sinus1 += A[i];
		}

		//2
		sinus2 = A[n-1];
		for (i = n-2; i >= 0; i--)
		{
			sinus2 += A[i];
		}

		//3
		sinus3 = 0;
		for (i = 0; i < n; i += 2)
		{
			sinus3 += (A[i] + A[i + 1]);
		}

		prov = sin(x);
		printf("%.30lf; %.30lf; ", (sinus1 - prov), fabs(((sinus1 - prov) / prov)*100));
		printf("%.30lf; %.30lf; ", (sinus2 - prov), fabs(((sinus2 - prov) / prov)*100));
		printf("%.30lf; %.30lf \n",(sinus3 - prov), fabs(((sinus3 - prov) / prov)*100));
		

		//cos(x)
		k = 0;
		A[0] = 1;
		for (i = 1; i < n; i++)
		{
			k = k + 2;
			A[i] = A[i - 1] * x * x / k / (k - 1) * (-1);
		}

		//1
		cosinus1 = A[0];
		for (i = 1; i < n; i++)
		{
			cosinus1 += A[i];
		}

		//2
		cosinus2 = A[n - 1];
		for (i = n - 2; i >= 0; i--)
		{
			cosinus2 += A[i];
		}

		//3
		cosinus3 = 0;
		for (i = 0; i < n; i += 2)
		{
			cosinus3 += (A[i] + A[i + 1]);
		}

		prov = cos(x);
		printf("%.30lf; %.30lf; ", (cosinus1 - prov), fabs(((cosinus1 - prov) / prov)*100));
		printf("%.30lf; %.30lf; ", (cosinus2 - prov), fabs(((cosinus2 - prov) / prov)*100));
		printf("%.30lf; %.30lf \n",(cosinus3 - prov), fabs(((cosinus3 - prov) / prov)*100));


		//exp(x)
		A[0] = 1;
		k = 0;
		for (i = 1; i < n; i++)
		{
			k = k + 1;
			A[i] = A[i - 1] * x / k;
		}

		//1
		expon1 = A[0];
		for (i = 1; i < n; i++)
		{
			expon1 += A[i];
		}

		//2
		expon2 = A[n - 1];
		for (i = n - 2; i >= 0; i--)
		{
			expon2 += A[i];
		}

		//3
		expon3 = 0;
		for (i = 0; i < n; i += 2)
		{
			expon3 += (A[i] + A[i + 1]);
		}
		prov = exp(x);
		printf("%.30lf; %.30lf; ", (expon1 - prov), fabs(((expon1 - prov) / prov)*100));
		printf("%.30lf; %.30lf; ", (expon2 - prov), fabs(((expon2 - prov) / prov)*100));
		printf("%.30lf; %.30lf \n",(expon3 - prov), fabs(((expon3 - prov) / prov)*100));


		//ln(x+1)
		if ((x > -1)&&(x<1))
		{
			A[0] = x;
			k = 1;
			for (i = 1; i < n; i++)
			{
				k = k + 1;
				A[i] = A[i - 1] * x / k * (-1);
			}

			//1
			ln1 = A[0];
			for (i = 1; i < n; i++)
			{
				ln1 += A[i];
			}

			//2
			ln2 = A[n - 1];
			for (i = n - 2; i >= 0; i--)
			{
				ln2 += A[i];
			}

			//3
			ln3 = 0;
			for (i = 0; i < n; i += 2)
			{
				ln3 += (A[i] + A[i + 1]);
			}
			prov = log(x + 1);
			printf("%.30lf; %.30lf; ", (ln1 - prov), fabs(((ln1 - prov) / prov)*100));
			printf("%.30lf; %.30lf; ", (ln2 - prov), fabs(((ln2 - prov) / prov)*100));
			printf("%.30lf; %.30lf \n",(ln3 - prov), fabs(((ln3 - prov) / prov)*100));

		}
	}
   
	return 0;
}
