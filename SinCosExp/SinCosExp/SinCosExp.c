#include "stdio.h"
#include "stdlib.h"
#include "locale.h"  //Инклюды
#include "float.h"
#include "math.h"

// sinx    = x - x^3/3! + x^5/5! - x^7/7! +    ... 
// cosx    = 1 - x^2/2! + x^4/4! - x^6/6! +    ... // Формулы
// expx    = 1 + x + x^2/2! + x^3/3! + x^4/4! +...
// ln(1+x) = x + x^2/2 + x^3/3 + x^4/4 + x^5/5+...



//Функции подсчета следующего элемента

//Функции подсчета следующего элемента через сумму

//Функции подсчета следующего элемента для синуса два особых способа

float next_sin1(float pred, float x, int i)
{
	float u = (pred * x * x) / ((2.0 * i) * (2.0 * i + 1.0));
	if (x > 0)
		if (u > FLT_EPSILON)
			return u;
		else return 0.0;
	else
		if (-u > FLT_EPSILON)
			return u;
		else return 0.0;
}

float next_sin2(float pred, float x, int i)
{
	float predr;
	predr = pred * x / (2.0 * i + 1.0);
	predr *= x;
	predr = predr / (2.0 * i);
	return predr;
}



float next_lnx(float pred, float x, int i)
{
	return i * pred * x / (i + 1.0);
}

float next_cos(float pred, float x, int i)
{
	return pred * x * x / (2.0 * i - 1) / (2.0 * i);
}

float next_exp(float pred, float x, int i)
{
	return pred * x / (i + 0.0);
}





//Функции подсчета следующего элемента через рекурсию

float recsin(float x, float xc, int i)
{
	if (x > 0)
		if (x > FLT_EPSILON)
		{
			if (i % 2 != 0)
				return -x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
			else
				return x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
		}
		else return x;
	else
		if (-x > FLT_EPSILON)
		{
			if (i % 2 != 0)
				return -x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
			else
				return x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
		}
		else return x;
}

float reccos(float x, float xc, int i)
{
	if (x > 0)
		if (x > FLT_EPSILON)
		{
			if (i % 2 != 0)
				return -x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
			else
				return x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
		}
		else return x;
	else
		if (-x > FLT_EPSILON)
		{
			if (i % 2 != 0)
				return -x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
			else
				return x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
		}
		else return x;
}

float recexp(float x, float xc, int i)
{
	if (x > 0)
		if (x > FLT_EPSILON && i < 4000)
			return x + recexp(x * xc / (i + 1.0), xc, i + 1);
		else return x;
	else
		if (-x > FLT_EPSILON && i < 4000)
			return x + recexp(x * xc / (i + 1.0), xc, i + 1);
		else return x;
}

float recln(float x, float xc, int i) //Возращает 0 если число болше 1 или меньше -1
{
	if ((x <= 1 && x > -1) && (i < 3500 && xc != 1))
	{
		if (x > FLT_EPSILON)
		{
			if (i % 2 == 0)
				return -x + recln(x * xc * i / (i + 1.0), xc, i + 1);
			else
				return x + recln(x * xc * i / (i + 1.0), xc, i + 1);
		}
		else return x;
	}
	else if (xc == 1.0) return 0.693147;
	else
		return 0.0;
}



