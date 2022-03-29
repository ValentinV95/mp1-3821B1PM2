// sin_cos_exp_ln.c:

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX_FCTRL 14

double factorial(double i)
{
    double result = 1;
    for (; i > 1; i--)
        result *= i;
    return result;
}

double deg(double x, int i)
{
    double result = 1;
    for (; i > 0; i--)
        result *= x;
    return result;
}

double prev(double next, double i, double x, int chose)
{
    if (chose == 1)
        return ((next * i) / x);
    if (chose == 2 || chose == 3)
        return ((next * i * (i - 1)) / (x * x));
    if (chose == 4)
        return ((next * i) / x) / (i - 1);
    
    return 0;
}

double next(double prev, double i, double x, int chose)
{
    if (chose == 1)
    {
        return ((prev * x) / (i+1));
    }
    if (chose == 2 || chose == 3)
    {
        return (prev * x * x) / (i) / (i + 1);
    }
    if (chose == 4)
    {
        return (prev * x) * (i - 1) / i;
    }

    return 0;
}

double summa_pair(double x, double i, int chose)
{
    double sum, sum_res, el1, el2;
    int step;
    int _i = ((int)i); 
    sum = 0; sum_res = 0; step = 0;
    el1 = 0; el2 = 0;
    
    if (chose == 1)
    {
        sum_res = 1;
        el1 = x;
        el2 = x * x / 2;

        for (i = 0; i < _i; i += 2)
        {
            sum = el1 + el2;
            sum_res += sum;
            el1 = next(el2, i + 2, x, chose);
            el2 = next(el1, i + 3, x, chose);
        }

        return sum_res;
    }

    if (chose == 2)
    {
        el1 = x;
        el2 = x * x * x / (2 * 3);
        step = 3;

        for (i = 1; i < _i; i += 2)
        {
            sum = el1 - el2;
            sum_res += sum;
            el1 = next(el2, i + step, x, chose);
            step += 2;
            el2 = next(el1, i + step, x, chose);
        }

        return sum_res;
    }

    if (chose == 3)
    {
        sum_res = 1;
        el1 = x * x / 2;
        el2 = (el1 * x * x) / (3 * 4);
        step = 4;

        for (i = 1; i < _i; i += 2)
        {
            sum = ((-1)*el1) + el2;
            sum_res += sum;
            el1 = next(el2, i + step, x, chose);
            step += 2;
            el2 = next(el1, i + step, x, chose);
        }

        return sum_res;
    }

    if (chose == 4)
    {
        el1 = x;
        el2 = (x*x) / 2;

        for (i = 1; i < 50; i += 3)
        {
            sum = el1 - el2;
            sum_res += sum;
            el1 = next(el2, i + 2, x, chose);
            el2 = next(el1, i + 3, x, chose);
        }

        return sum_res;
    }

    return 0;
}

double summa_revers(double x, double i, int chose)
{
    double el, sum;
    int _i, sgn;
    _i = ((int)i);
    sgn = 1; el = 0;
    sum = 0;

    if (chose == 1)
    {
        sum = 1;
        _i += 1;
        el = deg(x, _i) / factorial(_i);

        for (; _i > 0; _i -= 1)
        {
            sum += (el * sgn);
            el = prev(el, _i, x, chose);
        }

        return sum;
    }

    if (chose == 2)
    {
        el = deg(x, _i - 1) / factorial(_i - 1);

        for (_i = _i - 1; _i > 0; _i -= 2)
        {
            sum += (el * sgn);
            sgn *= -1;
            el = prev(el, _i, x, chose);
            printf("%lf\n", sum);
        }

        return sum;
    }

    if (chose == 3)
    {
        sgn = -1;
        sum = 1;
        el = deg(x, _i) / factorial(_i);

        for (; _i > 0; _i -= 2)
        {
            sum += (el * sgn);
            sgn *= -1;
            el = prev(el, _i, x, chose);
        }

        return sum;
    }

    if (chose == 4)
    {
        _i += 16;
        el = deg(x, _i) / _i;
        sgn = -1;

        for (; _i > 0; _i -= 1)
        {
            sum += (el * sgn);
            sgn *= -1;
            el = prev(el, _i, x, chose);
        }

        return sum;
    }

    return 0;
}

