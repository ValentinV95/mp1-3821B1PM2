#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define max_array 10000
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

// Поразрядная сортировка

void createCounters(float* data, long* counters, long N)
{
    unsigned char* bp;
    unsigned char* dataend;
    int i;

    bp = (unsigned char*)data;
    dataend = (unsigned char*)(data + N);

    memset(counters, 0, 256 * sizeof(float) * sizeof(long int));

    while (bp != dataend)
    {
        for (i = 0; i < sizeof(float); i++)
        {
            counters[256 * i + *(bp++)]++;
        }
    }
}

void radixPass(short int Offset, long int N, float* source, float* dest, long* count)
{
    float* sp;
    long int s, c, * cp;
    unsigned char* bp;
    int i;

    s = 0;
    cp = count;

    for (i = 256; i > 0; --i, ++cp)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    bp = (unsigned char*)source + Offset;
    sp = source;

    for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
    {
        cp = count + *bp;
        dest[*cp] = *sp;
        (*cp)++;
        reshuffle++;
    }

}
void signedradixLastPass(short Offset, long N, float* source, float* dest, long* count)
{
    float* sp;
    long int s = 0, c, * cp;
    unsigned char* bp;
    int i;

    for (i = 128; i < 256; i++)
    {
        s += count[i];
    }

    cp = count;

    for (i = 0; i < 128; ++i, ++cp)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    cp = count + 255;
    s = 0;
    *cp = 0;

    for (i = 255; i >= 128; i--, cp--)
    {
        s += *cp;
        *cp = s;
    }

    bp = (unsigned char*)source + Offset;
    sp = source;

    for (i = N; i > 0; i--, bp += sizeof(float), sp++)
    {
        cp = count + *bp;

        if (*bp < 128)
        {
            dest[*cp] = *sp;
            (*cp)++;
        }

        else
        {
            (*cp)--;
            dest[*cp] = *sp;
        }
    }
}
void radixSort(float* in, float* out, int N)
{
    int i;
    long int* counters, * count;
    float* tmp;

    counters = (long int*)malloc(sizeof(float) * 256 * sizeof(long int));

    createCounters((float*)in, counters, N);

    for (i = 0; i < sizeof(float) - 1; i++)
    {
        count = counters + 256 * i;
        radixPass(i, N, in, out, count);
        tmp = in;
        in = out;
        out = tmp;
    }

    count = counters + 256 * (i);

    signedradixLastPass(i, N, in, out, count);

}

void rs(float* a)
{
    float b[max_array];

    radixSort(a, b, max_array);
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

    rs(a);

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
    printf("\nКоличество перестановок = %d", reshuffle);

    return 0;
}