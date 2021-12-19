#include<stdio.h>
#include <math.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>

#define L 10

long long swap = 0;
long long comp = 0;

void InsertionSort(float arr[], int n) 
{
    int i, j;
    float key;
    for (i = 1; i < n; i++) 
    {
        comp++;
        key = arr[i];
        swap++;
        j = i - 1;
        
        while (j >= 0 && arr[j] > key)
        {
            comp += 2;
            arr[j + 1] = arr[j];
            j = j - 1;
            swap++;
        }
        arr[j + 1] = key;
        swap++;
    }
   
}

void PrintArr(float arr[], int n) 
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%.3f ", arr[i]);
    }
}
int compare(const void* a, const void* b)
{
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
}

int main() 
{
    float arr[L];
    float arr_dup[L];
    int n = L;
    int i = 0;
    srand(time(0));

    for (i = 0; i < n; i++)
    {
        arr[i] = pow(-1,i)*(rand() % 1000 / 100.0 + (rand() % 1000) / 1000.0);
        arr_dup[i] = arr[i];
    }
    printf("Original array: ");
    PrintArr(arr, n);

    InsertionSort(arr, n);
    qsort(arr_dup,n,sizeof(float),compare);

    printf("\nSorted array: ");
    PrintArr(arr, n);

    printf("\n qsort array: ");
    PrintArr(arr_dup, n);

    printf("\nnumber of swaps and compares: %lli %lli\n", swap, comp);

    return 0;
}