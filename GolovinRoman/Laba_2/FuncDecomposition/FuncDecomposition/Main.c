#include <stdio.h>
#include <math.h>
#include "Funcs.h"

void sinDeviationTest()
{
	double i = 0.00001;
	double revsum,straightsum,nearbysum,origSin;
	for (;i<3;i+= 0.001)
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

}

void expDeviationTest()
{

}

void lnDeviationTest()
{

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
	sinDeviationTest();
}