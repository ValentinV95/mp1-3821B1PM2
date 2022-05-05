// sin_cos_exp.c: 

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX_FCTRL 14
#define TYPE simple    /*simple*/    /*revers*/    /*pairs*/           //смена типа суммирования

double factorial(double i)
{
    double result = 1;
    for (; i > 1; i--)
        result *= i;
    return result;
}

double deg(double* x, int i)
{
    double result = 1;
    for (; i > 0; i--)
        result *= (*x);
    return result;
}

//--------------prev_element-----------------------------\\

double PrevExp(double element, double* x, double i)
{
    if (*x == 0)
        return 0;
    return element * i / *x;
}

double PrevSinCos(double element, double* x, double i)
{
    if (*x == 0)
        return 0;
    return element * i * (i - 1) / (*x * *x);
}

double PrevLog(double element, double* x, double i)
{
    if (*x == 0)
        return 0;
    return element * i / (i - 1) / *x;
}

//-------------------next_element--------------------------\\

double NextSinCos(double element, double* x, double i)
{
    return element / (i + 1) / (i + 2) * (*x) * (*x);
}

double NextExp(double element, double* x, double i)
{
    return element / (i + 1) * (*x);
}

double NextLog(double element, double* x, double i)
{
    return element * i / (i + 1) * (*x);
}

//----------------попарное суммирование--------------------------------\\

void pairs(double* x, double* arr, int choose, int* size)
{
    double el;
    int i, sgn, k;
    k = 0;

    if (choose == 1)
    {
        arr[0] = 1;
        arr[1] = *x;
        k = 2;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL; i+=2)
        {
            arr[k] = el;
            k += 1;
            el = NextExp(el, x, i);
            arr[k++] = el;
            el = NextExp(el, x, i+1);
        }
    }

    if (choose == 2)
    {
        arr[0] = *x;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x) * (*x)) / 6;
        for (i = 3; i <= MAX_FCTRL + 1; i += 4)
        {
            arr[k] = (el * sgn);
            k += 1;
            el = NextSinCos(el, x, i);
            sgn *= -1;
            arr[k] = (el * sgn);
            el = NextSinCos(el, x, i+2);
            sgn *= -1;
            k += 1;
        }
    }

    if (choose == 3)     
    {
        arr[0] = 1;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL; i += 4)
        {
            arr[k] = (el * sgn);
            k += 1;
            el = NextSinCos(el, x, i);
            sgn *= -1;
            arr[k] = (el * sgn);
            el = NextSinCos(el, x, i+2);
            sgn *= -1;
            k += 1;
        }
    }

    if (choose == 4)               
    {       
        arr[0] = *x;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL + 15; i+=2)
        {
            arr[k] = (el * sgn);
            el = NextLog(el, x, i);
            sgn *= -1;
            k += 1;
            arr[k] = (el * sgn);
            el = NextLog(el, x, i+1);
            sgn *= -1;
            k += 1;
        }
    }

    *size = k;
}

//----------------обратный ход--------------------------------\\

void revers(double* x, double* arr, int choose, int* size)
{
    double el;
    int i, sgn, k;
    k = 0;

    if (choose == 1)            //exp
    {
        el = deg(x, MAX_FCTRL) / factorial(MAX_FCTRL);

        for (i = MAX_FCTRL; i > 1; i--)
        {
            arr[k++] = el;
            el = PrevExp(el, x, i);
        }

        arr[k++] = *x + 1;
    }

    if (choose == 2)            //sin
    {
        el = deg(x, MAX_FCTRL + 3) / factorial(MAX_FCTRL + 3);
        sgn = 1;

        for (i = MAX_FCTRL + 3; i >= 1; i -= 2)
        {
            arr[k++] = (el * sgn);
            el = PrevSinCos(el, x, i);
            sgn *= -1;
        }
    }

    if (choose == 3)        //cos
    {
        el = deg(x, MAX_FCTRL + 2) / factorial(MAX_FCTRL + 2);
        sgn = 1;

        for (i = MAX_FCTRL + 2; i > 1; i -= 2)
        {
            arr[k++] = (el * sgn);
            el = PrevSinCos(el, x, i);
            sgn *= -1;
        }

        arr[k++] = 1;
    }

    if (choose == 4)          //ln                  
    {
        el = deg(x, MAX_FCTRL) / (MAX_FCTRL);
        sgn = -1;

        for (i = MAX_FCTRL; i > 1; i--)
        {
            arr[k++] = (el * sgn);
            el = PrevLog(el, x, i);
            sgn *= -1;
        }

        arr[0] = *x;
    }

    *size = k;
}

