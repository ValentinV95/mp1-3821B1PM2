#include <iostream>
#include <math.h>
#define pi 3.14159265358979323846




float absolute_pogr(float a, float b)
{
    float e = 0;

    e = abs(abs(a) - abs(b));

    return e;

}

float otn_pogr (float a, float b)
{
    float e = 0;
    e = abs(b / a);
    return e;
}
 
 float period(float x)
 {
     if (x > 2 * pi)
     {
         while (x > 2 * pi)
         {
             x -= 2 * pi;
         }
         return x;
     }
     else
     {
         return x;
     }
 }

void my_sin(float x,float* mas)
{
    x = period(x);

    mas[0] = x;
    for (int i = 1; i < 150; i++)
    {
        mas[i] = mas[i - 1] *(-1)* pow(x, 2) / ((2. * i + 1.) * (2. * i));
    }
    
}

void my_cos(float x, float* mas)
{
    x = period(x);

    mas[0] = 1;
    for (int i = 1; i < 150; i++)
    {
        mas[i] = mas[i - 1] * (-1) * pow(x, 2) / ((2 * i) * (2 * i - 1.));
    }

}

void my_exp(float x, float* mas)
{
    mas[0] = 1;
    for (int i = 1; i < 150; i++)
    {
        mas[i] = mas[i - 1] * x / i;
    }
}

void my_ln(float x, float* mas)
{
    mas[0] = 0;
    for (int i = 1; i < 150; i++)
    {
        mas[i] = (pow(-1, i - 1) * pow(x, i)) / i;
    }
}

float straight_sum(float* mas, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mas[i];
    }
    return sum;

}



float double_sum(float* mas, int n)
{
    float sum = 0;
    for (int i =0; i < n-1; i+=2)
    {
        sum += mas[i] + mas[i + 1];
    }
    return sum;
}

float reverse_sum(float* mas, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mas[n - i-1];
    }
    return sum;
}

enum function 
{
    SIN =1,
    COS,
    EXP,
    LN
};


int main()
{
    float x;
    float* mas;
    float sum;
    enum function func_num;
    
    
    while (1)
    {
        printf("choose function: \n1) sin\n2) cos\n3) exp\n4)ln\nenter: ");
        scanf_s("%d", &func_num);
        switch (func_num)
        {

        case SIN:
            printf("enter x: ");
            scanf_s("%f", &x);
            mas = (float*)malloc(150 * sizeof(float));
            sum = 0;
            my_sin(x, &mas[0]);
            sum = straight_sum(&mas[0], 150);
            printf("straight sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(sin(x),sum), absolute_pogr(sin(x),sum));
            sum = reverse_sum(&mas[0], 150);
            printf("reverse sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(sin(x), sum), absolute_pogr(sin(x), sum));
            sum = double_sum(&mas[0], 150);
            printf("double sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(sin(x), sum), absolute_pogr(sin(x), sum));
            
            printf("standart sin: %f \n\n", sin(x));
            free(mas);
            break;

        case COS:
            scanf_s("%f", &x);
            mas = (float*)malloc(150 * sizeof(float));
            sum = 0;
            my_cos(x, &mas[0]);
            sum = straight_sum(&mas[0], 150);
            printf("straight sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(cos(x), sum), absolute_pogr(cos(x), sum));
            sum = reverse_sum(&mas[0], 150);
            printf("reverse sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(cos(x), sum), absolute_pogr(cos(x), sum));
            sum = double_sum(&mas[0], 150);
            printf("double sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(cos(x), sum), absolute_pogr(cos(x), sum));
            printf("standart cos: %f \n\n", cos(x));
            free(mas);
            break;

        case EXP:
            scanf_s("%f", &x);
            mas = (float*)malloc(150 * sizeof(float));
            sum = 0;
            my_exp(x, &mas[0]);
            sum = straight_sum(&mas[0], 150);
            printf("straight sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(exp(x), sum), absolute_pogr(exp(x), sum));
            sum = reverse_sum(&mas[0], 150);
            printf("reverse sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(exp(x), sum), absolute_pogr(exp(x), sum));
            sum = double_sum(&mas[0], 150);
            printf("double sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(exp(x), sum), absolute_pogr(exp(x), sum));
            printf("standart exp: %f \n\n", exp(x));
            free(mas);
            break;

        case LN:
            scanf_s("%f", &x);
            mas = (float*)malloc(150 * sizeof(float));
            sum = 0;
            my_ln(x, &mas[0]);
            sum = straight_sum(&mas[0], 150);
            printf("straight sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(log(x+1), sum), absolute_pogr(log(x+1), sum));
            sum = reverse_sum(&mas[0], 150);
            printf("reverse sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(log(x + 1), sum), absolute_pogr(log(x + 1), sum));
            sum = double_sum(&mas[0], 150);
            printf("double sum: %f  relative error: %f   absolute error: %f\n", sum, otn_pogr(log(x + 1), sum), absolute_pogr(log(x + 1), sum));
            printf("standart ln: %f \n\n", log(x + 1));
            free(mas);
            break;

        default:
            break;
        }

    }
    
}

