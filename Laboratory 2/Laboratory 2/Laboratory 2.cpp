#include <stdio.h>
#include <cmath>

#define col 200

float exp_next(float x, float prev, int n) {

	return (prev * x) / (float(n));
}
float ln_next(float x, float prev, int n) {
	float res = -((prev * float(n - 1) * x) / float(n));
	//printf("%lf ;%lf;%lf;%d \n", res,prev,x,n);
	return res;
}

float sin_next(float x, float prev, int n) {
	if (n % 2 == 1) {
		float res = (0 - 1) * (prev * x * x) / (float(n * (n - 1)));
		return res;
	}
	else {
		return 0;
	}
}
float cos_next(float x, float prev, int n) {
	if (n % 2 == 1) {
		return 0;
	}
	else {
		float res = (0 - 1) * (prev * x * x) / (float(n * (n - 1)));
		return res;
	}

}

void fillarray(float* array, int n, int func, float x) {
	for (int i = 0; i < n; i++) {
		array[i] = float(0);
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

void printarray(float* array, int n) {
	for (int i = 0; i < n; i++) {
		printf("%.20f \n", array[i]);
	}
}

float sumarray(float* array, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += array[i];
	}
	return sum;
}

float rev_sumarray(float* array, int n) {
	float sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		sum += array[i];
	}
	return sum;
}
float pair_sumarray(float* array, int n) {
	float sum = 0;
	for (int i = 0; i < n - 1; i += 2) {
		sum += array[i] + array[i + 1];
	}
	return sum;
}

void error_check(float res, float(*original)(float x), float x) {
	printf("absolute error - %.20lf %%\n", fabs(original(x) - res));
	printf("relative error - %.20lf %% \n", fabs(original(x) - res) / original(x) * 100);
}



int main() {
	float x;
	printf("enter x\n");
	scanf_s("%f", &x);
	int n;
	printf("enter steps amount\n");
	scanf_s("%d", &n);

	float a[col];
	float sum;
	int ff;
	printf("choose function\n1 - exp\n2 - ln\n3 - sin\n4 - cos\n");
	scanf_s("%d", &ff);
	printf("\n");
	if (ff == 1) {
		fillarray(a, n, 1, x);
		sum = sumarray(a, n);
		printf("straight sum: \n");
		printf("exp = %.10lf \n", sum);
		error_check(sum, exp, x);
		printf("\n");
		sum = rev_sumarray(a, n);
		printf("reverse sum: \n");
		printf("exp = %.10lf \n", sum);
		error_check(sum, exp, x);
		printf("\n");
		sum = pair_sumarray(a, n);
		printf("pair sum: \n");
		printf("exp = %.10lf \n", sum);

		error_check(sum, exp, x);
	}
	if (ff == 2) {
		if ((abs(x)) < 1.0) {
			fillarray(a, n, 2, x);
			sum = sumarray(a, n);
			printf("straight sum: \n");
			printf("ln = %.10lf \n", sum);
			error_check(sum, log, x + 1);
			printf("\n");
			sum = rev_sumarray(a, n);
			printf("reverse sum: \n");
			printf("ln = %.10lf \n", sum);
			error_check(sum, log, x + 1);
			printf("\n");
			sum = pair_sumarray(a, n);
			printf("pair sum: \n");
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
		printf("straight sum: \n");
		printf("sin = %.10lf \n", sum);
		error_check(sum, sin, x);
		printf("\n");
		sum = rev_sumarray(a, n);
		printf("reverse sum: \n");
		printf("sin = %.10lf \n", sum);
		error_check(sum, sin, x);
		printf("\n");
		sum = pair_sumarray(a, n);
		printf("pair sum: \n");
		printf("sin = %.10lf \n", sum);
		error_check(sum, sin, x);
	}
	if (ff == 4) {
		fillarray(a, n, 4, x);
		sum = sumarray(a, n);
		printf("straight sum: \n");
		printf("cos = %.10lf \n", sum);
		error_check(sum, cos, x);
		printf("\n");
		sum = rev_sumarray(a, n);
		printf("reverse sum: \n");
		printf("cos = %.10lf \n", sum);
		error_check(sum, cos, x);
		printf("\n");
		sum = pair_sumarray(a, n);
		printf("pair sum: \n");
		printf("cos = %.10lf \n", sum);
		error_check(sum, cos, x);
	}
	return 0;
}