#include <stdio.h>
#include <cmath>

#define col 200

double exp_next(double x, double prev, int n) {

	return (prev * x) / (double(n));
}
double ln_next(double x, double prev, int n) {
	double res = -((prev * double(n - 1) * x) / double(n));
	//printf("%lf ;%lf;%lf;%d \n", res,prev,x,n);
	return res;
}

double sin_next(double x, double prev, int n) {
	if (n % 2 == 1) {
		double res = (0 - 1) * (prev * x * x) / (double(n * (n - 1)));
		return res;
	}
	else {
		return 0;
	}
}
double cos_next(double x, double prev, int n) {
	if (n % 2 == 1) {
		return 0;
	}
	else {
		double res = (0 - 1) * (prev * x * x) / (double(n * (n - 1)));
		return res;
	}

}

void fillarray(double* array, int n, int func, double x) {
	for (int i = 0; i < n; i++) {
		array[i] = double(0);
	}
	if (func == 1) {
		array[0] = 1;

		for (int i = 1; i < n; i++) {
			array[i] = exp_next(x, array[i - 1], i);

		}
	}
	if (func == 2) {

		array[0] = 0;
		array[1] = x;
		for (int i = 2; i < n; i++) {
			array[i] = ln_next(x, array[i - 1], i);

		}
	}
	if (func == 3) {
		array[0] = 0;
		array[1] = x;
		for (int i = 2; i < n; i++) {
			array[i] = sin_next(x, array[i - 2], i);

		}
	}
	if (func == 4) {
		array[0] = 1;
		array[1] = 0;
		for (int i = 2; i < n; i++) {
			array[i] = cos_next(x, array[i - 2], i);

		}
	}
}

void printarray(double* array, int n) {
	for (int i = 0; i < n; i++) {
		printf("%.20f \n", array[i]);
	}
}

double sumarray(double* array, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += array[i];
	}
	return sum;
}
void error_check(double res, double(*original)(double x), double x) {
	printf("absolute error - %.20lf\n", fabs(original(x) - res));
	printf("relative error - %.20lf %% \n", fabs(original(x) - res) / original(x) * 100);
}

int main() {
	double x;
	printf("enter x\n");
	scanf_s("%lf", &x);
	int n;
	printf("enter steps amount\n");
	scanf_s("%d", &n);

	double a[col];
	double sum;
	int ff;
	printf("choose function\n1 - exp\n2 - ln\n3 - sin\n4 - cos\n");
	scanf_s("%d", &ff);

	if (ff == 1) {
		fillarray(a, n, 1, x);
		sum = sumarray(a, n);
		printf("exp = %.10lf \n", sum);
		error_check(sum, exp, x);
	}
	if (ff == 2) {
		if ((abs(x)) < 1.0) {
			fillarray(a, n, 2, x);
			sum = sumarray(a, n);
			printf("ln = %.10lf \n", sum);
			error_check(sum, log, x + 1);
		}
		else {
			printf("ln not defined (|x|>1) \n");
		}
	}
	if (ff == 3) {
		fillarray(a, n, 3, x);
		sum = sumarray(a, n);
		printf("sin = %.10lf \n", sum);
		error_check(sum, sin, x);
	}
	if (ff == 4) {
		fillarray(a, n, 4, x);
		sum = sumarray(a, n);
		printf("cos = %.10lf \n", sum);
		error_check(sum, cos, x);
	}
	return 0;
}