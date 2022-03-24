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


 //--------------------------------------------------------------------------------------------


float next_element_sin(float prevElement, float x, int i)
{
	float nes = (prevElement * x * x) / ((2.0 * i) * (2.0 * i + 1.0));
	if (nes > FLT_EPSILON)
		return nes;
	else return 0.0;
}

float next_element_lnx(float prevElement, float x, int i)
{
	return i * prevElement * x / (i + 1.0);
}

float next_element_cos(float prevElement, float x, int i)
{
	return prevElement * x * x / (2.0 * i - 1) / (2.0 * i);
}

float next_element_exp(float prevElement, float x, int i)
{
	return prevElement * x / (i + 0.0);
}


//--------------------------------------------------------------------------------------------


float recursive_sin(float x, float xconst, int i)
{
	if (x > FLT_EPSILON)
	{
		if (i % 2 != 0)
			return -x + recursive_sin(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xconst, i + 1);
		else
			return x + recursive_sin(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xconst, i + 1);
	}
	else return x;
}

float recursive_cos(float x, float xconst, int i)
{
	if (x > FLT_EPSILON)
	{
		if (i % 2 != 0)
			return -x + recursive_cos(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xconst, i + 1);
		else
			return x + recursive_cos(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xconst, i + 1);
	}
	else return x;
}

float recursive_exp(float x, float xconst, int i)
{
	if (x > FLT_EPSILON && i < 4000)                                        // Если будет больше 4161, то ОШИБКА!
		return x + recursive_exp(x * xconst / (i + 1.0), xconst, i + 1);
	else return x;
}

float recursive_ln(float x, float xconst, int i)
{
	if ((x <= 1 && x > -1) && (i < 4000 && xconst != 1))
	{
		if (x > FLT_EPSILON)
		{
			if (i % 2 == 0)
				return -x + recursive_ln(x * xconst * i / (i + 1.0), xconst, i + 1);
			else
				return x + recursive_ln(x * xconst * i / (i + 1.0), xconst, i + 1);
		}
		else return x;
	}
	else
		return 0.0;      // показывает ошибку!
}


//--------------------------------------------------------------------------------------------