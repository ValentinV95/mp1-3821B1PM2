#include<stdio.h>
void swap(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}
int partition(float arr[], int low, int high)
{
    float pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void QuickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}
void PrintArr(float arr[], int n) 
{
    int i;
    for (i = 0; i < n; i++)
        printf("%.1f ", arr[i]);

}

int main() 
{
    float arr[] = { 88.2, 72.9, 76.3, 12.2, 32.4, 14.0, 20.7, 80.6, 66.5, 86.8 };
    int n,high;
    n = sizeof(arr) / sizeof(arr[0]);
   

    QuickSort(arr, 0, n-1);
    PrintArr(arr, n);

    return 0;
}