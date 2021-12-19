#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define SIZE 10

int main()
{
	double arr[SIZE], num;
    int p, i, n = 0, sravn = 0, perest = 0;

	printf("Massiv: \n");
	// Вводим значиния элементов массива
	for (i = 0; i < SIZE; i++)
	{
		printf("arr[%d] = ", i);
		scanf("%lf", &arr[i]);
	}
    printf("\n Sorted array: \n");
    //Сортировка 
    for (i = 0; i < SIZE; i++)
    {
        for (p = 0; p < SIZE - i - 1; p++)
        {
            sravn++;
            if (arr[p] > arr[p + 1])
            {
                perest++;
                num = arr[p];
                arr[p] = arr[p + 1];
                arr[p + 1] = num;
                
                
            }
            
           
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        printf("%.5f \n", arr[i]);
    }

    printf("\n Number of sravneny = %d", sravn);
    printf("\n Number of perestanovok = %d", perest);

    return 0;
}