//--------------------прямой ход-------------------------------\\

void simple(double* x, double* arr, int choose, int* size)
{
    int i, sgn, k;
    double el;

    if (choose == 1)      //exp
    {
        arr[0] = 1;
        arr[1] = *x;
        k = 2;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL; i++)
        {
            arr[k++] = el;
            el = NextExp(el, x, i);
        }
    }

    if (choose == 2)       //sin
    {
        arr[0] = *x;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x) * (*x)) / 6;
        for (i = 3; i <= MAX_FCTRL + 1; i += 2)
        {
            arr[k++] = (el * sgn);
            el = NextSinCos(el, x, i);
            sgn *= -1;
        }
    }

    if (choose == 3)     //cos
    {
        arr[0] = 1;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL; i += 2)
        {
            arr[k++] = (el * sgn);
            el = NextSinCos(el, x, i);
            sgn *= -1;
        }
    }

    if (choose == 4)               //ln
    {
        arr[0] = *x;
        sgn = -1;
        k = 1;
        el = ((*x) * (*x)) / 2;
        for (i = 2; i <= MAX_FCTRL + 16; i++)
        {
            arr[k++] = (el * sgn);
            el = NextLog(el, x, i);
            sgn *= -1;
        }
    }

    *size = k;
}

//----------------------------------------------------------\\

double summa(double* arr,int size)
{
    int i;
    double print = 0;
    for (i = 0; i < size; i++)
        print += arr[i];

    return print;
}

double exp_sin_cos_ln(double x, double* arr, int choose)
{
    int size, i;
    /*double pi = 2 * 3.14159265358979323846264338327950;
    if (chose == 2 || chose == 3)       //уменьшение косинуса и синуса до 2пи
        while (x >= pi)
            x -= pi;*/

    TYPE(&x, arr, choose, &size);

    return summa(arr, size);
}



int main()
{
    double x, arr[MAX_FCTRL + 16], result;
    int select, i;
    setlocale(LC_ALL, "Rus");

    printf("Введите число:");
    scanf_s("%lf", &x);
    printf("Что вычислить:\n1 - экспонента\n2 - синус\n3 - косинус\n4 - натуральный логарифм от 1+х (-1<x<=1)\n");
    scanf_s("%d", &select);

    for (i = 0; i < MAX_FCTRL + 16; i++)
        arr[i] = 0;

    switch (select)
    {
    case(1):
    {
        result = exp_sin_cos_ln(x, arr, select);
        printf("Результат: %lf\n", result);
        printf("должно быть: %lf\n", exp(x));
        printf("абсолютная погрешность: %.16lf\n", fabs(exp(x) - result));
        printf("относительная погрешность: %.16lf %%", fabs(((exp(x) - result) / exp(x)) * 100));
        break;
    }
    case(2):
    {
        result = exp_sin_cos_ln(x, arr, select);
        printf("Результат: %lf\n", result);
        printf("должно быть: %lf\n", sin(x));
        printf("абсолютная погрешность: %.16lf\n", fabs(sin(x) - result));
        printf("относительная погрешность: %.16lf %%", fabs(((sin(x) - result) / sin(x)) * 100));
        break;
    }
    case(3):
    {
        result = exp_sin_cos_ln(x, arr, select);
        printf("Результат: %lf\n", result);
        printf("должно быть: %lf\n", cos(x));
        printf("абсолютная погрешность: %.16lf\n", fabs(cos(x) - result));
        printf("относительная погрешность: %.16lf %%", fabs(((cos(x) - result) / cos(x)) * 100));
        break;
    }
    case(4):
    {
        result = exp_sin_cos_ln(x, arr, select);
        printf("Результат: %lf\n", result);
        printf("должно быть: %lf\n", log(1 + x));
        printf("абсолютная погрешность: %.16lf\n", fabs(log(1 + x) - result));
        printf("относительная погрешность: %.16lf %%", fabs(((log(1 + x) - result) / log(1 + x)) * 100));
        break;
    }
    default:
    {
        printf("ERROR");
        break;
    }
    }
}