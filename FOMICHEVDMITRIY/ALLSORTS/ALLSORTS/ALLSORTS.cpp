#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

int max_array = 1;
long long int compare = 0, reshuffle = 0;

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

//Сортировка слиянием
void merge(float* array, int first, int last)
{
    int middle, left, right, i;
    float* a = (float*)malloc(max_array * sizeof(float));

    middle = (first + last) / 2;
    left = first;
    right = middle + 1;

    for (i = first; i <= last; i++)
    {
        if ((left <= middle) && ((right > last) || (array[left] < array[right])))
        {
            a[i] = array[left];
            left++;
            //reshuffle++;
        }

        else
        {
            a[i] = array[right];
            right++;
            //reshuffle++;
        }
        compare++;
    }

    for (i = first; i <= last; i++)
    {
        array[i] = a[i];
        reshuffle++;
    }

    free(a);
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

// Функция обмена значений
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
        //middle = array[left];
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

// Пузырьковая сортировка
void bs(float* array)
{
    int i, j, flag;
    float tmp;

    for (i = 0; i < max_array; i++)
    {
        for (j = 0; j < max_array - i - 1; j++)
        {
            flag = 0;
            if (array[j] > array[j + 1])
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                compare++;
                reshuffle++;
                flag = 1;

                if (flag == 0)
                {
                    compare++;
                    break;
                }
            }
        }
    }
}

// Упрощение вызова функций
void qs(float* array)
{
    int first, last;
    first = 0;
    last = max_array - 1;

    quicksort(array, first, last);
}

void ms(float* array)
{
    int first, last;

    first = 0;
    last = max_array - 1;
    mergesort(array, first, last);
}

void rs(float* a)
{
    float* b = (float*)malloc(max_array * sizeof(float));

    radixSort(a, b, max_array);

    free(b);
}

// Создание случайного массива
void generate_array(float* array)
{
    int i;
    srand(time(NULL));

    printf("\nСгенерированный массив:\n");

    for (i = 0; i < max_array; i++)
    {
        if (i % 2 == 0)
        {
            array[i] = (float)(rand() + (rand() / 12.14));
            printf(" %f\n", array[i]);
        }

        else
        {
            array[i] = (float)(-(rand() + (rand() / 1.45)));
            printf("%f\n", array[i]);
        }
    }
}

// Создание обратно отсортированного массива
void sort_array(float* array)
{
    int i;
    printf("\nСгенерированный массив:\n");
    for (i = 0; i < max_array; i++)
    {
        array[i] = (float)(max_array - i);

        printf("%f\n", array[i]);
    }
}

// Функция проверки корректности сортировки

int compared(const void* a, const void* b)
{
    return *(float*)a > *(float*)b ? 1 : -1;
}

void correct(float* a, float* b)
{
    int i, flag = 1;

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
        printf("\n\nСортировка работает корректно\n");
    }

    else
    {
        printf("\n\nСортировка работает некорректно\n");
    }
}

// Меню выбора

void inform(short int alg_select, short int sort_select, int max_array)
{
    if (alg_select == 1)
    {
        printf("\n||Выбрано: массив из случайных чисел");
    }

    if (alg_select == 2)
    {
        printf("\nВыбрано: обратно отсортированный массив");
    }

    if (sort_select == 1)
    {
        printf(", сортировка пузырьком\n");
    }

    if (sort_select == 2)
    {
        printf(", быстрая сортировка\n");
    }

    if (sort_select == 3)
    {
        printf(", сортировка слиянием\n");
    }

    if (sort_select == 4)
    {
        printf(", поразрядная сортировка\n");
    }

}

void sort_menu(short int alg_select, short int sort_select, int max_array)
{
    float *array, *brray;
    int i;
    //printf("\nsort_select = %hd, alg_select = %hd, max_array = %d\n", sort_select, alg_select, max_array);

    array = (float*)calloc(max_array, sizeof(float));
    brray = (float*)calloc(max_array, sizeof(float));

    if (alg_select == 1)
    {
        generate_array(array);
    }

    if (alg_select == 2)
    {
        sort_array(array);
    }

    // Дублирование первого массива
    for (i = 0; i < max_array; i++)
    {
        brray[i] = array[i];
    }

    if (sort_select == 1)
    {
        bs(array);
    }

    if (sort_select == 2)
    {
        qs(array);
    }

    if (sort_select == 3)
    {
        ms(array);
    }

    if (sort_select == 4)
    {
        rs(array);
    }

    // Вывод отсортированного массива

    printf("\n\nОтсортированный массив: \n");
    for (i = 0; i < max_array; i++)
    {
        if (array[i] >= 0)
        {
            printf(" %f\n", array[i]);
        }

        else
        {
            printf("%f\n", array[i]);
        }
    }

    //Проверка на корректность функцией correct
    correct(array, brray);

    //Количество сравнений и перстановок
    printf("\nКоличество сравнений = %lld\nКоличество перестановок = %lld\n", compare, reshuffle);

    // Free
    compare = 0;
    reshuffle = 0;
    free(array);
    free(brray);
}

void menu()
{
    short int sort_select = -1, alg_select = -1;

    while (1)
    {
        printf("Выберете тип генерации массива или нажмите 0, чтобы выйти из программы:\n");
        printf("1. Массив из случайных чисел\n2. Обратно отсортированный массив\n\n");
        printf("Ваш выбор: ");
        scanf_s("%hd", &alg_select);

        if (alg_select == 0)
        {
            printf("\n");
            break;
        }

        switch (alg_select) {
        case 1:
        {
            printf("\n|Выбран массив из случайных чисел|\n\n");
            break;
        }

        case 2:
        {
            printf("\n|Выбран обратно отсортированный массив|\n\n");
            break;
        }

        default:
        {
            printf("\nНеверное значение. Повторите попытку.\n\n");
            continue;
        }}

        while (1)
        {
            sort_select = 0;
            inform(alg_select, sort_select, max_array);
            printf("\nВыберете нужную сортировку или нажмите 0, чтобы вернуться к выбору алгоритма генерации массива:\n");
            printf("\n1. Сортировка пузырьком\n2. Быстрая сортировка\n3. Сортировка слиянием\n4. Поразрядная сортировка\n\n");
            printf("Ваш выбор: ");
            scanf_s("%hd", &sort_select);

            if (sort_select == 0)
            {
                printf("\n");
                break;
            }

            switch (sort_select) {
            case 1:
            {
                printf("\n|Выбрана сортировка пузырьком|\n\n");
                break;
            }

            case 2:
            {
                printf("\n|Выбрана быстрая сортировка|\n\n");
                break;
            }

            case 3:
            {
                printf("\n|Выбрана сортировка слиянием|\n\n");
                break;
            }

            case 4:
            {
                printf("\n|Выбрана поразрядная сортировка|\n\n");
                break;
            }

            default:
            {
                printf("\nНеверное значение. Повторите попытку.\n\n");
                continue;
            }}

            while (1)
            {
                inform(alg_select, sort_select, max_array);
                printf("\nВыберете количество элементов в массиве или нажмите 0, чтобы вернуться к выбору сортировки:\n");
                printf("\nВаш выбор: ");
                scanf_s("%d", &max_array);

                if (max_array == 0)
                {
                    printf("\n");
                    break;
                }

                if (max_array < 0)
                {
                    printf("\n|Количество элементов в массиве не может быть отрицательным!!!|\n|Повторите попытку|\n");
                }

                else
                {
                    sort_menu(alg_select, sort_select, max_array);
                    max_array = 0;
                }
            }

        }
    }
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    // Вызов самой программы
    menu();

	return 0;
}
