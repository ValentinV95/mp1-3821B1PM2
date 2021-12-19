// Сортировка выбором(SelectionSort), быстрая сортировка(QuickSort), сортировка слиянием(MergeSort), поразрядная сортировка(RadixSort).
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <memory.h>
#define SIZE 10

void swap(float* f, float* s)
{
    float tmp;
    tmp = *f;
    *f = *s;
    *s = tmp;
}

int separation(float array[], int left, int right, int* swaping, int* check)    // разделение массива и кусочная сортировка
{
    int l, r;
    float v;
    v = array[rand() % right];          // выбор рандомного элемента
    l = left;
    r = right;
    while (l <= r)
    {
        *check += 1;
        while (array[l] < v)
        {
            *check += 1;
            l++;
        }
        while (array[r] > v)
        {
            *check += 1;
            r--;
        }
        if (l >= r)
        {
            *check += 1;
            break;
        }
        *swaping += 1;
        swap(&array[l++], &array[r--]);
    }
    return r;
}

void QuickSort(float arr[], int left, int right, int* swaping, int* check)      // left - левый индекс массива(arr[0]); right - правый индекс массива(arr[size])
{
    int sct;                                         // sct(select) - опорный элемент массива;
    if (left < right)
    {
        *check += 1;
        sct = separation(arr, left, right, swaping, check);
        QuickSort(arr, left, sct, swaping, check);                   // сортировка подмассивов
        QuickSort(arr, sct + 1, right, swaping, check);
    }
}

void SelectionSort(float arr[], int size, int* swaping, int* check)
{
    int i, j, index;
    for (j = 0; j < size - 1; j++)
    {
        *check += 1;
        index = j;
        for (i = j + 1; i < size; i++)                  //нахождение минимального элемента
        {
            if (arr[index] > arr[i])
                *check += 1;
            index = i;
        }
        *swaping += 1;
        swap(&arr[j], &arr[index]);
    }
}

void merge(float arr[], float second[], int l, int m, int r, int* swaping, int* check)
{
    int k, i, j, t, step;
    step = l;
    for (i = l, j = m + 1, k = 0; (i <= m) && (j <= r);)
    {
        *check += 1;
        if (arr[i] < arr[j])                // слияние отсортированных частей массива в отсортированный массив(second)
        {
            *check += 1;
            second[k++] = arr[i++];
            *swaping += 1;
        }
        else
        {
            second[k++] = arr[j++];
            *swaping += 1;
        }
    }
    for (; i <= m; i++)
    {
        second[k++] = arr[i];
        *check += 1;
        *swaping += 1;
    }
    for (; j <= r; j++)
    {
        second[k++] = arr[j];
        *check += 1;
        *swaping += 1;
    }
    for (t = 0; t <= k - 1; t++)            // перемещение сортированного массива в исходный массив
    {
        arr[step++] = second[t];
        *swaping += 1;
        *check += 1;
    }
}

void MergeSort(float arr[], float second[], int left, int right, int* swaping, int* check)
{
    if (left < right)
    {
        int middle;
        middle = (left + right) / 2;                // нахождение среднего элемента массива
        *check += 1;
        MergeSort(arr, second, left, middle, swaping, check);      // поочередный вызов двух частей массива
        MergeSort(arr, second, middle + 1, right, swaping, check);
        merge(arr, second, left, middle, right, swaping, check);    // слияние
    }
}

void createCounters(float data[], long counters[], int* swaping, int* check)
{
    unsigned char* bp = (unsigned char*)data;
    unsigned char* dataEnd = (unsigned char*)(data + SIZE);
    unsigned short int i;

    memset(counters, 0, 256 * sizeof(float) * sizeof(long));

    while (bp != dataEnd)
    {
        *check += 1;
        for (i = 0; i < sizeof(float); i++)
        {
            *check += 1;
            counters[256 * i + *(bp++)]++;
        }
    }
}

void signedradixPass(float source[], float out[], int* swaping, int* check)
{
    unsigned int i, j, index;
    i = 0;
    index = 0;
    while (source[i++] > 0)
        *check += 1;
    for (j = SIZE - 1; j >= i - 1; j--)
    {
        *check += 1;
        source[index++] = out[j];
        *swaping += 1;
    }
    for (j = 0; j < i - 1; j++)
    {
        *check += 1;
        source[index++] = out[j];
        *swaping += 1;
    }
}

void radixPass(short Offset, float source[], float dest[], long count[], int* swaping, int* check) //source - исходная последовательность, 
{                                                                        //dest - отсортирован Offset разряд
    float* sp;
    unsigned char* bp;
    long s, c, i, * cp = count;

    s = 0;
    for (i = 256; i > 0; --i, ++cp)          // формирование вспомогательного массива
    {
        *check += 1;
        c = *cp;
        *cp = s;
        *swaping += 2;
        s += c;
    }
    bp = (unsigned char*)source + Offset;
    sp = source;
    *swaping += 1;
    for (i = SIZE; i > 0; --i, bp += sizeof(float), ++sp)
    {
        *check += 1;
        cp = count + *bp;
        dest[*cp] = *sp;
        *swaping += 2;
        (*cp)++;
    }
}

void RadixSort(float in[], float out[], long counters[], int* swaping, int* check)
{
    long* count;
    unsigned short int i;
    createCounters(in, counters, swaping, check);

    for (i = 0; i < sizeof(float); i++)
    {
        *check += 1;
        count = counters + 256 * i;
        radixPass(i, in, out, count, swaping, check);
        for (long j = 0; j < SIZE; j++)
        {
            *check += 1;
            in[j] = out[j];
            *swaping += 1;
        }
    }
    count = counters + 256 * i;
    signedradixPass(in, out, swaping, check);
}


void randomArr(float arr[], int size)       // генерация массива
{
    int t;
    srand(time(0));
    for (t = 0; t < size; t++)
    {
        arr[t] = pow(-1, rand() % 2) * (rand() % 1001 + (rand() % 1000) / 1000.0);
        printf("%f\t", arr[t]);
    }
    printf("\n");
}

void main()
{
    int k, select, swaping, check;
    float a[SIZE], secondary[SIZE];
    long counters[sizeof(float) * 256];
    swaping = 0;
    check = 0;
    setlocale(LC_ALL, "Rus");
    printf("Ваш массив:\n");
    randomArr(a, SIZE);
    printf("Введите нужную сортировку из списка:\n1 - сортировка выбором\n2 - быстрая сортировка Хоара\n3 - сортировка слиянием\n4 - поразрядная сортировка\nВаш выбор: ");
    scanf_s("%i", &select);
    switch (select)
    {
    case 1:
        SelectionSort(a, SIZE, &swaping, &check);
        break;
    case 2:
        QuickSort(a, 0, SIZE - 1, &swaping, &check);
        break;
    case 3:
        MergeSort(a, secondary, 0, SIZE - 1, &swaping, &check);
        break;
    case 4:
        RadixSort(a, secondary, counters, &swaping, &check);
        break;
    default:
        printf("Ошибочка вышла(\n");
        break;
    }
    printf("Результат программы:\n");
    for (k = 0; k < SIZE; k++)
        printf("%f\t", a[k]);

    printf("\nКоличество сравнений:\n%i\n", check);
    printf("\nКоличество перестановок(присвоений):\n%i", swaping);
}
