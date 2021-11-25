#include <stdlib.h>
#include <stdio.h>


void comb_sort(double array[], int size)
{
    double factor = 1.2473309;
    int step = size - 1;

    while (step >= 1)
    {
        for (int i = 0; i + step < size; i++)
        {
            if (array[i] > array[i + step])
            {
                double tmp = array[i];
                array[i] = array[i + step];
                array[i + step] = tmp;
            }
        }
        step /= factor;
    }
}

void print(double array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("a[%d] = %lf\n", i, array[i]);
    }
}

int main()
{
    double a[15];
    int i;
    srand(1000);
    for (i = 0; i < 15; i++)
    {
        a[i] = rand() % 10000000 + rand()%10000000 / 10000000.0;
    }
    print(a, 15);
    printf("sorted : \n");
    comb_sort(a, 15);
    print(a, 15);
}