#include <iostream>
#include <math.h>
#define pi 3.14159265358979323846


unsigned long long int fac(int a)
{
    unsigned long long int b = 1;
    if (a == 0)
    {
        return 1;
    }
    for (int i = 1; i <= a; i++)
    {
        b *= i;
        
    }
    return b;
}

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

float my_sin1(float x) 
{
    float a = 0;
    
    x = period(x);

    for (int i = 0; i <= 11; i++)
    {       
        a += pow(-1, i) * (pow(x, 2 * i + 1) / fac(2 * i + 1));
    }
    return a;
}

float my_sin2 (float x)
{
    x = period(x);

    float a = x;
    float b = a;
    

    for (float i = 1; i <= 100; i++)
    {
        b = b * (-1)* pow(x, 2) / ((2 * i + 1.) * (2 * i ));
        a += b;

    }
    return a;

}
float my_cos1(float x) //вроде нет проблем
{
    long double a = 0;
    x = period(x);
    for (int i = 0; i <= 11; i++)
    {
        a += (pow(-1, i) * pow(x, 2 * i)) / fac(2*i);

    }
    return a;
}

float my_cos2 (float x)
{
    x = period(x);
    float a = 1;
    float b = a;
    for (float i = 1; i <= 100; i++)
    {
        b = b * (-1) * pow(x, 2) / ((2 * i)*(2*i-1.));
        a += b;

    }
    return a;
}

float my_exp1(float x)
{

    float a = 1;
    for (int i = 1; i <= 11; i++)
    {
        a += pow(x, i) / fac(i);
    }
    return a;
}

float my_exp2(float x) 
{
    long double a = 1;
    long double b = a;
    
    
    for (int i = 1; i <= 150; i++)
    {
        b = b * x / i;
        a += b;  
    }
    return a;
 
}


float my_ln1(float x)
{
    float a = 0;

    for (int i = 1; i <= 11; i++)
    {
        a += (pow(-1, i - 1) * pow(x, i)) / i;
    }
    return a;
}

float my_ln2(float x)
{

    float a = x;
    float b = a;

    for (float i = 1; i <= 100; i++)
    {
        b = b *x* pow(-1, i)*i/(i+1.) ;
        a += b;

    }
    return a;
}




int main()
{
    float x;
    printf("1: sin\n2: cos\n3: exp\n4: ln\n");
    int a = 1;
    while (a)
    {
        int a = 0;

        printf("select function : ");
        scanf_s("%d", &a);
        printf("enter x : ");
        scanf_s("%f", &x);
        

        switch(a)
        {
            case 1:
            
                printf("my sin 1 :%f  absolute error: %f relative error: %f\n", my_sin1(x), absolute_pogr(my_sin1(x),sin(x)), otn_pogr(sin(x),my_sin1(x)));

                printf("my sin 2 : %f absolute error: %f relative error: %f\n", my_sin2(x), absolute_pogr(my_sin2(x), sin(x)), otn_pogr(sin(x), my_sin2(x)));

                printf("standart sin: %f\n", sin(x));

                break;
            
            case 2:
            

                printf("my cos 1: %f  absolute error: %f relative error: %f \n", my_cos1(x), absolute_pogr(my_cos1(x), cos(x)), otn_pogr(cos(x), my_cos1(x)));
                printf("my cos 2: %f  absolute error: %f relative error: %f \n", my_cos2(x), absolute_pogr(my_cos2(x), cos(x)), otn_pogr(cos(x), my_cos2(x)));
                printf("standart cos: %f \n", cos(x));
                break;
            
            case 3:
            
                printf("my exp 1: %f  absolute error: %f relative error: %f \n", my_exp1(x), absolute_pogr(my_exp1(x), exp(x)), otn_pogr(exp(x), my_exp1(x)));
                printf("my exp 2: %f  absolute error: %f relative error: %f \n", my_exp2(x), absolute_pogr(my_exp2(x), exp(x)), otn_pogr(exp(x), my_exp2(x)));
                printf("standart exp: %f \n", exp(x));
                break;
            
            case 4:
            
                printf("my ln1: %f  absolute error: %f relative error: %f \n", my_ln1(x), absolute_pogr(my_ln1(x), log(x+1)), otn_pogr(log(x+1), my_ln1(x)));
                printf("my ln2: %f  absolute error: %f relative error: %f \n",my_ln2(x), absolute_pogr(my_ln2(x), log(x + 1)), otn_pogr(log(x + 1), my_ln2(x)));
                printf("standart ln: %lf\n", log(x+1));
                break;
            
            
        }
    }
}

