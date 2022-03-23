#include <stdio.h>
#include <math.h>
#include "Funcs.h"

void sinDeviationTest()
{
	printf("sinDeviationTest\n");
	double i = 0.00001;
	double revsum,straightsum,nearbysum,origSin;
	for (;i<6.3;i+= 0.01)
	{
		origSin = sin(i);
		revsum = revSum(*nextSin,i,i);
		straightsum = straightSum(*nextSin, i, i);
		nearbysum = nearbySum(*nextSin, i, i);
		printf("%lf;%.16lf;%.16lf;%.16lf;\n", i, relativeDeviation(revsum, origSin), relativeDeviation(straightsum, origSin), relativeDeviation(nearbysum, origSin));
	}
}

void cosDeviationTest()
{
	printf("cosDeviationTest\n");
	double i = 0.00001;
	double revsum, straightsum, nearbysum, origCos;
	for (; i < 6.3; i += 0.01)
	{
		origCos = cos(i);
		revsum = revSum(nextCos,1, i);
		straightsum = straightSum(nextCos,1, i);
		nearbysum = nearbySum(nextCos,1, i);
		printf("%lf;%.16lf;%.16lf;%.16lf;\n", i, relativeDeviation(revsum, origCos), relativeDeviation(straightsum, origCos), relativeDeviation(nearbysum, origCos));
	}
}

void expDeviationTest()
{
	printf("expDeviationTest\n");
	double i = -3;
	double revsum, straightsum, origExp;
	for (; i < 5; i += 0.5)
	{
		origExp = exp(i);
		revsum = revSum(nextExp,1, i);
		straightsum = straightSum(nextExp,1, i);
		printf("%lf;%.16lf;%.16lf;\n", i, relativeDeviation(revsum, origExp), relativeDeviation(straightsum, origExp));
	}
}

void lnDeviationTest()
{
	printf("lnDeviationTest\n");
	double i = 0;
	double revsum, straightsum, origLn;

	for (; i < 1; i += 0.05)
	{
		origLn = log(i+1);
		revsum = revSum(nextLn,i, i);
		straightsum = straightSum(nextLn,i, i);
		printf("%lf;%.16lf;%.16lf;\n", i,origLn, revsum);
		//printf("%lf;%.16lf;%.16lf;\n", i, relativeDeviation(revsum, origExp), relativeDeviation(straightsum, origExp));
	}
}

double absoluteDeviation(double value, double standard)
{
	return fabs(value - standard);
}

double relativeDeviation(double value, double standard)
{
	return fabs((value - standard) / standard) * 100;
}

void main()
{
	lnDeviationTest();
}