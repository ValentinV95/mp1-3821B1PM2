#include<stdio.h>
#include<time.h>
#define L 10

int cnt = 0;

void swap(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}
int partition(float arr[], int low, int high)
{
    
    float pivot = arr[high];
    cnt++;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        cnt++;
        if (arr[j] <= pivot)
        {
            cnt++;
            i++;
            swap(&arr[i], &arr[j]);
            cnt+=3;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    cnt+=3;
   
    return (i + 1);
   
}
void QuickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        cnt++;
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

int main() 
{
    float arr[L];
    int n = L;
    int i = 0, high;
    
    srand(time(0));
    for (i >= 0; i < L; i++) {
        arr[i] = rand() % 1000 / 100 + (rand() % 1000) / 1000.0;
    }
    printf("\nOriginal array: ");
    PrintArr(arr, n);
 
    QuickSort(arr, 0, n-1);

    printf("\nSorted array: ");
    PrintArr(arr, n);

    printf("\nNumber of operations: %i\n", cnt);
   
    return 0;
}