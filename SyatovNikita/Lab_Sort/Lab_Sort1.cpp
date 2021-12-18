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

int separation(float array[], int left, int right)    // разделение массива и кусочная сортировка
{
    int l, r;
    float v;
    v = array[rand() % right];          // выбор рандомного элемента
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

void QuickSort(float arr[], int left, int right)      /* left - левый индекс массива(arr[0]); right - правый индекс массива(arr[size])*/
{
    int sct;                                         // sct(select) - опорный элемент массива
    if (left < right)
    {
        sct = separation(arr, left, right);
        QuickSort(arr, left, sct);                   // сортировка подмассивов
        QuickSort(arr, sct + 1, right);
    }
}

void SelectionSort(float arr[], int size)
{
    int i, j, index;
    for (j = 0; j < size - 1; j++)
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

void merge(float arr[], float second[], int l, int m, int r)
{
    int k, i, j, t, step;
    step = l;
    for (i = l, j = m + 1, k = 0; (i <= m) && (j <= r);)
    {
        if (arr[i] < arr[j])                // слияние отсортированных частей массива в отсортированный массив(second)
            second[k++] = arr[i++];
        else
            second[k++] = arr[j++];
    }
    for (; i <= m; i++)
        second[k++] = arr[i];
    for (; j <= r; j++)
        second[k++] = arr[j];

    for (t = 0; t <= k - 1; t++)            // перемещение сортированного массива в исходный массив
        arr[step++] = second[t];
}

void MergeSort(float arr[], float second[], int left, int right)
{
    if (left < right)
    {
        int middle;
        middle = (left + right) / 2;                // нахождение среднего элемента массива
        MergeSort(arr, second, left, middle);      // поочередный вызов двух частей массива
        MergeSort(arr, second, middle + 1, right);
        merge(arr, second, left, middle, right);    // слияние
    }
}

void createCounters(float data[], long counters[])
{
    unsigned char* bp = (unsigned char*)data;
    unsigned char* dataEnd = (unsigned char*)(data + SIZE);
    unsigned short int i;

    memset(counters, 0, 256 * sizeof(float) * sizeof(long));

    while (bp != dataEnd)
    {
        for (i = 0; i < sizeof(float); i++)
            counters[256 * i + *(bp++)]++;
    }
}

void signedradixPass(float source[], float out[])
{
    unsigned int i, j, index;
    i = 0;
    index = 0;
    while (source[i++] > 0) {}
    for (j = SIZE - 1; j >= i - 1; j--)
        source[index++] = out[j];
    for (j = 0; j < i - 1; j++)
        source[index++] = out[j];
}

void radixPass(short Offset, float source[], float dest[], long count[]) //source - исходная последовательность, 
{                                                                        //dest - отсортирован Offset разряд
    float* sp;
    unsigned char* bp;
    long s, c, i, * cp = count;

    s = 0;
    for (i = 256; i > 0; --i, ++cp)          // формирование вспомогательного массива
    {
        c = *cp;
        *cp = s;
        s += c;
    }
    bp = (unsigned char*)source + Offset;
    sp = source;
    for (i = SIZE; i > 0; --i, bp += sizeof(float), ++sp)
    {
        cp = count + *bp;
        dest[*cp] = *sp;
        (*cp)++;
    }
}

void RadixSort(float in[], float out[], long counters[])
{
    long* count;
    unsigned short int i;
    createCounters(in, counters);

    for (i = 0; i < sizeof(float); i++)        //-1
    {
        count = counters + 256 * i;
        radixPass(i, in, out, count);
        for (long j = 0; j < SIZE; j++)
            in[j] = out[j];
    }
    count = counters + 256 * i;
    signedradixPass(in, out);
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

int main()
{
    int k, select;
    float a[SIZE], secondary[SIZE];
    long counters[sizeof(float) * 256];
    setlocale(LC_ALL, "Rus");
    printf("Ваш массив:\n");
    randomArr(a, SIZE);
    printf("Введите нужную сортировку из списка:\n1 - сортировка выбором\n2 - быстрая сортировка Хоара\n3 - сортировка слиянием\nВаш выбор: ");
    scanf_s("%i", &select);
    switch (select)
    {
    case 1:
        SelectionSort(a, SIZE);
        break;
    case 2:
        QuickSort(a, 0, SIZE - 1);
        break;
    case 3:
        MergeSort(a, secondary, 0, SIZE - 1);
        break;
    case 4:
        RadixSort(a, secondary, counters);
        break;
    default:
        printf("Ошибочка вышла(\n");
        break;
    }
    printf("Результат программы:\n");
    for (k = 0; k < SIZE; k++)
        printf("%f\t", a[k]);

    return 0;
}
