#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void merge(float A[], int p, int q, int r, int& sravn, int& perest)
{
    const int n1 = q - p + 1;
    const int n2 = r - q;
    int i, j, k;
    float L[1000], M[1000];
    for (i = 0; i < n1; i++) L[i] = A[p + i]; sravn++;
    for (j = 0; j < n2; j++) M[j] = A[q + 1 + j]; sravn++;
    i = 0; j = 0; k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            A[k] = L[i];
            i++; sravn++; perest++;
        }
        else
        {
            A[k] = M[j];
            j++; sravn++; perest++;
        }
        k++;
    }
    while (i < n1)
    {
        A[k] = L[i];
        i++; k++; sravn++; perest++;
    }
    while (j < n2)
    {
        A[k] = M[j];
        j++; k++; sravn++; perest++;
    }
}

void mergesort(float A[], int l, int r, int& sr, int& per)
{
    int m;
    if (l < r)
    {
        sr++;
        m = l + (r - l) / 2;
        mergesort(A, l, m, sr, per);
        mergesort(A, m + 1, r, sr, per);
        merge(A, l, m, r, sr, per);
    }
}

void main()
{
    srand(time(0));
    const int n = 5;
    int i, j, k = 0, sravn = 0, perest = 0;
    float A[n], B[n], tmp;
    for (i = 0; i < n; i++)
    {
        A[i] = -100 + rand() % 1000;
        B[i] = A[i];
        printf("%.0f ", A[i]);
    }

    mergesort(A, 0, n - 1, sravn, perest);
    printf("\n");
    printf("Sort: ");
    for (i = 0; i < n; i++)
    {
        printf("%.0f ", A[i]);
    }
    printf("\n");
    for (i = 0; i < n - 1; i++)
        for (j = n - 2; j > (i - 1); j--)
            if (B[j] > B[j + 1])
            {
                tmp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = tmp;
            }
    printf("Check: ");
    for (i = 0; i < n; i++)
    {
        if (A[i] == B[i]) { k = k + 1; };
        printf("%.0f ", B[i]);
    }
    printf("\n ");
    if (k == n) { printf("Correct"); }
    else { printf("No correct"); }
    printf("\n ");
    printf("%i %i %i ", n, sravn, perest);
}