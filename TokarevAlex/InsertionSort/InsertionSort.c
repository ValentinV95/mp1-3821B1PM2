#include<stdio.h>
#include <math.h>
#include<time.h>
#define L 10

int cnt = 0;

void InsertionSort(float arr[], int n) 
{
    int i, j;
    float key;
    for (i = 1; i < n; i++) 
    {
        cnt++;
        key = arr[i];
        cnt++;
        j = i - 1;
        
        while (j >= 0 && arr[j] > key)
        {
            cnt += 2;
            arr[j + 1] = arr[j];
            j = j - 1;
            cnt++;
        }
        arr[j + 1] = key;
        cnt++;
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

int main() {
    float arr[L];
    int n = L;
    int i = 0;
    srand(time(0));

    for (i = 0; i < L; i++) 
    {
        arr[i] = rand() % 1000 / 100.0 + (rand() % 1000) / 1000.0;
    }
    printf("Original array: ");
    PrintArr(arr, n);

    InsertionSort(arr, n);

    printf("\nSorted array: ");
    PrintArr(arr, n);
   
    printf("\nnumber of swaps and compares: %i\n",cnt);

    return 0;
}