#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"


float sin_next(float pre, int i, float x)
{
    return -1.0 * pre * x * x / (2.0 * i * (2.0 * i + 1.0));
}

float cos_next(float pre, int i, float x)
{
    return -1.0 * pre * x * x / ((i * 2.0 - 1.0) * (i * 2.0));
}

float ln_next(float pre, int i, float x)
{
    return -1.0 * pre * x * (i / (i + 1.0));
}

float exp_next(float pre, int i, float x)
{
        if (i == 1) return x;
        else return pre * (x / (i));
}

float sin_ln_first(float x)
{
    return x;
}

float cos_exp_first()
{
    return 1.0;
}

float directsum(float* mas)
{
    int i = 0;
    float func = 0;
    for (i = 1; i < 101; i++)
    {
        func += mas[i - 1];
    }
    return func;
}

float reversesum(float* mas)
{
    int i = 0;
    float func = 0;
    for (i = 100; i > 0; i--)
    {
        func += mas[i - 1];
    }
    return func;
}

float pairwisesum(float* mas)
{
    int i = 0;
    float func = 0;
    for (i = 2; i < 101; i += 2)
    {
        func += mas[i - 2] + mas[i - 1];
    }
    return func;
}

void create_mas(float* mas, float(*next)(float, int, float), float x)
{
    int i;
    for (i = 1; i < 100; i++)
    {
        mas[i] = next(mas[i - 1], i, x);
    }
}

void printfunc(float func, double original, float x)
{
    
    if (sin(x) != 0 || cos(x) != 0 || log(x + 1.0) != 0 || exp(x) != 0)
    {
        printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = %.8f%%\n", x, func, fabsf(func - original), (fabsf(original - func) / fabsf(original)) * 100.0);
    }
    else
    {
        printf("\nX = %f My func = %.8f Absolute error = %.8f Relative error = 0.00000000%\n", x, func, fabsf(func - original));
    }
}

enum summ_type
{
    direct,
    reverse,
    pairwise
};

int main()
{
    float mas[100];
    float x = 0.0, func = 0.0;
    int i, a;
    summ_type type;
    printf("Choose function:\n");
    printf("Enter: 1 - sin(x), 2 - cos(x), 3 - exp(x), 4 - ln(1+x)\n");
    scanf_s("%d", &a);
    printf("\nEnter x : ");
    scanf_s("%f", &x);
    switch (a)
    {
    case(1):
        mas[0] = sin_ln_first(x);
        create_mas(mas, sin_next, x);
        printf("Select the type of summation:\n0 - direct summation \n1 - reverse summation\n2 - pairwise summation\n");
        scanf_s("\n%i", &type);
        switch (type)
        {
        case(direct):
        {
            func = directsum(mas);
            printfunc(func, sin(x), x);
            break;
        }
        case(reverse):
        {
            func = reversesum(mas);
            printfunc(func, sin(x), x);
            break;
        }
        case(pairwise):
        {
            func = pairwisesum(mas);
            printfunc(func, sin(x), x);
            break;
        }
        default:
        {
            printf("error");
            break;
        }
        }
        break;
    case(2):
        mas[0] = cos_exp_first();
        create_mas(mas, cos_next, x);
        printf("Select the type of summation:\n0 - direct summation \n1 - reverse summation\n2 - pairwise summation\n");
        scanf_s("\n%i", &type);
        switch (type)
        {
        case(direct):
        {
            func = directsum(mas);
            printfunc(func, cos(x),  x);
            break;
        }
        case(reverse):
        {
            func = reversesum(mas);
            printfunc(func, cos(x), x);
            break;
        }
        case(pairwise):
        {
            func = pairwisesum(mas);
            printfunc(func, cos(x), x);
            break;
        }
        default:
        {
            printf("error");
            break;
        }
        }
        break;
    case(3):
        mas[0] = cos_exp_first();
        create_mas(mas, exp_next, x);
        printf("Select the type of summation:\n0 - direct summation \n1 - reverse summation\n2 - pairwise summation\n");
        scanf_s("\n%i", &type);
        switch (type)
        {
        case(direct):
        {
            func = directsum(mas);
            printfunc(func, exp(x), x);
            break;
        }
        case(reverse):
        {
            func = reversesum(mas);
            printfunc(func, exp(x), x);
            break;
        }
        case(pairwise):
        {
            func = pairwisesum(mas);
            printfunc(func, exp(x), x);
            break;
        }
        default:
        {
            printf("error");
            break;
        }
        }
        break;
    case(4):
        if (x >= 1 || x <= -1) { printf("ERROR: x must be in the range (-1;1)"); return 0; }
        mas[0] = sin_ln_first(x);
        create_mas(mas, ln_next, x);
        printf("Select the type of summation:\n0 - direct summation \n1 - reverse summation\n2 - pairwise summation\n");
        scanf_s("\n%i", &type);
        switch (type)
        {
        case(direct):
        {
            func = directsum(mas);
            printfunc(func, log(x + 1.0), x);
            break;
        }
        case(reverse):
        {
            func = reversesum(mas);
            printfunc(func, log(x + 1.0), x);
            break;
        }
        case(pairwise):
        {
            func = pairwisesum(mas);
            printfunc(func, log(x + 1.0), x);
            break;
        }
        default:
        {
            printf("error");
            break;
        }
        }
        break;
    default:
    {
        printf("error");
        break;
    }
    }
    return 0;
}