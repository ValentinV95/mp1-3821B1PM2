#include <stdio.h>
#include <math.h>
#include "Funcs.h"


void sinDeviationTest(float start,float stop,float step)
{
	printf("sinDeviationTest\n");
	float x = start;
	float revsum, straightsum, nearbysum;
	double origSin;

	printf("\nAbs. Div.\n");

	for (;x<=stop;x+= step)
	{
		origSin = sin(x);
		revsum = revSum(*nextSin,x,x);
		straightsum = straightSum(*nextSin, x, x);
		nearbysum = nearbySum(*nextSin, x, x);
		printf("%lf;%.8lf;%.8lf;%.8f;\n", x, absoluteDeviation(revsum, origSin), absoluteDeviation(straightsum, origSin), absoluteDeviation(nearbysum, origSin));
	}

	printf("\nRel. Div.\n");

	for (x=start;x <= stop; x += step)
	{
		origSin = sin(x);
		revsum = revSum(*nextSin, x, x);
		straightsum = straightSum(*nextSin, x, x);
		nearbysum = nearbySum(*nextSin, x, x);
		printf("%lf;%.8lf;%.8lf;%.8f;\n", x, relativeDeviation(revsum, origSin), relativeDeviation(straightsum, origSin),relativeDeviation(nearbysum, origSin));
	}
}

void cosDeviationTest(float start, float stop, float step)
{
	printf("cosDeviationTest\n");
	float x = start;
	float revsum, straightsum, nearbysum;
	double origCos;

	printf("\nAbs. Div.\n");

	for (; x <= stop; x += step)
	{
		origCos = cos(x);
		revsum = revSum(*nextCos,1.0f, x);
		straightsum = straightSum(*nextCos,1.0f, x);
		nearbysum = nearbySum(*nextCos,1.0f, x);
		printf("%lf;%.8lf;%.8lf;%.8f;\n", x, absoluteDeviation(revsum, origCos), absoluteDeviation(straightsum, origCos), absoluteDeviation(nearbysum, origCos));
	}

	printf("\nRel. Div.\n");

	for (x = start; x <= stop; x += step)
	{
		origCos = cos(x);
		revsum = revSum(nextCos, 1.0f, x);
		straightsum = straightSum(nextCos, 1.0f, x);
		nearbysum = nearbySum(nextCos, 1.0f, x);
		printf("%lf;%.8lf;%.8lf;%.8f;\n", x, relativeDeviation(revsum, origCos), relativeDeviation(straightsum, origCos), relativeDeviation(nearbysum, origCos));
	}
}

void expDeviationTest(float start, float stop, float step)
{
	printf("expDeviationTest\n");
	float x = start;
	float revsum, straightsum;
	double origExp;

	printf("\nAbs. Div.\n");

	for (; x <= stop; x += step)
	{
		origExp = exp(x);
		revsum = revSum(*nextExp, 1.0f, x);
		straightsum = straightSum(*nextExp, 1.0f, x);
		printf("%lf;%.8lf;%.8lf;\n", x, absoluteDeviation(revsum, origExp), absoluteDeviation(straightsum, origExp));
	}

	printf("\nRel. Div.\n");

	for (x = start; x <= stop; x += step)
	{
		origExp = exp(x);
		revsum = revSum(*nextExp,1.0f, x);
		straightsum = straightSum(*nextExp,1.0f, x);
		printf("%lf;%.8lf;%.8lf;\n", x, relativeDeviation(revsum, origExp), relativeDeviation(straightsum, origExp));
	}
}

void lnDeviationTest(float start, float stop, float step)
{
	printf("lnDeviationTest\n");
	float x = start;
	float revsum, straightsum;
	double origLn;

	printf("\nAbs. Div.\n");

	for (; x <= stop; x += step)
	{
		origLn = log(x+1.0f);
		revsum = revSum(nextLn, x, x);
		straightsum = straightSum(nextLn, x, x);
		printf("%lf;%.16lf;%.16lf;\n", x, absoluteDeviation(revsum, origLn), absoluteDeviation(straightsum, origLn));
	}

	printf("\nRel. Div.\n");

	for (x = start; x <= stop; x += step)
	{
		origLn = log(x+1.0f);
		revsum = revSum(nextLn,x,x);
		straightsum = straightSum(nextLn,x, x);
		printf("%lf;%.16lf;%.16lf;\n", x, relativeDeviation(revsum,origLn), relativeDeviation(straightsum, origLn));
	}
}

float absoluteDeviation(float value, double standard)
{
	return fabs(value - (float)standard);
}

float relativeDeviation(float value, double standard)
{
	return fabs((value - (float)standard) / (float)standard) * 100.0f;
}

void main()
{
	int a=0;
	printf("1 for sin\n2 for cos\n3 for exp\n4 for ln\n");
	scanf_s("%d",&a);

	switch (a)
	{
	case(1):
	{
		sinDeviationTest(0.0f,6.30f,0.05f);
		break;
	}
	case(2):
	{
		cosDeviationTest(0.0f,6.0f,0.05f);
		break;
	}
	case(3):
	{
		expDeviationTest(-2.0f,20.0f,0.5f);
		break;
	}
	case(4):
	{
		lnDeviationTest(-0.95f,0.96f, 0.03f);
		break;
	}
	}
}