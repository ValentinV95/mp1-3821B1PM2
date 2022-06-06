#include <stdio.h>
#include <math.h>
#include "Functions.h"


float relative_dev(float val, float right_val)
{
	return ((right_val - val) / right_val) * 100;
}
float absolute_dev(float val, float right_val)
{
	return right_val - val;
}
int main()
{
	//exp
	//float val;
	/*for (float val = 0.001; val < 2; val += 0.001)
	{
		float originExp = exp(val);
		float recum = sum('E', val, val);
		printf("%lf %lf Absolute deviation: %lf Relative deviation: %lf \n", originExp, recum,absolute_dev(recum,originExp),relative_dev(recum,originExp));
	}*/
	char func_type;
	printf("Enter the type of function (S - sin(x); C - cos(x); E - exp(x); L- ln(1+x) : \n");
	scanf_s("%c", &func_type);
	switch (func_type)
	{
	case 'S':
		for (float val = 0.001; val < 3; val += 0.001)
		{
			float originExp = sin(val);
			float recsum = forward_sum('S', val, val);
			float inversum = invers_sum('S', val, val);
			float cwise = pairwise_sum('S', val, val);
			//printf("%lf %lf %lf %lf %lf %lf \n", absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
			//printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
			printf("%lf %lf %lf %lf %lf %lf %lf \n",
				val, fabs(absolute_dev(recsum, originExp)), fabs(relative_dev(recsum, originExp)),
				fabs(absolute_dev(inversum, originExp)), fabs(relative_dev(inversum, originExp)), fabs(absolute_dev(cwise, originExp)),
				fabs(relative_dev(cwise, originExp)));
		}
		break;
	case 'C':
		for (float val = 0.001; val < 3; val += 0.001)
		{
			float originExp = cos(val);
			float recsum = forward_sum('C', val, val);
			//printf("%lf %lf \n", absolute_dev(recum, originExp), relative_dev(recum, originExp));
			float inversum = invers_sum('C', val, val);
			float cwise = pairwise_sum('C', val, val);
			printf("%lf %lf %lf %lf %lf %lf %lf \n", 
				val, fabs(absolute_dev(recsum, originExp)), fabs(relative_dev(recsum, originExp)),
				fabs(absolute_dev(inversum, originExp)), fabs(relative_dev(inversum, originExp)), fabs(absolute_dev(cwise, originExp)),
				fabs(relative_dev(cwise, originExp)));
		}
		break;
	case 'E':
		for (float val = 0.001; val < 0.99; val += 0.001)
		{
			float originExp = exp(val);
			float recsum = forward_sum('E', val, val);
			float inversum = invers_sum('E', val, val);
			float cwise = pairwise_sum('E', val, val);
			//printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
			printf("%lf %lf %lf %lf %lf %lf %lf \n",
				val, fabs(absolute_dev(recsum, originExp)), fabs(relative_dev(recsum, originExp)),
				fabs(absolute_dev(inversum, originExp)), fabs(relative_dev(inversum, originExp)), fabs(absolute_dev(cwise, originExp)),
				fabs(relative_dev(cwise, originExp)));
		}
		break;
	case 'L':
		for (float val = 0.001; val < 0.99; val += 0.001)
		{
			float originExp = log(val+1);
			float recsum = forward_sum('L', val, val);
			float inversum = invers_sum('L', val, val);
			float cwise = pairwise_sum('L', val, val);
			//printf("%lf %lf %lf %lf %lf %lf %lf \n", val, absolute_dev(recsum, originExp), relative_dev(recsum, originExp), absolute_dev(inversum, originExp), relative_dev(inversum, originExp), absolute_dev(cwise, originExp), relative_dev(cwise, originExp));
			printf("%lf %lf %lf %lf %lf %lf %lf \n",
				val,fabs( absolute_dev(recsum, originExp)), fabs(relative_dev(recsum, originExp)),
				fabs(absolute_dev(inversum, originExp)), fabs(relative_dev(inversum, originExp)), fabs(absolute_dev(cwise, originExp)),
				fabs(relative_dev(cwise, originExp)));
		}
		break;
	}
}
