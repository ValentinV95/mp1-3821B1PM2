#include <stdio.h>
#include <math.h>
#include "Functions.h"


double relative_dev(double val, double right_val)
{
	return ((right_val - val) / right_val) * 100;
}
double absolute_dev(double val, double right_val)
{
	return right_val - val;
}
int main()
{
	//exp
	//double val;
	/*for (double val = 0.001; val < 2; val += 0.001)
	{
		double originExp = exp(val);
		double recum = sum('E', val, val);
		printf("%lf %lf Absolute deviation: %lf Relative deviation: %lf \n", originExp, recum,absolute_dev(recum,originExp),relative_dev(recum,originExp));
	}*/
	char func_type;
	printf("Enter the type of function (S - sin(x); C - cos(x); E - exp(x); L- ln(1+x) : \n");
	scanf_s("%c", &func_type);
	switch (func_type)
	{
	case 'S':
		for (double val = 0.001; val < 3; val += 0.001)
		{
			double originExp = sin(val);
			double recsum = sum('S', val, val);
			double inversum = invers_sum('S', val, val);
			double cwise = pairwise_sum('S', val, val);
			//printf("%lf %lf %lf %lf %lf %lf \n", absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
			printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
		}
		break;
	case 'C':
		for (double val = 0.001; val < 1.5; val += 0.001)
		{
			double originExp = cos(val);
			double recsum = sum('C', val, val);
			//printf("%lf %lf \n", absolute_dev(recum, originExp), relative_dev(recum, originExp));
			double inversum = invers_sum('C', val, val);
			double cwise = pairwise_sum('C', val, val);
			printf("%lf %lf %lf %lf %lf %lf %lf \n", 
				val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp),
				absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp),
				relative_dev(cwise, originExp));
		}
		break;
	case 'E':
		for (double val = 0.001; val < 0.99; val += 0.001)
		{
			double originExp = exp(val);
			double recsum = sum('E', val, val);
			double inversum = invers_sum('E', val, val);
			double cwise = pairwise_sum('E', val, val);
			printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));

		}
		break;
	case 'L':
		for (double val = 0.001; val < 0.99; val += 0.001)
		{
			double originExp = log(val+1);
			double recsum = sum('L', val, val);
			double inversum = invers_sum('L', val, val);
			double cwise = pairwise_sum('L', val, val);
			printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
		}
		break;
	}
}
