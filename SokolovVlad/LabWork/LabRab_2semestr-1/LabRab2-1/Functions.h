#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  
#include <limits.h>
#include <float.h>
#include <math.h>

#ifdef MYDLL_EXPORTS                            //подстраховка
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

/* --------------------------------------------------------------------------------------------

		  ФОРМУЛЫ НАХОЖДЕНИЯ синуса, косинуса, экспоненты, натурального логарифма(1+x)

 sinx = x - x^3/3! + x^5/5! - ... + (-1)^m * x^(2m+1)/(2m+1)!

 cosx = 1 - x^2/2! + x^4/4! - ... + (-1)^n * x^2n/(2n)!

 expx = 1 + x + x^2/2! + ... + x^k/k!                  k - любая

 ln(1+x) = x - x^2/2 + x^3/3 - ... + (-1)^(n-1) * x^n/n

  --------------------------------------------------------------------------------------------
  */


float x_period(float x)
{

	float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078;
	if (x > 0)
	{
		while (x - 2 * PI > 0)
		{
			x -= 2 * PI;
		}
	}
	else if (x < 0)
	{
		while (x < 0)
		{
			x += 2 * PI;
		}
	}

	return x;
}



 //--------------------------------------------------------------------------------------------

//					<[ Прямое суммирование ]>




float next_element_sin(float prevElement, float x, int i)
{
	float nes = (prevElement * x * x) / ((2.0 * i) * (2.0 * i + 1.0));
	if (nes > FLT_EPSILON)
		return nes;
	else return 0.0;
}

float next_element_cos(float prevElement, float x, int i)
{
	return prevElement * x * x / (2.0 * i - 1) / (2.0 * i);
}

float next_element_exp(float prevElement, float x, int i)
{
	return prevElement * x / (i + 0.0);
}

float next_element_lnx(float prevElement, float x, int i)
{
	return i * prevElement * x / (i + 1.0);
}




//--------------------------------------------------------------------------------------------



float direct_summ(float* mas)
{
	float summ = 0;
	int i;
	for (i = 0; i < 100; i++)
	{
		summ += mas[i];
	}
	return summ;
}



float reverse_summ(float* mas)
{
	float summ = 0;
	int i;
	for (i = 99; i >=0; i--)
	{
		summ += mas[i];
	}
	return summ;
}



float pair_summ(float* mas)
{
	float summ = 0;
	int i;
	for (i = 99; i > 0; i-=2)
	{
		summ = summ + (mas[i]+mas[i-1]);
	}
	return summ;
}