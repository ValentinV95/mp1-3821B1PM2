#include<stdio.h>
#include <math.h>

void InsertionSort(float arr[], int n) {
    int i, j, mov=0;
    float key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        /*Перемещаем элементы от 0 до i-1 ,большие ключа, на одну позицию вперёд */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            mov++;
        }
        arr[j + 1] = key;
    }
    printf("number of swaps:%i\n", mov);
}

void PrintArr(float arr[], int n) {
    int i;
    for (i=0; i < n; i++)
        printf("%.1f ", arr[i]);

}

int main() {

	float arr[] = { 12.2, 72.9, 76.3, 14.0, 32.4, 88.2, 20.7, 80.6, 66.5, 86.8 };
	int n = sizeof(arr) / sizeof(arr[0]);

	InsertionSort(arr, n);
    PrintArr(arr, n);

    return 0;
}