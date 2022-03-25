#pragma once
#include"Functions.h"

float next_element(char func_type, float x, float prev_element, int i)
{
	switch (func_type)
	{
	case 'E':
		return ((prev_element)*x) / (float)i;
		break;
	case 'S':
		return ((-1)*(prev_element)*x*x) / (float)((2 * i) * (2 * i + 1));
		break;
	case 'C':
		return ((-1) * (prev_element)*x * x) / (float)((2 * i) * (2 * i - 1));
		break;
	case 'L':
		return ((-1) * prev_element * x) / (float)i;
		break;
	default:
		return 0;
	}
}
float sum(char func_type, float x, float first_element)
{
	return first_element + recursion_sum(func_type, first_element, x, 1);
}

static float recursion_sum(char func_type,float prev_elem, float x, int i)
{
	float nextel = next_element(func_type, x, prev_elem, i);
	if (fabs(nextel) > 0.00001)
	{
		return nextel + recursion_sum(func_type, nextel, x, i + 1);
	}
	else
	{
		return nextel;
	}
}

float invers_sum(char func_type, float first_elem, float x)
{
	int i = 1;
	float last_elem;
	float next_elem = first_elem;
	last_elem = next_elem;
	while (fabs(last_elem) > 0.00001)
	{
		last_elem = next_element(func_type, x, last_elem, i);
		i++;
	}
	float summ = last_elem;
	int n = i;
	while (n >0)
	{
		float nextelem = first_elem;
		if (n != 1)
		{
			for (int j = 1; j < n; j++)
			{
				nextelem = next_element(func_type, x, nextelem, j);
			}
			summ += nextelem;
		}
		if (n == 1)
		{
			summ += first_elem;
		}

		n--;
	}
	return summ;
}

float pairwise_sum(char func_type, float first_elem, float x)
{
	int i = 1;
	float last_elem;
	float next_elem = first_elem;
	last_elem = next_elem;
	while (fabs(last_elem) > 0.00001)
	{
		last_elem = next_element(func_type, x, last_elem, i);
		i++;
	}
	float summ = last_elem;
	int n = i;
	int z = 1;
	while (n > n/2)
	{
		float nextelem = first_elem;
		for (int j = 1; j < n; j++)
		{
			nextelem = next_element(func_type, x, nextelem, j);
		}
		summ += nextelem;

		n--;
	}
	while (z < n / 2-1)
	{
		float nextelem = first_elem;
		if (z != 1)
		{
			for (int j = 1; j < z; j++)
			{
				nextelem = next_element(func_type, x, nextelem, j);
			}
			summ += nextelem;
		}
		if (z == 1)
		{
			summ += first_elem;
		}
	}
	return summ;
}
