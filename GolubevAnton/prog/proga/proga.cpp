#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

typedef double(*function)(double, double, int);

double sinx(double xg, double x, int i)
{
    return xg * (-1 * x * x / ((2.0 * i) * (2.0 * i + 1.0)));
}

double cosx(double xg, double x, int i)
{
    return xg * (-1 * x * x / ((2.0 * i) * (2.0 * i - 1.0)));
}

double expx(double xg, double x, int i)
{
    return xg * (x / i);
}

double lnx(double xg, double x, int i)
{
    return xg * (-1 * x * i / (i + 1.0));
}

void create(double* array, int n, function res, double param)
{
    for (int i = 1; i < n; i++)
    {
        array[i] = res(array[i - 1], param, i);
    }
}

double straight(double* array, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    return sum;
}

double inverse(double* array, int n)
{
	double sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += array[n - i];
	}
	return sum;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    double x, res, sum=0, obr;
    int select, n = 100;
    double* array = NULL;

    printf("Что вычислить:\n1 - синус \n2 - косинус \n3 - экспонента \n4 - натуральный логарифм от 1+х (-1<x<=1)\n");
    scanf_s("%d", &select);
    printf("Введите число:");
    scanf_s("%lf", &x);

    array = (double*)malloc(n * sizeof(double));

    switch (select)
    {
    case(1):
    {
        array[0] = x;
        create(array, n, sinx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        printf("Результат: %.16lf\n", res);
        printf("Погрешность: %.31lf\n", (sin(x) - res));
        if (res < 0)
        {
            printf("Относительная погрешность: %.16lf%%\n", ((sin(x) - res) / res) * -100.0);
        }
        else
        {
            printf("Относительная погрешность: %.16lf%%\n", ((sin(x) - res) / res) * 100.0);
        }
        printf("Обратный: %.16lf\n", obr);
        break;
    }
    case(2):
    {
        array[0] = 1;
        create(array, n, cosx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        printf("Результат: %.16lf\n", res);
        printf("Погрешность: %.31lf\n", (cos(x) - res));
        if (res < 0)
        {
            printf("Относительная погрешность: %.16lf%%\n", ((cos(x) - res) / res) * -100.0);
        }
        else
        {
            printf("Относительная погрешность: %.16lf%%\n", ((cos(x) - res) / res) * 100.0);
        }
        printf("Обратный: %.16lf\n", obr);
        break;
    }
    case(3):
    {
        array[0] = 1;
        create(array, n, expx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        printf("Результат: %.16lf\n", res);
        printf("Погрешность: %.31lf\n", (exp(x) - res));
        printf("Относительная погрешность: %.16lf%%\n", ((exp(x) - res) / res) * 100.0);
        printf("Обратный: %.16lf\n", obr);
        break;
    }
    case(4):
    {
        array[0] = x;
        create(array, n, lnx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        printf("Результат: %.16lf\n", res);
        printf("Погрешность: %.31lf\n", (log(1 + x) - res));
        if (res < 0)
        {
            printf("Относительная погрешность: %.16lf%%\n", ((log(1 + x) - res) / res) * -100.0);
        }
        else
        {
            printf("Относительная погрешность: %.16lf%%\n", ((log(1 + x) - res) / res) * 100.0);
        }
        printf("Обратный: %.16lf\n", obr);
        break;
    }
    }
}