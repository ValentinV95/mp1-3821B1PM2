#include "Funcs.h"

//Первый у синуса - x
//Первый у косинуса - 1
//Первый у экспоненты - 1
//Первый у логорифма - x

float revSum(float (*nextEl)(float x, float pref, int i), float first, float x)
{
	return  first + recSum(nextEl, x, first, 1);
}

static float recSum(float (*nextEl)(float x, float pref, int i), float x, float pref, int i)
{
	float next = nextEl(x, pref, i);
	if (fabs(next) > 0.00000001)
		return next + recSum(nextEl, x, next, i + 1);
	else
		return  next;
}

//Сумма влоб
float straightSum(float (*nextEl)(float x, float pref, int i), float first, float x)
{
	float next = first,sum =next;
	int i = 1;

	while (fabs(next) > 0.00000001)
	{
		next = nextEl(x,next,i++);
		sum += next;
	}

	return sum;
}

//Сумма соседних элементов
float nearbySum(float (*nextEl)(float x, float pref, int i), float first, float x)
{
	float sum = 0.0f, next = first,a;
	int i = 1;

	next = nextEl(x,first, i);
	sum += (first + next);
	while (fabs(next) > 0.00000001)
	{
		next = nextEl(x, next, ++i);
		a = next;
		next = nextEl(x, next, ++i);
		sum += (a+next);
	}

	return sum;
}

float nextSin(float x, float pref, int i)
{
	return ((-1) * pref * x * x) / (float)(2*i * (2*i + 1.0f));
}

float nextCos(float x, float pref, int i)
{
	return ((-1) * pref * x * x) / (float)(2*i * (2*i-1.0f));
}

float nextExp(float x, float pref, int i)
{
	return pref * (x / (float)i);
}

float nextLn(float x, float pref, int i)
{
	return (-1)* x* pref*((float)i / (float)(i+1.0f));
}
