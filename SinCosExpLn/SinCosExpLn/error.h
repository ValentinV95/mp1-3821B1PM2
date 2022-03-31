#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "reverse.h"
#include "forward.h"
#include "in_pairs.h"

float error_forward_sin(double x)
{
	return fabs(forward_sin(x) - sin(x));
}
float error_forward_cos(double x)
{
	return fabs(forward_cos(x) - cos(x));
}
float error_forward_exp(double x)
{
	return fabs(forward_exp(x) - exp(x));
}
float error_forward_ln(double x)
{
	return fabs(forward_ln(x) - log(1+x));
}

float error_reverse_sin(double x)
{
	return fabs(reverse_sin(x) - sin(x));
}
float error_reverse_cos(double x)
{
	return fabs(reverse_cos(x) - cos(x));
}
float error_reverse_exp(double x)
{
	return fabs(reverse_exp(x) - exp(x));
}
float error_reverse_ln(double x)
{
	return fabs(reverse_ln(x) - log(1 + x));
}

float error_in_pairs_sin(double x)
{
	return fabs(in_pairs_sin(x) - sin(x));
}
float error_in_pairs_cos(double x)
{
	return fabs(in_pairs_cos(x) - cos(x));
}
float error_in_pairs_exp(double x)
{
	return fabs(in_pairs_exp(x) - exp(x));
}
float error_in_pairs_ln(double x)
{
	return fabs(in_pairs_ln(x) - log(1 + x));
}
