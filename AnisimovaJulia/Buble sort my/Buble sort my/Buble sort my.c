#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define SIZE 10
int flag = 0;
int checkflag = 0;
int sravn = 0;
int perest = 0;
int compare(const void* x1, const void* x2)
{
    return (*(double*)x1 - *(double*)x2);
}
void bubble_sort(double* arr, const size_t size)
{
    for (int i = 0; i < SIZE; i++)
    {
        flag = 0;
        for (int p = 0; p < SIZE - i - 1; p++)
        {
            sravn++;
            if (arr[p] > arr[p + 1])
            {
                perest++;
                double num = arr[p];
                arr[p] = arr[p + 1];
                arr[p + 1] = num;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
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
	double arr[SIZE], num;
    int p, i, n = 0;

	printf("Massiv: \n");
	// Вводим значиния элементов массива
	for (i = 0; i < SIZE; i++)
	{
		printf("arr[%d] = ", i);
		scanf("%lf", &arr[i]);
	}
    printf("\n Sorted array: \n");
    //Сортировка 
    bubble_sort(arr, 0, SIZE - 1);
    for (i = 0; i < SIZE; i++)
    {
        printf("%.5f \n", arr[i]);
    }
    if (flag == 1)
    {
        printf("Sorting was performed incorrectly\n");
    }
    else {
        printf("Sorting was performed correctly\n");
    }

    printf("\n Number of sravneny = %d", sravn);
    printf("\n Number of perestanovok = %d", perest);
    return 0;
}






