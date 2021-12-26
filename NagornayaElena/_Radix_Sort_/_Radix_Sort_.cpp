#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

const int n = 30, col_razr = 3;
int velich_razr(int chislo, int razr)
{
    while (razr > 1)
    {
        chislo /= 10;
        razr--;
    }
    return chislo % 10;
}

void sort_razr(float dop_mas[n][n], float mas[n], int razr)
{
    int mas_col[n], i, j, temp = 0;
    for (i = 0; i < n; i++)
        mas_col[i] = 0;
    for (i = 0; i < n; i++)
    {
        int a = velich_razr(mas[i], razr);
        dop_mas[mas_col[a]][a] = mas[i];
        mas_col[a]++;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < mas_col[i]; j++)
        {
            mas[temp] = dop_mas[j][i];
            temp++;
        }
}

int main()
{
    int razr, i, j, k=0, sravn=0;
    float A[n],B[n], tmp;
    float dop_mas[n][n];
    srand(1000);
    for (i=0; i<n; i++)
    {
        A[i] = rand() % 1000;
        B[i] = A[i];
        printf("%.0f  ", A[i]);
    }
    for (razr = 1; razr < 4; razr++)
    {
        sravn = sravn + 3*n;
        sort_razr(dop_mas, A, razr);
    }
    printf("\n");
    for (i = 0; i < n; i++)
        printf("%.0f  ", A[i]);
    printf("\n");
    for (i = 0; i < n - 1; i++)
        for (j = n - 2; j > (i - 1); j--)
            if (B[j] > B[j + 1]) {
                tmp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = tmp;
            }
    for (i = 0; i < n; i++) {
        if (A[i] == B[i]) { k = k + 1; };
        printf("%.0f  ", B[i]);
    }
    printf("\n");
    if (k == n) { printf("Correct"); }
    else { printf("No correct"); }
    printf("\n");
    printf("%i  %i", n, sravn);
    return 0;
}
