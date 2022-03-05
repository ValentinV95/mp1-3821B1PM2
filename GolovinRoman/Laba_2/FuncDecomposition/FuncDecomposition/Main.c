#include <stdio.h>
#include <math.h>
#include "MySin.h"

//Первый у синуса - x
//Первый у косинуса - 1
//Первый у экспоненты - 1
//Первый у логорифма - x

double revSum(double (*nextEl)(double x, double pref, int i),double first, double x)
{
	return  first + recSum(nextEl, x, first, 2);
}

static double recSum(double (*nextEl)(double x, double pref, int i), double x, double pref, int i)
{
	double next = nextEl(x, pref, i);
	if (fabs(next) > 0.0000000000000001)
		return next + recSum(nextEl, x, next, i + 1);
	else
		return  next;
}

//Сумма влоб
double straightSum(double (*nextEl)(double x, double pref, int i),double first, double x)
{
	double sum = 0, next;
	int i = 1;

	next = first;
	while (fabs(next) > 0.0000000000000001)
	{
		sum += next;
		i++;
		next = nextEl(x, next, i);
	}

	return sum;
}

//Сумма соседних элементов
double nearbySum(double (*nextEl)(double x, double pref, int i), double first, double x)
{
	double sum = 0, next;
	int i = 1;

	next = first;
	while (fabs(next) > 0.0000000000000001)
	{
		sum += next + nextEl(x, next, i+1);
		i+=2;
		next = nextEl(x,nextEl(x, next, i-1), i);
	}

	return sum;
}

double nextSin(double x, double pref, int i)
{
	return ((-1) * pref * x * x) / (double)(i * (i - 1));
}

double nextCos(double x, double pref, int i)
{
	return ((-1) * pref * x * x) / (double)(i * (i - 1));
}

double nextExp(double x, double pref, int i)
{
	return pref * x / (double)i;
}

double nextLn(double x, double pref, int i)
{
	return (-1)*pref * x / i;
}

double absoluteDeviation(double value,double standard)
{
	return fabs(value - standard);
}

double relativeDeviation(double value, double standard)
{
	return (fabs(value - standard) / fabs(standard))*100;
}

void main()
{
	
}