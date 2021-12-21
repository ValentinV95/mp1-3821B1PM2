#include <stdio.h>
#include <locale.h>
#define max_numbers 10

int main()
{
    float c[max_numbers], swap, k, m = 0.548;
    int j, i, n = 0, flag, t = 0;
    setlocale(LC_ALL, "Russian");

    printf("Сгенерированный массив: \n");
    // Создание массива
    for (i = 0; i < max_numbers; i++)
    {
        k = i;
        c[i] = m * (max_numbers - k);
        printf("%.3f ", c[i]);
    }

    printf("\n Отсортированный массив: \n");
    //Сортировка по возрастанию
    for (i = 0; i < max_numbers; i++)
    {
        for (j = 0; j < max_numbers - i - 1; j++)
        {
            flag = 0;
            if (c[j] > c[j + 1])
            {
                swap = c[j];
                c[j] = c[j + 1];
                c[j + 1] = swap;
                t++;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            t++;
            break;
        }
    }

    for (i = 0; i < max_numbers; i++)
    {
        printf("%.3f ", c[i]);
    }

    printf("\nКоличество сравнений = %d", t);
    return 0;
}
