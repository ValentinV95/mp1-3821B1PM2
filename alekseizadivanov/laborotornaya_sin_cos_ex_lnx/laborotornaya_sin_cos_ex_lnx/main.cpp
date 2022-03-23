#include <stdio.h>
#include <iostream>
#include <math.h>
#define N 100 //для логарифма число членов
double fact[14] = {1, 2, 6, 24, 120 , 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200};
double p2 = 6.283185307179586;
void ex(double b);
void cosx(double b);
void sinx(double b);
void ln1px(double b);
void prov(int i, double b, double d);
void main() {
	setlocale(LC_ALL, "Russian");
	double c;
	int a;
	printf("введите число\n");
	scanf_s("%lf", &c);	
	printf("ввдите номер  функции\n 1 - sinx\n 2 - cosx\n 3 - e^x\n 4 - ln(1+x)\n ");
	scanf_s("%i", &a);
	if (a == 1) {
		while(c >= p2) {
			c -= p2;
		}
		sinx(c);
	}
	else if (a == 2) {
		while (c >= p2) {
			c -= p2;
		}
		cosx(c);
	}
	else if (a == 3) {
		 ex(c);
	}
	else {
		if (c > 1 || c < -1) {
			printf("неверные данные");
			
		}
		else {
			ln1px(c);
		}
	}

}
void ex(double b) {
	double res = 1.0,n = 1, res2 = 1.0,b2,arr[14];
	int i,k;
	for (i = 0; i <= 13; i++) {
		arr[i] = 0;
	}
	b2 = b;
	printf("прямое суммирование\n");
	for (i = 0; i < 14; i++) {
		arr[i] = b2 / fact[i];
	}
	for (i = 0; i < 14; i++) {
		res += arr[i];
	}
	printf("%lf\n", res);
	printf("обратное суммирование\n");
	for (i = 13; i >= 0; i--) {
		res2 += arr[i];
	}
	printf("%lf", res2);
}
void sinx(double b) {
	int i;
	double res = 0,res2 = 0, k = 1,arr[14],b2 = 0;
	b2 = b;
	for (i = 0; i <= 13; i++) {
		arr[i] = 0;
	}
	for (i = 0;i <= 12 ;i+=2) {
		arr[i] = (b2 * k) / fact[i];
		b2 = b2 * b * b;
		k = -k;		
	}
	for (i = 0; i <=13; i++) {
		res += arr[i];
	}
	printf("прямое суммирование\n");
	printf("%lf\n", res);
	prov(1,res , b);
	for (i = 13; i >= 0; i--) {
		res2 += arr[i];
	}
	printf("обратное суммирование\n");
	printf("%lf", res2);
	prov(1, res2, b);

}
void cosx(double b) {
	double res = 1, res2 = 1, k = -1, b2, b3,arr[14];
	int i;
	b2 = b;
	for (i = 0; i <= 13; i++) {
		arr[i] = 0;
	}
	for (i = 1; i <= 13; i += 2) {
		arr[i] = (b2 * k) / fact[i];
		k = -k;
		b2 = b2 * b * b;
	}
	for (i = 0; i <= 13; i++) {
		res += arr[i];
	}
	printf("прямое суммирование\n");
	printf("%lf\n", res);
	prov(2, res, b);
	for (i = 13; i >= 1; i -= 1) {
		res2 += arr[i];
	}
	printf("обратное суммирование\n");
	printf("%lf", res2);
	prov(2, res2, b);
}
void ln1px(double b) {
	int i;
	double arr[N], res = 0,a = 1,k = 1,res2 = 0;
	for (i = 0;i < N ; i++) {
		arr[i] = (b * k) / a;
		b *= b;
		a += 1;
		k = -k;
	}

	for (i = 0; i < N; i++) {
		res += arr[i];
	}
	printf("прямое суммирование\n");
	printf("%lf\n", res);
	for (i = 99; i >= 0; i--) {
		res2 += arr[i];
	}
	printf("обратное суммирование\n");
	printf("%lf", res2);
}
void prov(int i, double b, double d) {
	double c,err;
	if(i == 1) {
		c = sin(d);
		if (b > c) {
			err = b - c;
		}
		else {
			err = c - b;
		}
		printf("значение синуса = %d\n ", &c);
		printf("ошибка =  %d \n", &err);
	}
	else if (i == 2) {
		c = cos(d);
		if (b > c) {
			err = b - c;
		}
		else {
			err = c - b;
		}
		printf("значение косинуса = %d\n ", &c);
		printf("ошибка =  %d\n", &err);
	}
	else if (i == 3) {
		c = exp(d);
		if (b > c) {
			err = b - c;
		}
		else {
			err = c - b;
		}
		printf("значение экспоненты = %d\n ",&c);
		printf("ошибка =  %d \n",&err);
	}
	else {
		c = log(d);
		if (b > c) {
			err = b - c;
		}
		else {
			err = c - b;
		}
		printf("значение логарифма = %d\n ", &c);
		printf("ошибка =  %d\n ", &err);
	}
}