#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

typedef float(*function)(float, float, int);

float sinx(float xg, float x, int i)
{
    return xg * (-1 * x * x / ((2.0 * i) * (2.0 * i + 1.0)));
}

float cosx(float xg, float x, int i)
{
    return xg * (-1 * x * x / ((2.0 * i) * (2.0 * i - 1.0)));
}

float expx(float xg, float x, int i)
{
    return xg * (x / i);
}

float lnx(float xg, float x, int i)
{
    return xg * (-1 * x * i / (i + 1.0));
}

void create(float* array, int n, function res, float param)
{
    for (int i = 1; i < n; i++)
    {
        array[i] = res(array[i - 1], param, i);
    }
}

float straight(float* array, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    return sum;
}

float inverse(float* array, int n)
{
    float sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += array[n - i];
    }
    return sum;
}

float pairwise(float* array, int n)
{
    int i, j;
    while (n > 1)
    {
        for (i = 1, j = 0; i < n; i += 2, ++j)
        {
            array[j] = array[i] + array[i - 1];
        }
        n /= 2;
    }
    return array[0];
}

int main()
{
    setlocale(LC_ALL, "Russian");

    float x, res, sum = 0, obr, pair;
    int select, n = 100;
    float* array = NULL;

    printf("Что вычислить:\n\
            1 - синус \n\
            2 - косинус \n\
            3 - экспонента \n\
            4 - натуральный логарифм от 1+х (-1<x<=1)\n");
    scanf_s("%d", &select);
    printf("Введите число:");
    scanf_s("%f", &x);

    array = (float*)malloc(n * sizeof(float));

    switch (select)
    {
    case(1):
    {
        array[0] = x;
        create(array, n, sinx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        pair = pairwise(array, n);
        printf("Результат: %.16f\n", res);
        //printf("Погрешность: %.31f\n", (sin(x) - res));
        printf("Относительная погрешность: %.16f%%\n", ((sin(x) - res) / sin(x)) * 100.0);
        printf("Обратный: %.16f\n", obr);
        printf("Относительная погрешность: %.16f%%\n", ((sin(x) - obr) / obr) * 100.0);
        printf("попарный: %.16f\n", pair);
        printf("Относительная погрешность: %.16f%%\n", ((sin(x) - pair) / sin(x)) * 100.0);

        break;
    }
    case(2):
    {
        array[0] = 1;
        create(array, n, cosx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        pair = pairwise(array, n);
        printf("Результат: %.16f\n", res);
        //printf("Погрешность: %.31f\n", (cos(x) - res));
        printf("Относительная погрешность: %.16f%%\n", ((cos(x) - res) / cos(x)) * 100.0);
        printf("Обратный: %.16f\n", obr);
        printf("Относительная погрешность: %.16f%%\n", ((cos(x) - obr) / cos(x)) * 100.0);
        printf("попарный: %.16f\n", pair);
        printf("Относительная погрешность: %.16f%%\n", ((cos(x) - pair) / cos(x)) * 100.0);

        break;
    }
    case(3):
    {
        array[0] = 1;
        create(array, n, expx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        pair = pairwise(array, n);
        printf("Результат: %.16f\n", res);
        //("Погрешность: %.31f\n", (exp(x) - res));
        printf("Относительная погрешность: %.16f%%\n", ((exp(x) - res) / exp(x)) * 100.0);
        printf("Обратный: %.16lf\n", obr);
        printf("Относительная погрешность: %.16f%%\n", ((exp(x) - obr) / exp(x)) * 100.0);
        printf("попарный: %.16f\n", pair);
        printf("Относительная погрешность: %.16f%%\n", ((exp(x) - pair) / exp(x)) * 100.0);
        break;
    }
    case(4):
    {
        array[0] = x;
        create(array, n, lnx, x);
        res = straight(array, n);
        obr = inverse(array, n);
        pair = pairwise(array, n);
        printf("Результат: %.16f\n", res);
        //printf("Погрешность: %.31f\n", (log(1 + x) - res));
        printf("Относительная погрешность: %.16f%%\n", ((log(1 + x) - res) / log(1 + x)) * 100.0);
        printf("Обратный: %.16lf\n", obr);
        printf("Относительная погрешность: %.16f%%\n", ((log(1 + x) - obr) / log(1 + x)) * 100.0);
        printf("попарный: %.16f\n", pair);
        printf("Относительная погрешность: %.16f%%\n", ((log(1+x) - pair) / log(1+x)) * 100.0);
        break;
    }
    }
}