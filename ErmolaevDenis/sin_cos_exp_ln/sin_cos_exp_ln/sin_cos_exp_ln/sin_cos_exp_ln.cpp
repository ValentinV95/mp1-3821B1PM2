#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

double next(char* namefunc, double pre, int i, double x)
{
    if (strcmp(namefunc, "sin") == 0) return -1.0 * pre * x * x / (2.0 * i * (2.0 * i + 1.0));
    if (strcmp(namefunc, "cos") == 0) return -1.0 * pre * x * x / ((i * 2.0 - 1.0) * (i * 2.0));
    if (strcmp(namefunc, "ln") == 0) return -1.0 * pre * x * (i / (i + 1.0));
    if (strcmp(namefunc, "exp") == 0)
    {
        if (i == 1) return x;
        else return pre * (x / (i));
    }
}

double first(char* namefunc, double x)
{
    if ((strcmp(namefunc, "sin") == 0) || (strcmp(namefunc, "ln") == 0)) return x;
    if ((strcmp(namefunc, "cos") == 0) || (strcmp(namefunc, "exp") == 0)) return 1;
}

double directsum(char* namefunc, double x)
{
    int i = 0;
    double pre = 0, func = 0;
    pre = first(namefunc, x);
    func = first(namefunc, x);
    for (i = 1; i < 101; i++)
    {
        func += next(namefunc, pre, i, x);
        pre = next(namefunc, pre, i, x);
    }
    return func;
}

double reversesum(char* namefunc, double x)
{
    int i = 0;
    double mas[100], last = 0, func = 0;
    last = first(namefunc, x);
    for (i = 1; i < 101; i++)
    {
        mas[i - 1] = last;
        last = next(namefunc, last, i, x);
    }
    for (i = 100; i > 0; i--)
    {
        func += mas[i - 1];
    }
    return func;
}

double pairwisesum(char* namefunc, double x)
{
    int i = 0;
    double func = 0, func1 = 0, func2 = 0, last = 0, mas[100];
    last = first(namefunc, x);
    for (i = 1; i < 101; i++)
    {
        mas[i - 1] = last;
        last = next(namefunc, last, i, x);
    }
    for (i = 1; i < 101; i++)
    {
        if ((i - 1) % 2 == 0) func1 += mas[i - 1];
        else func2 += mas[i - 1];
    }
    func = func1 + func2;
    return func;
}

void printfunc(char* namefunc, double func, double x)
{
    
    if (sin(x) != 0 || cos(x) != 0 || log(x + 1) != 0 || exp(x) != 0)
    {
        if (strcmp(namefunc, "sin") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = %.16lf\n", x, func, fabs(func - sin(x)), (fabs(sin(x) - func) / fabs(sin(x))) * 100);
        if (strcmp(namefunc, "cos") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = %.16lf\n", x, func, fabs(func - cos(x)), (fabs(cos(x) - func) / fabs(cos(x))) * 100);
        if (strcmp(namefunc, "exp") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = %.16lf\n", x, func, fabs(func - exp(x)), (fabs(exp(x) - func) / fabs(exp(x))) * 100);
        if (strcmp(namefunc, "ln") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = %.16lf\n", x, func, fabs(func - log(x + 1)), (fabs(log(x + 1) - func) / fabs(log(x + 1))) * 100);
    }
    else
    {
        if (strcmp(namefunc, "sin") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = 0.0000000000000000\n", x, func, fabs(func - sin(x)));
        if (strcmp(namefunc, "cos") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = 0.0000000000000000\n", x, func, fabs(func - cos(x)));
        if (strcmp(namefunc, "exp") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = 0.0000000000000000\n", x, func, fabs(func - exp(x)));
        if (strcmp(namefunc, "ln") == 0) printf("\nX = %lf My func = %.16lf Absolute error = %.16lf Relative error = 0.0000000000000000\n", x, func, fabs(func - log(x + 1)));
    }
}

int main()
{
    char namefunc[4];
    double x = 0, func = 0;
    int i, type;
    printf("Enter the function name (sin, cos, exp, ln) : ");
    scanf("%s", namefunc);
    printf("\nEnter x : ");
    scanf_s("%lf", &x);
    if ((strcmp(namefunc, "ln") == 0) && (x >= 1 || x <= -1)) { printf("ERROR: x must be in the range (-1;1)"); return 0; }
    printf("Select the type of summation:\n1 - direct summation \n2 - reverse summation\n3 - pairwise summation\n");
    scanf_s("\n%i", &type);
    switch (type)
    {
    case(1):
    {
        func = directsum(namefunc, x);
        printfunc(namefunc, func, x);
        break;
    }
    case(2):
    {
        func = reversesum(namefunc, x);
        printfunc(namefunc, func, x);
        break;
    }
    case(3):
    {
        func = pairwisesum(namefunc, x);
        printfunc(namefunc, func, x);
        break;
    }
    default:
    {
        printf("error");
        break;
    }
    }
    return 0;
}
