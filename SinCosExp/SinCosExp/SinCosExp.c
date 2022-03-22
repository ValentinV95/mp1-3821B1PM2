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

double next_sin1(double pred, double x, int i) 
{
	double u = (pred * x * x) / ((2.0 * i) * (2.0 * i + 1.0));
	if (u > DBL_EPSILON)
		return u;
	else return 0.0;
}

double next_sin2(double pred, double x, int i)
{
	double predr;
	predr = pred * x / (2.0 * i + 1.0);
	predr *= x;
	predr = predr / (2.0 * i);
	return predr;
}



double next_lnx(double pred, double x, int i)
{
	return i * pred * x / (i + 1.0);
}

double next_cos(double pred, double x, int i)
{
	return pred * x * x / (2.0 * i - 1) / (2.0 * i);
}

double next_exp(double pred, double x, int i)
{
	return pred * x/(i+0.0);
}





//Функции подсчета следующего элемента через рекурсию

double recsin(double x, double xc, int i)
{
	if (x > DBL_EPSILON)
	{
		if (i%2 != 0)
			return -x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
		else 
			return x + recsin(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
	}
	else return x;
}

double reccos(double x, double xc, int i)
{
	if (x > DBL_EPSILON)
	{
		if (i % 2 != 0)
			return -x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
		else 
			return x + reccos(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
	}
	else return x;
}

double recexp(double x, double xc, int i)
{
	if (x > DBL_EPSILON && i < 4000)
		return x + recexp(x * xc / (i + 1.0), xc, i + 1);
	else return x;
}

double recln(double x, double xc, int i) //Возращает 0 если число болше 1 или меньше -1
{
	if ((x <= 1 && x > -1) && i < 4000)
	{
		if (x > DBL_EPSILON)
		{
			if (i % 2 == 0)
				return -x + recln(x * xc * i / (i + 1.0), xc, i + 1);
			else 
				return x + recln(x * xc * i / (i + 1.0), xc, i + 1);
		}
		else return x;
	}
	else
	return 0.0;
}



int main()
{
	double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078;
	int isave, x1, i = 1;
	double y, x;                                //Инициализация
	double rs, rc, re, rl;
	double expx,cosx,sinx,sinx2,lnx;
	double predl, preds, preds2, predc, prede;

	setlocale(LC_ALL, "Rus");
	printf("Введите x = ");      //Простая меню
	scanf_s("%lf", &x);
	
	y = x;/*
	while (x - 2 * PI > 0)
	{                       //Вычитание из числа периода
		x -= 2*PI;
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

	while (i < 50000)  //Подсчет функций через сумму до 50 000 элементов
		{

		isave = i;

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

		i++;

		}
	//Ответ

	double r1 = ((sin(y) - sinx) / sin(y))*100,r2 = sinx - sin(y);
	double r3 = ((cos(y) - cosx) / cos(y)) * 100, r4 = cosx - cos(y);
	double r5 = ((exp(y) - expx) / exp(y)) * 100, r6 = expx - exp(y);
	double r7 = ((log(y+1) - lnx) / log(y+1)) * 100, r8 = lnx - log(y+1);
	printf("\nx = %lf\nSumm method\n\n",y);
	printf(" my sinx = %lf    real sinx = %lf facterror = %lf abserror = %.16lf\n", sinx, sin(y), r1, r2  );
	printf(" my cosx = %lf    real cosx = %lf facterror = %lf abserror = %.16lf\n", cosx, cos(y), r3, r4  );
	printf(" my expx = %lf    real expx = %lf facterror = %lf abserror = %.16lf\n", expx, exp(y), r5, r6  );
	printf("myln(1+x)= %lf   realln(1+x)= %lf facterror = %lf abserror = %.16lf\n", lnx , log(y+1), r7, r8);
	printf("\n");
	printf("my sinx1 = %.16lf   my sinx2 = %.16lf  real sinx = %.16lf", sinx, sinx2, sin(y));
	printf("\n\nRecurs method\n\n");
	double g1 = ((sin(y) - rs) / sin(y)) * 100, g2 = rs - sin(y);
	double g3 = ((cos(y) - rc) / cos(y)) * 100, g4 = rc - cos(y);
	double g5 = ((exp(y) - re) / exp(y)) * 100, g6 = re - exp(y);
	double g7 = ((log(y + 1) - rl) / log(y + 1)) * 100, g8 = rl - log(y + 1);
	printf(" my sinx = %lf    real sinx = %lf facterror = %lf abserror = %.16lf\n", rs, sin(y), g1, g2);
	printf(" my cosx = %lf    real cosx = %lf facterror = %lf abserror = %.16lf\n", rc, cos(y), g3, g4);
	printf(" my expx = %lf    real expx = %lf facterror = %lf abserror = %.16lf\n", re, exp(y), g5, g6);
	printf("myln(1+x)= %lf   realln(1+x)= %lf facterror = %lf abserror = %.16lf\n", rl, log(y + 1), g7, g8);

}
