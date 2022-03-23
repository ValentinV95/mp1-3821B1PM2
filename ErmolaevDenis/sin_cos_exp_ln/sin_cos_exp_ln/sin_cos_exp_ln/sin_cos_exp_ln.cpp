#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

float next(char* namefunc, float pre, int i, float x)
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

float first(char* namefunc, float x)
{
    if ((strcmp(namefunc, "sin") == 0) || (strcmp(namefunc, "ln") == 0)) return x;
    if ((strcmp(namefunc, "cos") == 0) || (strcmp(namefunc, "exp") == 0)) return 1.0;
}

float directsum(char* namefunc, float x)
{
    int i = 0;
    float pre = 0, func = 0;
    pre = first(namefunc, x);
    func = first(namefunc, x);
    for (i = 1; i < 101; i++)
    {
        func += next(namefunc, pre, i, x);
        pre = next(namefunc, pre, i, x);
    }
    return func;
}

float reversesum(char* namefunc, float x)
{
    int i = 0;
    float mas[100], last = 0, func = 0;
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

float pairwisesum(char* namefunc, float x)
{
    int i = 0;
    float func = 0, last = 0, mas[100];
    last = first(namefunc, x);
    for (i = 1; i < 101; i++)
    {
        mas[i - 1] = last;
        last = next(namefunc, last, i, x);
    }
    for (i = 2; i < 101; i += 2)
    {
        func += mas[i - 2] + mas[i - 1];
    }
    return func;
}

void printfunc(char* namefunc, float func, float x)
{
    
    if (sin(x) != 0 || cos(x) != 0 || log(x + 1.0) != 0 || exp(x) != 0)
    {
        if (strcmp(namefunc, "sin") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = %.8f%%\n", x, func, fabsf(func - sin(x)), (fabsf(sin(x) - func) / fabsf(sin(x))) * 100.0);
        if (strcmp(namefunc, "cos") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = %.8f%%\n", x, func, fabsf(func - cos(x)), (fabsf(cos(x) - func) / fabsf(cos(x))) * 100.0);
        if (strcmp(namefunc, "exp") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = %.8f%%\n", x, func, fabsf(func - exp(x)), (fabsf(exp(x) - func) / fabsf(exp(x))) * 100.0);
        if (strcmp(namefunc, "ln") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = %.8f%%\n", x, func, fabsf(func - log(x + 1.0)), (fabsf(log(x + 1.0) - func) / fabsf(log(x + 1.0))) * 100.0);
    }
    else
    {
        if (strcmp(namefunc, "sin") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = 0.00000000%\n", x, func, fabsf(func - sin(x)));
        if (strcmp(namefunc, "cos") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = 0.00000000%\n", x, func, fabsf(func - cos(x)));
        if (strcmp(namefunc, "exp") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = 0.00000000%\n", x, func, fabsf(func - exp(x)));
        if (strcmp(namefunc, "ln") == 0) printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = 0.00000000%\n", x, func, fabsf(func - log(x + 1.0)));
    }
}

int main()
{
    char namefunc[4];
    float x = 0.0, func = 0.0;
    int i, type;
    printf("Enter the function name (sin, cos, exp, ln) : ");
    scanf("%s", namefunc);
    if (strcmp(namefunc, "sin") != 0 && strcmp(namefunc, "ln") != 0 && strcmp(namefunc, "cos") != 0 && strcmp(namefunc, "exp") != 0) { printf("ERROR"); return 0; }
    printf("\nEnter x : ");
    scanf_s("%f", &x);
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
