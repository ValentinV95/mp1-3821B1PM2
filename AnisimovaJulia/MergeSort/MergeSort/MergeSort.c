#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
int sravn = 0;
int perest = 0;
int flag = 0;
int checkflag = 0;
int compare(const void* x1, const void* x2)
{
    return (*(double*)x1 - *(double*)x2);
}
void merge(double* arr, double* second, int p, int q, int t)
{
    int f, i, s, k;
    q = (p + t) / 2; f = p; i = p; s = q + 1;
    while ((f <= q) && (s <= t))
    {
        sravn++;
        if (arr[f] <= arr[s])
        {
            perest++;
            second[i] = arr[f];
            f++;
        }
        else
        {
            perest++;
            second[i] = arr[s];
            s++;
        }
        i++;
    }  if (f > q)
    {
        for (k = s; k <= t; k++)
        {
            perest++;
            second[i] = arr[k];
            i++;
        }
    }
    else
    {
        for (k = f; k <= q; k++)
        {
            perest++;
            second[i] = arr[k];
            i++;
        }
    } for (k = p; k <= t; k++)
    {
        arr[k] = second[k];
    }
}
void mergeSort(double* arr, double* second, int p, int t) {
    if (p < t) {
        int q = (p + t) / 2;
        mergeSort(arr, second, p, q);
        mergeSort(arr, second, q + 1, t);
        merge(arr, second, p, q, t);
    }
}
void checking(double* arr, double* check, int n)
{
    qsort(check, n, sizeof(double), compare);
    for (int i = 0; i < n; i++) {
        if (arr[i] != check[i])
        {
            checkflag = 1;
            break;
        }
        else {
            checkflag = 0;
        }
    }
}
int main()
{
    double a[SIZE];
    printf("Massiv: \n");
    // Заполняем элементы массива
    for (int i = 0; i < SIZE; i++)
    {
        printf("arr[%d]  = ", i);
        scanf("%lf", &a[i]);
    }
    printf("\n Sorted array: \n");
    double* b;
    b = (double*)malloc(SIZE * sizeof(double));

    mergeSort(a, b, 0, SIZE - 1);
    // вызываем функцию сортировки

   // Выводим отсортированный массив
    for (int i = 0; i < SIZE; i++)
        printf(" %.5lf \n ", a[i]);
    if (flag == 1)
    {
        printf("Sorting was performed incorrectly\n");
    }
    else {
        printf("Sorting was performed correctly\n");
    }
    printf("Number of comparisons: ");
    printf("%d\n ", sravn);
    printf("Number of permutations: ");
    printf("%d\n ", perest);
    return 0;

}
