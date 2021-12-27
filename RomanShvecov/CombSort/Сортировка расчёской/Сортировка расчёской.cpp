#include <stdio.h>
#include <stdlib.h> 
#define a_size 5
static void print_result(float array[], int size);
static void comb_sort(float array[], int size);


void main()
{
     
    
    float a[a_size];
    int i;


    srand(1000); 

    for (int i = 0; i < a_size; i++) { 
        a[i] = rand() % 200 + (-100) + rand() % 200 / 200.0;
    }

    for (int i = 0; i < a_size; i++) {
        printf("%f ", a[i]);
    }

    printf("\n");

    comb_sort(a, a_size);

    print_result(a, a_size);

}

void comb_sort(float array[], int size)
{
    double factor = 1.2473309;
    int step = size - 1;
    while (step >= 1) {
        for (int i = 0; i + step < size; i++) {
            if (array[i] > array[i + step]) {
                float tmp = array[i];
                array[i] = array[i + step];
                array[i + step] = tmp;
            }
        }
        step /= factor;
    }
}

void print_result(float array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");
}