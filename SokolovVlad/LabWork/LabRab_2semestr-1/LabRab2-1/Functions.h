#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  
#include <limits.h>
#include <float.h>
#include <math.h>

#ifdef MYDLL_EXPORTS
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


double next_element_sin(double predEl, double x, int i)
{
	return predEl * x * x / ((2.0 * i) * (2.0 * i + 1.0));
}

double next_element_lnx(double predEl, double x, int i)
{
	return i * predEl * x / (i + 1.0);
}

double next_element_cos(double predEl, double x, int i)
{
	return predEl * x * x / (2.0 * i - 1) / (2.0 * i);
}

double next_element_exp(double predEl, double x, int i)
{
	return predEl * x / (i + 0.0);
}


//--------------------------------------------------------------------------------------------


double recursive_sin(double x, double xconst, int i)
{
	if (x > DBL_EPSILON)
	{
		if (i % 2 != 0)
			return -x + recursive_sin(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xconst, i + 1);
		else
			return x + recursive_sin(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xconst, i + 1);
	}
	else return x;
}

double recursive_cos(double x, double xconst, int i)
{
	if (x > DBL_EPSILON)
	{
		if (i % 2 != 0)
			return -x + recursive_cos(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xconst, i + 1);
		else
			return x + recursive_cos(x * xconst * xconst / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xconst, i + 1);
	}
	else return x;
}

double recursive_exp(double x, double xconst, int i)
{
	if (x > DBL_EPSILON && i < 4100)                                        // Если будет больше 4161, то ОШИБКА!
		return x + recursive_exp(x * xconst / (i + 1.0), xconst, i + 1);
	else return x;
}

double recursive_ln(double x, double xconst, int i)
{
	if (x <= 1 && x > -1)
	{
		if (x > DBL_EPSILON)
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