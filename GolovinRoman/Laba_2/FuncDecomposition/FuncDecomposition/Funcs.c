#include "Funcs.h"

//Первый у синуса - x
//Первый у косинуса - 1
//Первый у экспоненты - 1
//Первый у логорифма - x

double revSum(double (*nextEl)(double x, double pref, int i), double first, double x)
{
	return  first + recSum(nextEl, x, first, 1);
}

static double recSum(double (*nextEl)(double x, double pref, int i), double x, double pref, int i)
{
	double next = nextEl(x, pref, i);
	if (i < 200)
		return next + recSum(nextEl, x, next, i + 1);
	else
		return  next;
}

//Сумма влоб
double straightSum(double (*nextEl)(double x, double pref, int i), double first, double x)
{
	double  next = first,sum =next;
	int i = 1;

	while (i < 100)
	{
		next = nextEl(x, next, i);
		sum += next;
		i++;
	}

	return sum;
}

//Сумма соседних элементов
double nearbySum(double (*nextEl)(double x, double pref, int i), double first, double x)
{
	double sum = 0.0, next = first,a;
	int i = 1;

	next = nextEl(x,first, i);
	sum += (first + next);
	while (i < 100)
	{
		next = nextEl(x, next, ++i);
		a = next;
		next = nextEl(x, next, ++i);
		a += next;
		sum += a;
	}

	return sum;
}

double nextSin(double x, double pref, int i)
{
	return ((-1) * pref * x * x) / (double)(2*i * (2*i + 1.0));
}

double nextCos(double x, double pref, int i)
{
	return ((-1) * pref * x * x) / (double)(2*i * (2*i-1));
}

double nextExp(double x, double pref, int i)
{
	return pref * x / (double)i;
}

double nextLn(double x, double pref, int i)
{
	return (-1) * pref*i / (double)(i+1.0);
}
