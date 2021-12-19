#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include <math.h>
#include <string.h>
#include<time.h>
int perest = 0;

void createCounters(double* in, long* count, long N) {
    unsigned char* bp = (unsigned char*)in;
    unsigned char* end = (unsigned char*)(in + N);
    memset(count, 0, 256 * sizeof(double) * sizeof(long));
    while (bp != end) {
        for (int i = 0; i < sizeof(double); i++) {
            count[256 * i + *(bp++)]++;

        }
    }

}

void radixPass(short Offset, long N, double* in, double* out, long* count) {
    double* sp;
    long s, c, * cp;
    unsigned char* bp;
    s = 0;
    cp = count;
    for (int i = 256; i > 0; --i, ++cp) {
        c = *cp;
        *cp = s;
        s += c;
    }
    bp = (unsigned char*)in + Offset;
    sp = in;
    for (int i = N; i > 0; --i, bp += sizeof(double), ++sp) {
        cp = count + *bp;
        out[*cp] = *sp;
        (*cp)++;
        perest++;
    }

}
void signedradixLastPass(short Offset, long N, double* in, double* out, long* count) {
    double* sp;
    long s, c, * cp, numNeg = 0;
    unsigned char* bp;
    for (int i = 128; i < 256; i++) numNeg += count[i];
    s = numNeg;
    cp = count;
    for (int i = 0; i < 128; ++i, ++cp) {
        c = *cp;
        *cp = s;
        s += c;
    }
    cp = count + 255;
    s = 0; *cp = 0;
    for (int i = 255; i >= 128; i--, cp--) {
        s += *cp;
        *cp = s;
    }
    bp = (unsigned char*)in + Offset;
    sp = in;
    for (int i = N; i > 0; i--, bp += sizeof(double), sp++) {
        cp = count + *bp;
        if (*bp < 128) {
            out[*cp] = *sp;
            (*cp)++;
        }
        else {
            (*cp)--;
            out[*cp] = *sp;
        }
        perest++;
    }

}
void radixSort(double* in, double* out, int N) {
    int i;
    long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long));
    long* count;
    createCounters((double*)in, counters, N);
    for (i = 0; i < sizeof(double) - 1; i++) {
        count = counters + 256 * i;
        radixPass(i, N, in, out, count);
        double* tmp = in;
        in = out;
        out = tmp;
    }
    count = counters + 256 * (i);
    signedradixLastPass(i, N, in, out, count);

}
void main()
{
    double mas[] = { 1.021564, 36.12546, 36.56467, -78.312546, -96.3121546, 0, -78.897646, 45.213446, 12.12433, 8976.78699};
    double out_mas[10] = { 1.021564, 36.12546, 36.56467, -78.312546, -96.3121546, 0, -78.897646, 45.213446, 12.12433, 8976.78699 };
    int N = 10;

    int i = 0;
    printf("Array: \n");
    for (i; i < N; i++)
    { 
        printf_s("%.5lf \n", mas[i]);
    }

    radixSort(mas, out_mas, N);

    printf("\n");

    i = 0;
    printf("\n Sorted array: \n");
    for (i; i < N; i++)
    {
        
        printf_s("%.5lf \n ", mas[i]);
    }
    printf("Number of permutations: ");
    printf("%d\n ", perest);

}
