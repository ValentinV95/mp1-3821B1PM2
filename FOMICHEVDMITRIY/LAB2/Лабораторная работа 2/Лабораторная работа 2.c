#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

const float Pi = 3.1415926535897932384;
int st = 0;

long long int fct(int a)
{
	int i;
	long long result = 1;
    
	if (a == 0)
	{
		return result;
	}

	else
	{
		for (i = 1; i <= a; i++)
		{
			result *= i;
		}

		return result;
	}
}

float sign(int i, int status)
{
	if (status == 1)
	{
		if (i % 4 == 1)
		{
			return 1;
		}

		else
		{
			return -1;
		}
	}

	if (status == 2)
	{
		if (i % 4 == 0)
		{
			return 1;
		}

		else
		{
			return -1;
		}
	}
}

float tr(float a)
{
	//printf("\n%lf\n", a);
	if ((a >= Pi) && (a <= 3 * Pi / 2))
	{
		a -= Pi;
		st = 3;
	}

	if ((a >= 3 * Pi / 2) && (a <= 2 * Pi))
	{
		a -= Pi;
		st = 4;
	}

	//printf("\n%lf\n", a);

	return a;
}

float dtr(float a)
{
	int status = 0;

	if (a < 0)
	{
		while (a < 0)
		{
			a += (2 * Pi);
			//printf("a = %lf\n", a);
		}
	}

	else
	{
		while (a >= 2 * Pi)
		{
			a -= (2 * Pi);
			//printf("a = %lf\n", a);
		}
	}

	a = tr(a);

	return a;
}

float tr_sign(int status)
{
	//printf("\n\nфункция = %d    четверь = %d \n\n", status, st);
	if (status == 2)
	{
		if (st == 3)
		{
			return -1;
		}

		if (st == 4)
		{
			//printf("\n\nITSWORK\n\n");
			return -1;
		}

		else
		{
			return 1;
		}
	}

	else
	{
		if (st == 0)
		{
			return 1;
		}

		else
		{
			return -1;
		}
	}
}

float exponent(float a)
{
	int i;
	float result = 1.0;

	for (i = 1; i < 21; i++)
	{
		result += powf(a, i) / fct(i);
	}

	return result;
}

float r_exponent(float a)
{
	int i;
	float p = 0;

	for (i = 19; i > -1; i--)
	{
		p += powf(a, i) / fct(i);
	}

	return p;
}

float ln(float a)
{
	int i;
	float t = (a - 1) / (a + 1);
	float p = 0;

	if (a == 1)
	{
		return p;
	}

	else
	{
		for (i = 1; i < 23; i += 2)
		{
			p += powf(t, i) / i;
		    //printf("%lf\n", pow(t, i) / i);
		}
    }

	p *= 2;

	return p;
}

float r_ln(float a)
{
	int i;
	float t = (a - 1) / (a + 1);
	float p = 0;

	if (a == 1)
	{
		return p;
	}

	else
	{
		for (i = 21; i > 0; i -= 2)
		{
			p += powf(t, i) / i;
			//printf("%lf\n", pow(t, i) / i);
		}
	}

	p *= 2;

	return p;
}

float duo_sinus(float a)
{
	float Brray[5];
	float Array[10];
	float p = 0;
	int i, m = 0;

	a = dtr(a);

	(float)a;

	for (i = 1; i < 20; i += 2)
	{
		Array[m] = (float)sign(i, 1) * (float)powf(a, i) / fct(i);
		//printf("%f\n", Array[m]);
		m++;
	}

	m = 0;

	for (i = 0; i < 10; i += 2)
	{
		Brray[m] = Array[i] + Array[i + 1];
		m++;
	}

	for (i = 0; i < 5; i++)
	{
		p += Brray[i];
	}

	p *= (float)tr_sign(1);

	return p;

}

float sinus(float a)
{
	int i;
	float p = 0;

	a = dtr(a);

	//printf("\n\n\n%lf\n", a);

	for (i = 1; i < 20; i += 2)
	{
		p += sign(i, 1) * powf(a, i) / fct(i);
		//printf("%lf\n", sign(i) * pow(a, i) / fct(i));
	}

	p *= tr_sign(1);

	return p;
}

float r_sinus(float a)
{
	int i;
	float p = 0;

	a = dtr(a);

	for (i = 19; i > 0; i -= 2)
	{
		p += sign(i, 1) * powf(a, i) / fct(i);
		//printf("%lf\n", sign(i) * pow(a, i) / fct(i));
	}

	p *= tr_sign(1);

	return p;
}

