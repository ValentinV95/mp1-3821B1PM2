#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define n       100
#define PI      3.14159265358979323846
#define tos     stright_sum(arr)


double stright_sum(double* mas) {
	int k;
	double res = 0;
	for (k = 0; k < n; k++) {
		res += mas[k];
	}
	return res;
}


double back_sum(double* mas) {
	int k;
	double res = 0;
	for (k = n - 1; k >= 0; k--) {
		res += mas[k];
	}
	return res;
}


double couple_sum(double* mas) {
	int i;
	double res = 0;
	if (n % 2 != 0) {
		for (i = 0;i < n - 2;i += 2) { res += mas[i] + mas[i + 1]; }
	}
	else {
		for (i = 0;i < n - 3;i += 2) { res += mas[i] + mas[i + 1]; }
		res += mas[n - 1];
	}
	return res;
}


double nsin(double prev, int i, double x) {
	double i2 = 2.0 * (double)i;
	return (-1.0) * prev * ((x * x) / (i2 * (i2 + 1.0)));
}


double ncos(double prev, int i, double x) {
	double i2 = 2.0 * (double)i;
	return (-1.0) * prev * ((x * x) / (i2 * (i2 - 1.0)));
}


double nexp(double prev, int i, double x) {
	return prev * (x / (double)i);
}


double nln(double prev, int i, double x) {
	double i2 = (double)i;
	return (-1.0) * prev * (x * i2 / (i2 + 1));
}


double check_err(double a, double b) {
	printf("%.20lf, built-in = %.20lf\n", a, b);
	printf("absolute err: %.20lf\n", (a - b));
	printf("relative err: %.20lf\n", (a - b)/b);
}


int main() {
	double x, sum;
	int c, i;
	printf("Enter x:");
	scanf_s("%lf", &x);
	while (x > 2 * PI) {
		x -= 2 * PI;
	}
	double* arr = (double*)malloc(sizeof(double) * n);
	printf("Choose operation: 1) Sin, 2) Cos, 3) Exp, 4) Ln:");
	scanf_s("\n%d", &c);
	switch (c) {
	case 1:
		arr[0] = x;
		for (i = 1; i < n; i++) { arr[i] = nsin(arr[i - 1], i, x); }
		sum = tos;
		check_err(sum, sin(x));
		free(arr);
		break;
	case 2:
		arr[0] = 1;
		for (i = 1; i < n; i++) { arr[i] = ncos(arr[i - 1], i, x); }
		sum = tos;
		check_err(sum, cos(x));
		free(arr);
		break;
	case 3:
		arr[0] = 1;
		for (i = 1; i < n; i++) { arr[i] = nexp(arr[i - 1], i, x); }
		sum = tos;
		check_err(sum, exp(x));
		free(arr);
		break;
	case 4:
		arr[0] = x;
		for (i = 1; i < n; i++) { arr[i] = nln(arr[i - 1], i, x); }
		sum = tos;
		check_err(sum, log(1.0+x));
		free(arr);
		break;
	}
}