double summa(double x, double id, int chose)
{
    int i, sgn, index;
    double deg_x, factorial, el;
    double sum = 0;
    index = (int)id;
    factorial = 1;
    sgn = 1;

    if (chose == 1)
    {
        deg_x = x;
        sum = 1 + x;

        for (i = 2; i <= index; i++)
        {
            deg_x *= x;
            factorial *= i;
            sum += (deg_x / factorial);
        }

        return sum;
    }

    if (chose == 2)
    {
        sgn = 1;
        el = x;

        for (i = 1; i <= index-1; i += 2)
        {
            sum += (sgn * el);
            el = (el / (i + 1) / (i+2)) * x * x;
            sgn *= -1;
        }

        return sum;
    }

    if (chose == 3)
    {
        sum = 1;
        el = x * x / 2;
        sgn = -1;

        for (i = 2; i <= index; i += 2)
        {
            sum += (el * sgn);
            el = (el / (i + 1) / (i + 2)) * x * x;
            sgn *= (-1);
        }

        return sum;
    }

    if (chose == 4)
    {
        sum = x;
        el = (x * x) / 2;
        deg_x = x * x;
        sgn = -1;
        for (i = 2; deg_x != INFINITY && i < 30; i++)
        {
            sum += (el * sgn);
            el = ((el * i) * x) / (i + 1);
            sgn *= -1;
            deg_x *= x;
        }

        return sum;
    }

    return 0;
}

double exp_sin_cos_ln(double x, int chose)
{
    /*double pi = 2 * 3.14159265358979323846264338327950;
    if (chose == 2 || chose == 3)       //уменьшение косинуса и синуса до 2пи
        while (x >= pi)
            x -= pi;*/

    //return summa_revers(x, MAX_FCTRL, chose);    
    return summa(x, MAX_FCTRL, chose);
    //return summa_pair(x, MAX_FCTRL, chose);      
}



int main()
{
    double x, res;
    int select;
    setlocale(LC_ALL, "Rus");
    printf("Введите число:");
    scanf_s("%lf", &x);
    printf("Что вычислить:\n1 - экспонента\n2 - синус\n3 - косинус\n4 - натуральный логарифм от 1+х (-1<x<=1)\n");
    scanf_s("%d", &select);

    switch (select)
    {
        case(1):
        {
            res = exp_sin_cos_ln(x, select);
            printf("Результат: %lf\n", res);
            printf("должно быть: %lf\n", exp(x));
            printf("абсолютная погрешность: %.16lf\n", fabs(exp(x) - res));
            printf("относительная погрешность: %.16lf %%", fabs(((exp(x) - res) / exp(x)) * 100));
            break;
        }
        case(2):
        {
            res = exp_sin_cos_ln(x, select);
            printf("Результат: %lf\n", res);
            printf("должно быть: %lf\n", sin(x));
            printf("абсолютная погрешность: %.16lf\n", fabs(sin(x) - res));
            printf("относительная погрешность: %.16lf %%", fabs(((sin(x) - res) / sin(x)) * 100));
            break;
        }
        case(3):
        {
            res = exp_sin_cos_ln(x, select);
            printf("Результат: %lf\n", res);
            printf("должно быть: %lf\n", cos(x));
            printf("абсолютная погрешность: %.16lf\n", fabs(cos(x) - res));
            printf("относительная погрешность: %.16lf %%", fabs(((cos(x) - res) / cos(x)) * 100));
            break;
        }
        case(4):
        {
            res = exp_sin_cos_ln(x, select);
            printf("Результат: %lf\n", res);
            printf("должно быть: %lf\n", log(1 + x));
            printf("абсолютная погрешность: %.16lf\n", fabs(log(1 + x) - res));
            printf("относительная погрешность: %.16lf %%", fabs(((log(1 + x) - res) / log(1 + x)) * 100));
            break;
        }
        default:
        {
            printf("ERROR");
            break;
        }
    }
}