float cosinus(float a)
{
	int i;
	float p = 0;

	a = dtr(a);

	//printf("\n\n\n%lf\n", a);

	for (i = 0; i < 20; i += 2)
	{
		p += sign(i, 2) * powf(a, i) / fct(i);
		//printf("%lf\n", sign(i, 2) * pow(a, i) / fct(i));
		//printf("p = %lf\n", p);
	}

	//printf("SIGN   ++++ %lf\n", tr_sign(2));
	p *= tr_sign(2);


	return p;
}

float r_cosinus(float a)
{
	int i;
	float p = 0;

	a = dtr(a);

	//printf("\n\n\n%lf\n", a);

	for (i = 18; i > -1; i -= 2)
	{
		p += sign(i, 2) * powf(a, i) / fct(i);
		//printf("%lf\n", sign(i, 2) * pow(a, i) / fct(i));
		//printf("p = %lf\n", p);
	}

	//printf("SIGN   ++++ %lf\n", tr_sign(2));
	p *= tr_sign(2);


	return p;
}

float duo_cosinus(float a)
{
	float Brray[5];
	float Array[10];
	float p = 0;
	int i, m = 0;

	a = dtr(a);

	(float)a;

	for (i = 0; i < 20; i += 2)
	{
		Array[m] = (float)sign(i, 2) * (float)powf(a, i) / fct(i);
		//printf("%f\n", Array[m]);
		m++;
	}

	m = 0;

	for (i = 0; i < 10; i += 2)
	{
		Brray[m] = Array[i] + Array[i + 1];
		m++;
	}

	for (i = 0; i < 5; i++)
	{
		p += Brray[i];
	}

	p *= (float)tr_sign(1);

	return p;

}

void warning(int status)
{
	if (status == 4)
	{
		printf("(Помните, логарифм не может быть от 0 или от отрицательного числа)");
	}
}

void error(float a, float b)
{
	float c = 0, d = 0;

	c = fabsf(a - b);
	d = fabsf(c / a) * 100;

	printf("Абсолютная погрешность:                      %.20f\n", c);
	printf("Относительная погрешность:                   %.20f%%\n\n", d);
}

void main()
{
	int choice;
	float argument = 1;

	setlocale(LC_ALL, "Russian");

	while (1)
	{
		system("cls");

		printf("Выберите функцию:\n1) Синус\n2) Косинус\n3) Экспонента\n4) Натуральный логарифм\n\nВаш выбор: ");
		scanf_s("%d", &choice);
		getchar();

		printf("Введите аргумент");
		warning(choice);
		printf(": ");
		scanf_s("%f", &argument);
		getchar();

		if ((choice == 4) && (argument <= 0))
		{
			printf("Логарифм не может быть от 0 или от отрицательного числа");
		}

		else
		{
			switch (choice) {
			case 1:
			{
				printf("\nСинус из библиотеки:                         %.20f\n\n", sinf(argument));
				printf("Синус, прямое суммирование:                  %.20f\n", sinus(argument));
				error(sinf(argument), sinus(argument));
				printf("Синус, обратное суммирование:                %.20f\n", r_sinus(argument));
				error(sinf(argument), r_sinus(argument));
				printf("Синус, парное суммирование:                  %.20f\n", duo_sinus(argument));
				error(sinf(argument), duo_sinus(argument));


				break;
			}

			case 2:
			{
				printf("\nКосинус из библиотеки:                       %.20f\n\n", cosf(argument));
				printf("Косинус, прямое суммирование:                %.20f\n", cosinus(argument));
				error(cosf(argument), cosinus(argument));
				printf("Косинус, обратное суммирование:              %.20f\n", r_cosinus(argument));
				error(cosf(argument), r_cosinus(argument));
				printf("Косинус, парное суммирование:                %.20f\n", duo_cosinus(argument));
				error(cosf(argument), duo_cosinus(argument));

				break;
			}

			case 3:
			{
				printf("\nЭкспонента из библиотеки:                    %.20f\n\n", expf(argument));
				printf("Экспонента, прямое суммирование:             %.20f\n", exponent(argument));
				error(expf(argument), exponent(argument));
				printf("Экспонента, обратное суммирование:           %.20f\n", r_exponent(argument));
				error(expf(argument), r_exponent(argument));
				break;
			}

			case 4:
			{
				printf("\nНатуральный логарифм из библиотеки:          %.20f\n\n", logf(argument));
				printf("Натуральный логарифм, прямое суммирование:   %.20f\n", ln(argument));
				error(logf(argument), ln(argument));
				printf("Натуральный логарифм, обратное суммирование: %.20f\n", r_ln(argument));
				error(logf(argument), r_ln(argument));
				break;
			}

			default:
			{
				printf("Такой функции нет\n");
				break;
			}
			}
		}

		getchar();

	}
}