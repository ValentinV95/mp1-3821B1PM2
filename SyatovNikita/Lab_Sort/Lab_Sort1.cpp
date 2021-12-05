// Сортировка выбором и быстрая сортировка
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void swap(float* f, float* s)
{
    float tmp;
    tmp = *f;
    *f = *s;
    *s = tmp;
}

int separation(float array[], int left, int right)    // разделение массива и кусочная сортировка
{
    int l, r;
    float v;
    v = array[(left + right) / 2];                      // выбор рандомного элемента
    l = left;
    r = right;
    while (l <= r)
    {
        while (array[l] < v)
            l++;
        while (array[r] > v)
            r--;
        if (l >= r)
            break;
        swap(&array[l++], &array[r--]);
    }
    return r;
}

void quicksort(float arr[], int left, int right)      /* left - левый индекс массива(arr[0]); right - правый индекс массива(arr[size])*/
{
    int sct;                                         // sct(select) - опорный элемент массива
    if (left < right)
    {
        sct = separation(arr, left, right);
        quicksort(arr, left, sct);                   // сортировка подмассивов
        quicksort(arr, sct + 1, right);
    }
}

void SelectionSort(float arr[], int size)
{
    int i, j, index;
    for (j = 0; j < size; j++)
    {
        index = j;
        for (i = j + 1; i < size; i++)                  //нахождение минимального элемента
            if (arr[index] > arr[i])
            {
                index = i;
            }
        swap(&arr[j], &arr[index]);
    }
}

void randomArr(float arr[], int size)       // генерация массива
{
    int t;
    srand(time(0));
    for (t = 0; t < size; t++)
    {
        arr[t] = rand() % 1001 + (rand() % 1000) / 1000.0;
        printf("%f\t", arr[t]);
    }
    printf("\n");
}

int main()
{
    int n, k, select;
    float a[10];
    setlocale(LC_ALL, "Rus");
    n = 10;
    printf("Ваш массив:\n");
    randomArr(a, n);
    printf("Введите нужную сортировку из списка:\n1 - сортировка выбором\n2 - быстрая сортировка Хоара\nВаш выбор: ");
    scanf_s("%i", &select);
    switch (select)
    {
    case 1:
        SelectionSort(a, n);
        break;
    case 2:
        quicksort(a, 0, 9);
        break;
    default:
        printf("Ошибочка вышла(\n");
        break;
    }
    printf("Результат программы:\n");
    for (k = 0; k < 10; k++)
        printf("%f\t", a[k]);

    return 0;
}
