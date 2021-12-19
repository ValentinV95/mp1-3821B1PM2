#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define SIZE 10
int sravn = 0, perest = 0;
//Сортировка 
void quickSort(double* arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last;
        double medium = arr[(left + right) / 2];
        do
        {
            while (arr[left] < medium)
                left++;
            sravn++;
                while (arr[right] > medium)
                right--;
                sravn++;
                if (left <= right)
                    sravn++;
                  
            {
                double tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
                perest++;

            }
        } while (left <= right);
        
        quickSort(arr, first, right);
        quickSort(arr, left, last);
    }
}

int main()
{
    double a[SIZE];
    
    printf("Massiv: \n");
    // Вводим значения элементов массива
    for (int i = 0; i < SIZE; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%lf", &a[i]);
    }
    printf("\n Sorted array: \n");
   
    quickSort(a, 0, SIZE - 1); // Вызов функции сортировки
              // Вывод элементов массива после сортировки
    for (int i = 0; i < SIZE; i++) 
    {
        printf ("%.5lf \n", a[i]);
    }
    printf("\n Number of sravneny = %d", sravn);
    printf("\n Number of perestanovok = %d", perest);
    return 0;
}