int main()
{
	float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078;
	int   x1, i = 1;
	float y, x;                                //Инициализация
	float rs, rc, re, rl;
	float expx, cosx, sinx, sinx2, lnx;
	float predl, preds, preds2, predc, prede;
	float sum1s, sum1c, sum1e, sum1l, sum2s, sum2c, sum2e, sum2l, summs, summc, summe, summl;

	setlocale(LC_ALL, "Rus");
	printf("Введите x = ");      //Простая меню
	scanf_s("%f", &x);

	y = x;/*
	if (x>0)
	while (x - 2 * PI > 0)
	{                       //Вычитание из числа периода
		x -= 2*PI;
	}
	if (x<0)
	while (x < 0)
	{
		x += 2*PI;
	}
	*/
	lnx = y;
	predl = y;
	if (y > 1 || y <= -1)   // Проверка интервала x (-1;1] Возращает 0 если число болше 1 или меньше -1
	{
		lnx = 0;
		predl = 0;
	}
	rl = recln(y, y, 1);

	sinx = x;
	preds = x;
	rs = recsin(x, x, 0);

	sinx2 = x;
	preds2 = x;
	//Первые эементы в функции и ее подсчет через рекурсию
	cosx = 1;
	predc = 1;
	rc = reccos(1.0, x, 0);

	expx = 1;
	prede = 1;
	re = recexp(1.0, y, 0);

	summs = preds;
	summc = predc;
	summe = prede;
	summl = predl;

	sum1s = 0.0;
	sum1c = 0.0;
	sum1e = 0.0;
	sum1l = 0.0;

	sum2s = 0.0;
	sum2c = 0.0;
	sum2e = 0.0;
	sum2l = 0.0;

	while (i <= 50000)  //Подсчет функций через сумму до 50 000 элементов
	{

		if (i % 2 == 0) x1 = 1;
		else x1 = -1;

		predl = next_lnx(predl, y, i);
		preds = next_sin1(preds, x, i);
		preds2 = next_sin2(preds2, x, i);
		predc = next_cos(predc, x, i);
		prede = next_exp(prede, y, i);

		lnx += x1 * predl;
		sinx += x1 * preds;
		sinx2 += x1 * preds2;
		cosx += x1 * predc;
		expx += prede;



		if (i % 4 == 0)
		{
			sum1s += x1 * preds;
			sum1c += x1 * predc;
			sum1e += prede;
			sum1l += x1 * predl;
		}
		if (i % 4 == 1)
		{
			sum1s += x1 * preds;
			sum1c += x1 * predc;
			sum1e += prede;
			sum1l += x1 * predl;
		}
		if (i % 4 == 2)
		{
			sum2s += x1 * preds;
			sum2c += x1 * predc;
			sum2e += prede;
			sum2l += x1 * predl;
		}
		if (i % 4 == 3)
		{
			sum2s += x1 * preds;
			sum2c += x1 * predc;
			sum2e += prede;
			sum2l += x1 * predl;
			summs += sum1s + sum2s;
			summc += sum1c + sum2c;
			summe += sum1e + sum2e;
			summl += sum1l + sum2l;

			sum1s = 0.0;
			sum1c = 0.0;
			sum1e = 0.0;
			sum1l = 0.0;

			sum2s = 0.0;
			sum2c = 0.0;
			sum2e = 0.0;
			sum2l = 0.0;
		}
		i++;
	}
	//Ответ

	double g1 = ((sin(y) - sinx) / sin(y)) * 100, g2 = sinx - sin(y);
	double g3 = ((cos(y) - cosx) / cos(y)) * 100, g4 = cosx - cos(y);
	double g5 = ((exp(y) - expx) / exp(y)) * 100, g6 = expx - exp(y);
	double g7 = ((log(y + 1.0) - lnx) / log(y + 1.0)) * 100, g8 = lnx - log(y + 1.0);
	printf("\nx = %lf\n\nSumm method\n\n", y);
	printf(" my sinx = %f    real sinx = %lf facterror = %lf abserror = %.16lf\n", sinx, sin(y), g1, g2);
	printf(" my cosx = %f    real cosx = %lf facterror = %lf abserror = %.16lf\n", cosx, cos(y), g3, g4);
	printf(" my expx = %f    real expx = %lf facterror = %lf abserror = %.16lf\n", expx, exp(y), g5, g6);
	printf("myln(1+x)= %f   realln(1+x)= %lf facterror = %lf abserror = %.16lf\n", lnx, log(y + 1.0), g7, g8);
	printf("\n");
	printf("my sinx1 = %.16lf   my sinx2 = %.16lf  real sinx = %.16lf", sinx, sinx2, sin(y));
	printf("\n\nRecurs method\n\n");
	g1 = ((sin(y) - rs) / sin(y)) * 100, g2 = rs - sin(y);
	g3 = ((cos(y) - rc) / cos(y)) * 100, g4 = rc - cos(y);
	g5 = ((exp(y) - re) / exp(y)) * 100, g6 = re - exp(y);
	g7 = ((log(y + 1.0) - rl) / log(y + 1.0)) * 100, g8 = rl - log(y + 1.0);
	printf(" my sinx = %f    real sinx = %lf facterror = %lf abserror = %.16lf\n", rs, sin(y), g1, g2);
	printf(" my cosx = %f    real cosx = %lf facterror = %lf abserror = %.16lf\n", rc, cos(y), g3, g4);
	printf(" my expx = %f    real expx = %lf facterror = %lf abserror = %.16lf\n", re, exp(y), g5, g6);
	printf("myln(1+x)= %f   realln(1+x)= %lf facterror = %lf abserror = %.16lf\n", rl, log(y + 1.0), g7, g8);
	printf("\n\double summ method\n\n");
	g1 = ((sin(y) - summs) / sin(y)) * 100, g2 = summs - sin(y);
	g3 = ((cos(y) - summc) / cos(y)) * 100, g4 = summc - cos(y);
	g5 = ((exp(y) - summe) / exp(y)) * 100, g6 = summe - exp(y);
	g7 = ((log(y + 1.0) - summl) / log(y + 1.0)) * 100, g8 = summl - log(y + 1.0);
	printf(" my sinx = %f    real sinx = %lf facterror = %lf abserror = %.16lf\n", summs, sin(y), g1, g2);
	printf(" my cosx = %f    real cosx = %lf facterror = %lf abserror = %.16lf\n", summc, cos(y), g3, g4);
	printf(" my expx = %f    real expx = %lf facterror = %lf abserror = %.16lf\n", summe, exp(y), g5, g6);
	printf("myln(1+x)= %f   realln(1+x)= %lf facterror = %lf abserror = %.16lf\n", summl, log(y + 1.0), g7, g8);


}