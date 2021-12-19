#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define max_array 100

int compare = 0;
int reshuffle = 0;

// Создание случайного массива
void generate_array(float* array)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < max_array; i++)
    {
        if (i % 2 == 0)
        {
            array[i] = rand() + 1.142 / 0.459;
        }

        else
        {
            array[i] = -(rand() - 14.487 / 0.475);
        }
        printf("%f ", array[i]);
    }
}

// Создание обратно отсортированного массива
void sort_array(float* array)
{
    int i;
    for (i = 0; i < max_array; i++)
    {
        array[i] = max_array - i;
        printf("%f ", array[i]);
    }
}

// Обмен значениями
void swap(float* array, int left, int right)
{
    float temp;

    temp = array[left];
    array[left] = array[right];
    array[right] = temp;
    reshuffle++;;
}

// Быстрая сортировка Хоара
void quicksort(float* array, int first, int last)
{
    if (first < last)
    {
        int left, right;
        float middle;

        left = first;
        right = last;
        middle = array[(left + right) / 2];
        compare++;

        do
        {
            while (array[left] < middle)
            {
                left++;
                compare++;
            }

            while (array[right] > middle)
            {
                right--;
                compare++;
            }

            if (left <= right)
            {
                swap(array, left, right);
                left++;
                right--;
                compare++;
            }
        } while (left <= right);

        compare++;
        quicksort(array, first, right);
        quicksort(array, left, last);
    }
}

// Упрощение вызова сортировки
void qs(float* array)
{
    int first, last;
    first = 0;
    last = max_array - 1;

    quicksort(array, first, last);
}

int main()
{
    int choice;
    float a[max_array];
    int i;
    setlocale(LC_ALL, "Russian");

    printf("Случайный массив(цифра 1) или обратно отсортированный(цифра 2): ");
    scanf_s("%d", &choice);
    printf("Сгенерированный массив:\n");
    if (choice == 1)
    {
        generate_array(a);
    }

    if (choice == 2)
    {
        sort_array(a);
    }

    qs(a);

    // Вывод отсортированного массива
    printf("\n\nОтсортированный массив:\n");
    for (i = 0; i < max_array; i++)
    {
        printf("%f ", a[i]);
    }

    // Подсчет сравнений и перестановок
    printf("\n\nКоличество сравнений = %d", compare);
    printf("\nКоличество перестановок = %d", reshuffle);
    
    return 0;
}