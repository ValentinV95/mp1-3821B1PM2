#include<stdio.h>
#include<time.h>
#include<malloc.h>

#define L 10

int comp = 0;
int mov = 0;



void swap(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}
int partition(float arr[], int low, int high)
{
    
    float pivot = arr[high];
    mov++;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        comp++;
        if (arr[j] <= pivot)
        {
            comp++;
            i++;
            swap(&arr[i], &arr[j]);
            mov+=3;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    mov+=3;
   
    return (i + 1);
   
}
void QuickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        comp++;
        int pi = partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}
void PrintArr(float arr[], int n) 
{
    int i;
    for (i = 0; i < n; i++)
        printf("%.3f ", arr[i]);

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
    int i, n = L;
   
    srand(time(0));

    for (i = 0; i < n; i++)
    {
        arr[i] = pow(-1, i) * (rand() % 1000 / 100.0 + (rand() % 1000) / 1000.0);
        arr_dup[i] = arr[i];
    }
    printf("Original array: ");
    PrintArr(arr, n);

    QuickSort(arr, 0, n-1);
    qsort(arr_dup, n, sizeof(float), compare);

    printf("\nSorted array: ");
    PrintArr(arr, n);

    printf("\n qsort array: ");
    PrintArr(arr_dup, n);

    printf("\nnumber of swaps and compares: %i %i\n", mov, comp);

    return 0;
}