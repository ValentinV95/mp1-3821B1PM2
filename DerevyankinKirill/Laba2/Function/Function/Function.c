#include <stdio.h>
#include <locale.h>
#include <math.h>

double factorial(double number)
{
	if (number == 0 || number == 1)
	{
		return 1;
	}
	else
	{
		return (number * factorial(number - 1));
	}
}

int main()
{
	double x, lastresult = 0, num = 20, sum = 0, number = 1;
	int i, j = 1, choose;
	setlocale(LC_ALL, "Russian");
	printf("Выберите операцию:\n1.sinx\n2.cosx\n3.exp\n4.ln(1+x)\n");
	scanf_s("%d", &choose);
	printf("Введите x:\n");
	scanf_s("%lf", &x);
	switch (choose)
	{
	case 1:
		printf("Прямое суммирование\n");
		printf("| Аргумент X |       sin(x)     |         Проверка         |     Абсолютная ошибка   |   Относительная ошибка   |\n");
		for (i = 0; i < num; i++)
		{
			lastresult = ((pow(x, number) * j) / factorial(number));
			sum += lastresult;
			number += 2;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, sin(x), fabs(sin(x) - sum), fabs((sin(x) - sum) / sin(x)) * 100);
		printf("Обратное суммирование\n");
		for (i = num - 1; i > 0; i--)
		{
			lastresult = ((pow(x, number) * j) / factorial(number));
			sum += lastresult;
			number += 2;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, sin(x), fabs(sin(x) - sum), fabs(((sin(x) - sum) / sin(x))) * 100);
		printf("Попарное суммирование\n");
		for (i = 0; i < (num / 2); i++)
		{
			lastresult = ((pow(x, number)) / factorial(number)) + ((pow(x, number + 2) * (-1)) / factorial(number + 2));
			sum += lastresult;
			number += 4;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, sin(x), fabs(sin(x) - sum), fabs(((sin(x) - sum) / sin(x))) * 100);
		break;
	case 2:
		printf("Прямое суммирование\n");
		printf("| Аргумент X |       cos(x)     |         Проверка        |    Абсолютная ошибка    |    Относительная ошибка   |\n");
		number = 0;
		for (i = 0; i < num; i++)
		{
			lastresult = ((pow(x, number) * j) / factorial(number));
			sum += lastresult;
			number += 2;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, cos(x), fabs(cos(x) - sum), fabs(((cos(x) - sum) / cos(x))) * 100);
		printf("Обратное суммирование\n");
		for (i = num - 1; i > 0; i--)
		{
			lastresult = ((pow(x, number) * j) / factorial(number));
			sum += lastresult;
			number += 2;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, cos(x), fabs(cos(x) - sum), fabs(((cos(x) - sum) / cos(x))) * 100);
		printf("Попарное суммирование\n");
		for (i = 0; i < (num / 2); i++)
		{
			lastresult = ((pow(x, number)) / factorial(number)) + ((pow(x, number + 2) * (-1)) / factorial(number + 2));
			sum += lastresult;
			number += 4;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, cos(x), fabs(cos(x) - sum), fabs(((cos(x) - sum) / cos(x))) * 100);
		break;
	case 3:
		printf("Прямое суммирование\n");
		printf("| Аргумент X |        e^x       |         Проверка        |    Абсолютная ошибка    |    Относительная ошибка   |\n");
		number = 0;
		for (i = 0; i < num; i++)
		{
			lastresult = ((pow(x, number)) / factorial(number));
			sum += lastresult;
			number++;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, exp(x), fabs(exp(x) - sum), fabs(((exp(x) - sum) / exp(x))) * 100);
		printf("Обратное суммирование\n");
		for (i = num - 1; i > 0; i--)
		{
			lastresult = ((pow(x, number)) / (factorial(number)));
			sum += lastresult;
			number++;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, exp(x), fabs(exp(x) - sum), fabs(((exp(x) - sum) / exp(x))) * 100);
		printf("Попарное суммирование\n");
		for (i = 0; i < (num / 2); i++)
		{
			lastresult = ((pow(x, number)) / factorial(number)) + ((pow(x, number + 1)) / factorial(number + 1));
			sum += lastresult;
			number += 2;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, exp(x), fabs(exp(x) - sum), fabs(((exp(x) - sum) / exp(x))) * 100);
		break;
	case 4:
		printf("Прямое суммирование\n");
		printf("Значения ln(1+x) -1<=x<=1\n");
		printf("| Аргумент X |       ln(1+x)    |         Проверка         |    Абсолютная ошибка    |    Относительная ошибка   |\n");
		for (i = 0; i < (num / 2); i++)
		{
			lastresult = ((pow(x, number) * j) / number);
			sum += lastresult;
			number++;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, log(1 + x), fabs(log(1 + x) - sum), fabs(((log(1 + x) - sum) / log(1 + x))) * 100);
		printf("Обратное суммирование\n");
		for (i = num - 1; i > 0; i--)
		{
			lastresult = ((pow(x, number) * j) / number);
			sum += lastresult;
			number++;
			j = j * (-1);
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, log(1 + x), fabs(log(1 + x) - sum), fabs(((log(1 + x) - sum) / log(1 + x))) * 100);
		printf("Попарное суммирование\n");
		for (i = 0; i < (num / 2); i++)
		{
			lastresult = (pow(x, number) / number) + ((pow(x, number + 1) * (-1)) / (number + 1));
			sum += lastresult;
			number += 2;
		}
		printf("|   %5.2f    | %16.22f |     %10.22lf     |     %10.22lf     |     %10.22lf     |\n", x, sum, log(1 + x), fabs(log(1 + x) - sum), fabs(((log(1 + x) - sum) / log(1 + x))) * 100);
		break;
	default:
		printf("Ошибка");
	}
}