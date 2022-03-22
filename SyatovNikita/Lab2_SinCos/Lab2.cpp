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

double deg(double x, double i)
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
}

double summa_revers(double x, double i, int chose)
{
    double el, sum;
    int _i, sgn, value_step, value_sgn;
    _i = ((int)i);
    sgn = 1;
    sum = 0;
    value_sgn = -1;

    value_step = 2;

    if (chose == 1)
    {
        sum = 1;
        _i++;
        value_sgn = 1;
        value_step = 1;
    }

    if (chose == 3)
    {
        sgn = -1;
        _i++;
        sum = 1;
    }

    el = deg(x, _i) / factorial(_i);

    if (chose == 4)
    {
        _i += 1;
        el = deg(x, _i) / _i;
        sgn = 1;
        value_step = 1;
    }

    for (; _i > 0; _i -= value_step)
    {
        //printf("1\t%lf\n", el*sgn);
        sum += (el * sgn);
        sgn *= value_sgn;
        el = prev(el, _i, x, chose);
        //printf("2\t%lf\n", sum);
    }

    return sum;
}

double summa(double x, double id, int chose)
{
    int i, sgn, fctrl_id;
    double deg_x, factorial;
    double sum = 0;
    int index = (int)id;
    deg_x = x;
    factorial = 1;
    sgn = 1;
    fctrl_id = 0;

    if (chose == 1)
    {
        sum = 1 + x;
        for (i = 2; i < index; i++)
        {
            deg_x *= x;
            factorial *= i;
            sum += (deg_x / factorial);
            printf("%lf\n", sum);
        }

        return sum;
    }

    if (chose == 2)
    {
        sum = x;
        fctrl_id = 3;
    }
    if (chose == 3)
    {
        sum = 1;
        fctrl_id = 2;
        deg_x = 1;
    }
    if (chose == 2 || chose == 3)
    {
        for (i = 1; i < index; i++)
        {
            deg_x *= x * x;
            factorial *= fctrl_id * (fctrl_id - 1);
            sgn *= (-1);
            sum += ((deg_x / factorial) * sgn);
            fctrl_id += 2;
            //printf("%lf\n", sum);
        }

        return sum;
    }

    if (chose == 4)
    {
        sum = x;
        deg_x = x * x;
        sgn = 1;
        for (i = 2; deg_x != INFINITY && i < 50; i++)
        {
            sgn *= -1;
            sum += ((deg_x / i) * sgn);
            deg_x *= x;
            //printf("%lf\n", sum);
        }

        return sum;
    }
}

double exp_sin_cos_ln(double x, int chose)
{
    double pi = 3.14159265358979323846264338327950;
    if (chose == 2 || chose == 3)       //уменьшение косинуса и синуса до 2пи
        while (x >= (2 * pi))
            x -= (2 * pi);

    return summa_revers(x, MAX_FCTRL, chose);
    //return summa(x, MAX_FCTRL, chose);
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
        printf("относительная погрешность: %.16lf %%", fabs(((exp(x) - res) / res) * 100));
        break;
    }
    case(2):
    {
        res = exp_sin_cos_ln(x, select);
        printf("Результат: %lf\n", res);
        printf("должно быть: %lf\n", sin(x));
        printf("абсолютная погрешность: %.16lf\n", fabs(sin(x) - res));
        printf("относительная погрешность: %.16lf %%", fabs(((sin(x) - res) / res) * 100));
        break;
    }
    case(3):
    {
        res = exp_sin_cos_ln(x, select);
        printf("Результат: %lf\n", res);
        printf("должно быть: %lf\n", cos(x));
        printf("абсолютная погрешность: %.16lf\n", fabs(cos(x) - res));
        printf("относительная погрешность: %.16lf %%", fabs(((cos(x) - res) / res) * 100));
        break;
    }
    case(4):
    {
        res = exp_sin_cos_ln(x, select);
        printf("Результат: %lf\n", res);
        printf("должно быть: %lf\n", log(1 + x));
        printf("абсолютная погрешность: %.16lf\n", fabs(log(1 + x) - res));
        printf("относительная погрешность: %.16lf %%", fabs(((log(1 + x) - res) / res) * 100));
        break;
    }
    default:
    {
        printf("ERROR");
        break;
    }
}
