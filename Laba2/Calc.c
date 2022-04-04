#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void mas_sin(float *mas, float x)
{
	int i, k = 1;
	mas[0] = x;
	for (i = 1; i < 100; i++)
	{
		k = k + 2;
		mas[i] = mas[i - 1] * x * x / k / (k - 1) * (-1);
	}
}

void mas_cos(float *mas, float x)
{
	int i, k = 0;
	mas[0] = 1;
	for (i = 1; i < 100; i++)
	{
		k = k + 2;
		mas[i] = mas[i - 1] * x * x / k / (k - 1) * (-1);
	}
}

void mas_exp(float *mas, float x)
{
	int i, k = 0;
	mas[0] = 1;
	for (i = 1; i < 100; i++)
	{
		k = k + 1;
		mas[i] = mas[i - 1] * x / k;
	}
}

void mas_ln(float mas[100], float x)
{ 
	int i, k = 1;
	mas[0] = x;
	for (i = 1; i < 100; i++)
	{
		k = k + 1;
		mas[i] = mas[i - 1] * x / k * (-1);
	}
}

float simple_summ(float* mas, int n)
{
	float f = 0; int i;
	for (i = 0; i < n; i++)
	{
		f += mas[i];
	}
	return f;
}

float inverse_summ(float* mas, int n)
{
	float f = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		f += mas[n - i];
	}
	return f;
}

float pairwise_summ(float* mas, int n)
{
	int i;
	float f = 0;

	for (i = 0; i < n - 1; i += 2)
		mas[i] += mas[i + 1];
	if (n % 2 == 1)
		f += mas[i + 2];
	for (i = 0; i < n; i += 2)
		f += mas[i];
	return f;
}

void correct(float f, double prov)
{
	printf("\nАбсолютная погрешность:    %.10f", fabsf(prov - f));
	printf("\nОтносительная погрешность: %.10f %% \n", fabsf(((prov - f) / prov) * 100.f));
}


int main()
{
	int i, fun, sum; const int n = 100; double j, _x, prov;
	float mas[100], sinus, cosinus, expon, ln, k, x;
	setlocale(LC_ALL, "Russian");
	setlocale(LC_NUMERIC, "C");

	printf("");
	printf("Выберите вычисляемую функцию:\n 1.) sin(x) \n 2.) cos(x) \n 3.) exp(x) \n 4.) ln(1+x) \n");
	scanf_s("%d", &fun);
	printf("Введите число для вычисления функции: \n");
	scanf_s("%lf", &_x);
	printf("Выберите способ суммирования:\n 1.) Прямое суммирование \n 2.) Обратное суммирование \n 3.) Попарное суммирование \n");
	scanf_s("%d", &sum);
    x = (float)_x;

	switch (fun)
	{
	case(1):

		mas_sin(mas, x);
		switch (sum)
		{
		case(1):
			sinus = simple_summ(mas, n);
			break;
		case(2):
			sinus = inverse_summ(mas, n);
			break;
		case(3):
			sinus = pairwise_summ(mas, n);
			break;
		}
		printf("\nsin(%.3f) = %.10f", x, sinus);
		prov = sin(_x);
		correct(sinus, prov);
		break;

	case(2):

		mas_cos(mas, x);
		switch (sum)
		{
		case(1):
			cosinus = simple_summ(mas, n);
			break;
		case(2):
			cosinus = inverse_summ(mas, n);
			break;
		case(3):
			cosinus = pairwise_summ(mas, n);
			break;
		}
		printf("\ncos(%.3f) = %.10f", x, cosinus);
		prov = cos(_x);
		correct(cosinus, prov);
		break;

	case(3):

		mas_exp(mas,x);
		switch (sum)
		{
		case(1):
			expon = simple_summ(mas, n);
			break;
		case(2):
			expon = inverse_summ(mas, n);
			break;
		case(3):
			expon = pairwise_summ(mas, n);
			break;
		}
		printf("\nexp(%.3f) = %.10f", x, expon);
		prov = exp(_x);
		correct(expon, prov);
		break;

	case(4):
		if ((x > (-1)) && (x <= 1))
		{
			mas_ln(mas, x);
			switch (sum)
			{
			case(1):
				ln = simple_summ(mas, n);
				break;
			case(2):
				ln = inverse_summ(mas, n);
				break;
			case(3):
				ln = pairwise_summ(mas, n);
				break;
			}
			printf("\nln(1 + %.3f) = %.10f", x, ln);
			prov = log(_x+1);
			correct(ln, prov);
		}
		else printf("\nФункция не вычисляется");
		break;
	}

   return 0;
}
