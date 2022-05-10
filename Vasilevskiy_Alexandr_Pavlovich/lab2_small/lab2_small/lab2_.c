#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 150

typedef float (*nexElemFunction)(float, int, float);
typedef float (*summFunction)(nexElemFunction, float, int, float);

float nextExpElem(float pred, int i, float x){
	return pred * x / i;
}

float nextCosElem(float pred, int i, float x){
	return -1.f * pred * x * x / (2.f * i * (2.f * i - 1.f));
}

float nextSinElem(float pred, int i, float x){
	return -1.f * pred * x * x / (2.f * i * (2.f * i + 1.f));
}

float nextLnElem(float pred, int i, float x) {
	return -1.f * pred * x * i / (i + 1.f);
}

float sumInOrder(nexElemFunction fn, float first, int len, float x){
	float SUM = 0.0f;

	for (int i = 1; i < len+1; i++)
	{	
		SUM += first;
		first = fn(first, i, x);
	}
	return SUM;
}

float sumFromTheEnd(nexElemFunction fn, float first, int len, float x) {
	float SUM = 0.0f;
	float* arr = malloc(sizeof(float) * len);
	arr[0] = first;
	for (int i = 1; i < len; i++)
	{
		first = fn(first, i, x);
		arr[i] = first;
	}

	for (int i = len - 1; i >= 0; i--)
	{
		SUM += arr[i];
	}
	free(arr);
	return SUM;
}

float sumInPairs(nexElemFunction fn, float first, int len, float x){
	float SUM = 0.0f, lastElem;
	for (int i = 1; i < len; i += 2)
	{
		lastElem = first;
		first = fn(first, i, x);
		SUM += (lastElem + first);
		first = fn(first, i+1, x);
	}
	if (len % 2 == 1)
	{
		SUM += first;
	}
	return SUM;
}

float absoluteError(float TrueValue, float MyValue) { return fabsf(TrueValue - MyValue); }
float relativeError(float TrueValue, float MyValue) 
{ 
	if (TrueValue != 0) return fabsf(TrueValue - MyValue) / fabsf(TrueValue);
	else if (TrueValue == MyValue) return 0;
	else return 999.f;
}

int main()
{
	FILE* file;
	float x, value = 0, true_value = 0, firstElem, step, num, errorSum[3] = {0.f, 0.f, 0.f}, errorOrder, errorEnd, errorPairs;
	int funcType = -1, summationMethod = -1, errorType = -1, write = -1;
	nexElemFunction fn = NULL;
	summFunction MyFunction = NULL;
	float (*ERROR)(float, float);

	do
	{
		printf("select the function:\n\t1 - sin(x)\n\t2 - cos(x)\n\t3 - exp^(x)\n\t4 - ln(1+x)\n");
		scanf_s("%d", &funcType);
	} while (funcType < 1 || funcType > 4);
	
	do
	{
		printf("write data to a file?\n0 - NO\t1 - YES\n");
		scanf_s("%d", &write);
	} while (write != 0 && write != 1);

	printf("x = ");
	scanf_s("%f", &x);

	if (funcType == 1) {
		fn = nextSinElem;
		firstElem = x;
		true_value = sinf(x);
	}
	if (funcType == 2) {
		fn = nextCosElem;
		firstElem = 1.f;
		true_value = cosf(x);
	}
	if (funcType == 3) {
		fn = nextExpElem;
		firstElem = 1.f;
		true_value = expf(x);
	}
	if (funcType == 4) {
		fn = nextLnElem;
		firstElem = x;
		true_value = logf(x+1.f);
	}

	if (write == 1)
	{
		printf("Step = ");
		scanf_s("%f", &step);
		printf("error:\n\t1 - absolute\n\t2 - relative\n");
		scanf_s("%d", &errorType);
		fopen_s(&file, "table.txt", "w+");
		fprintf_s(file, "    Num: \t in order:\t the end:\t in pairs:\n");
		
		if (errorType == 1) ERROR = absoluteError;
		else ERROR = relativeError;

		for (num = -fabsf(x); num < fabsf(x); num += fabsf(step))
		{
			if (funcType == 1) { true_value = sinf(num); firstElem = num; }
			if (funcType == 2) { true_value = cosf(num); firstElem = 1.f; }
			if (funcType == 3) { true_value = expf(num); firstElem = 1.f; }
			if (funcType == 4) { true_value = logf(num + 1.f); firstElem = num; }
			
			errorOrder = ERROR(true_value, sumInOrder(fn, firstElem, N, num));
			errorEnd = ERROR(true_value, sumFromTheEnd(fn, firstElem, N, num));
			errorPairs = ERROR(true_value, sumInPairs(fn, firstElem, N, num));

			fprintf_s(file, "%.8f\t%.8f\t%.8f\t%.8f\n", num, errorOrder, errorEnd, errorPairs);
			errorSum[0] += errorOrder;
			errorSum[1] += errorEnd;
			errorSum[2] += errorPairs;
		}
		fprintf_s(file, "   Sum:   \t%.8f\t%.8f\t%.8f\n", errorSum[0], errorSum[1], errorSum[2]);
		fclose(file);
	}
	else
	{
		do
		{
			printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n");
			scanf_s("%d", &summationMethod);
		} while (summationMethod < 1 || summationMethod > 3);

		if (summationMethod == 1) MyFunction = sumInOrder;
		if (summationMethod == 2) MyFunction = sumFromTheEnd;
		if (summationMethod == 3) MyFunction = sumInPairs;
		
		value = MyFunction(fn, firstElem, N, x);
		printf("~ %.8f\n", value);
		printf("= %.8f\n", true_value);
		printf("absolute error = %.8f relative error = %.8f\n", absoluteError(true_value, value), relativeError(true_value, value));
	}
	return 0;
}