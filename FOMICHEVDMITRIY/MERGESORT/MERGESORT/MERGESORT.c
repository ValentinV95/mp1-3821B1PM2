#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define max_array 1000

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
        printf("%f\n", array[i]);
    }
}

// Создание обратно отсортированного массива
void sort_array(float* array)
{
    int i;
    for (i = 0; i < max_array; i++)
    {
        array[i] = max_array - i;
        printf("%f\n", array[i]);
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

// Сортировка слиянием
void merge(float* array, int first, int last)
{
    int middle, left, right, i;
    float a[max_array];

    middle = (first + last) / 2;
    left = first;
    right = middle + 1;

    for (i = first; i <= last; i++)
    {
        if ((left <= middle) && ((right > last) || (array[left] < array[right])))
        {
            a[i] = array[left];
            left++;
            compare++;
            reshuffle++;
        }

        else
        {
            a[i] = array[right];
            right++;
            compare++;
            reshuffle++;
        }
    }

    for (i = first; i <= last; i++)
    {
        array[i] = a[i];
        reshuffle++;
    }
}

void mergesort(float* array, int first, int last)
{
    int middle;

    middle = (first + last) / 2;

    if (first < last)
    {
        mergesort(array, first, middle);
        mergesort(array, middle + 1, last);
        merge(array, first, last);
        compare++;
    }
}

// Упрощение ввода 
void ms(float* array)
{
    int first, last;

    first = 0;
    last = max_array - 1;
    mergesort(array, first, last);
}

int compared(const void* a, const void* b)
{
    return *(float*)a > *(float*)b ? 1 : -1;
}

int main()
{
    int choice;
    float a[max_array];
    float b[max_array];
    int i, flag;
    setlocale(LC_ALL, "Russian");
    flag = 1;
    

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

    for (i = 0; i < max_array; i++)
    {
        b[i] = a[i];
    }

    ms(a);

    // Вывод отсортированного массива
    printf("\n\nОтсортированный массив:\n");
    for (i = 0; i < max_array; i++)
    {
        printf("%f\n", a[i]);
    }

    qsort(b, max_array, sizeof(float), compared);

    for (i = 0; i < max_array; i++)
    {
        if (a[i] != b[i])
        {
            flag = 0;
            printf("\nКак минимум %f элемент отличается от элемента правильной сотировки %f", a[i], b[i]);
        }
    }

    if (flag == 1)
    {
        printf("\nСортировка работает корректно");
    }

    else
    {
        printf("\nСортировка работает некорректно");
    }
    // Подсчет сравнений и перестановок
    printf("\n\nКоличество сравнений = %d", compare);
    printf("\nКоличество перестановок = %d", reshuffle);
     
    return 0;
}
