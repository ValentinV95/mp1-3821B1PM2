#include <math.h>
#include <stdio.h>
#include<locale.h>

#define N 150

float cosx(float prev, int i, float x)
{
	return (prev * x * x * (-1.f)) / (2 * i * (2 * i - 1.f));
}

float sinx(float prev, int i, float x)
{
	return (prev * x * x * (-1.f)) / (2 * i * (2 * i + 1.f));
}

float expx(float prev, int i, float x)
{
	return (prev * x) / ((float)i);
}

float lnx(float prev, int i, float x)
{
	return ((prev * (-1.f) * x * i) / (i + 1.f));
}

float straight_sum(float* mas)
{
	float sum = 0.0f;
	for (int i = 0; i < N; i++)
	{
		sum += mas[i];
	}
	return sum;
}

float reverse_sum(float* mas)
{
	float sum = 0.0f;
	for (int i = N - 1; i >= 0; i--)
	{
		sum += mas[i];
	}
	return sum;
}

float pairwise_sum(float* mas)
{
	int i;
	float sum = 0.0f;
	for (i = 0; i < N - 1; i += 2)
	{
		mas[i] += mas[i + 1];
	}
	if (N % 2 == 1)
	{
		sum += mas[i + 2];
	}
	for (i = 0; i < N; i += 2)
	{
		sum += mas[i];
	}
	return sum;
}
int main()
{
	enum function{sin=1, cos=2, exp=3, ln=4};
	int choose;
	float* mas;
	float x, prev, function = 0, answer1 = 0, answer2 = 0, answer3 = 0;
	setlocale(LC_ALL, "Russian");
	printf("Выберите функцию:\n1 - sin(x)\n2 - cos(x)\n3 - exp^(x)\n4 - ln(1+x)\n");
	scanf_s("%d", &choose);
	printf("Введите значение x:");
	scanf_s("%f", &x);
	switch (choose)
	{
	case (sin):
		prev = x;
		mas = (float*)malloc(N * sizeof(float));
		mas[0] = x;
		for (int i = 1; i < N; i++)
		{
			prev = sinx(prev, i, x);
			mas[i] = prev;
		}
		answer1 = straight_sum(mas);
		answer2 = reverse_sum(mas);
		answer3 = pairwise_sum(mas);
		function = sinf(x);
		printf("sin(x)= %.8f\n", function);
		free(mas);
		break;
	case (cos):
		prev = 1.f;
		mas = (float*)malloc(N * sizeof(float));
		mas[0] = 1.f;
		for (int i = 1; i < N; i++)
		{
			prev = cosx(prev, i, x);
			mas[i] = prev;
		}
		answer1 = straight_sum(mas);
		answer2 = reverse_sum(mas);
		answer3 = pairwise_sum(mas);
		function = cosf(x);
		printf("cos(x)= %.8f\n", function);
		free(mas);
		break;
	case (exp):
		prev = 1.f;
		mas = (float*)malloc(N * sizeof(float));
		mas[0] = 1.f;
		for (int i = 1; i < N; i++)
		{
			prev = expx(prev, i, x);
			mas[i] = prev;
		}
		answer1 = straight_sum(mas);
		answer2 = reverse_sum(mas);
		answer3 = pairwise_sum(mas);
		function = expf(x);
		printf("e^x= %.8f\n", function);
		free(mas);
		break;
	case (ln):
		prev = x;
		mas = (float*)malloc(N * sizeof(float));
		mas[0] = x;
		for (int i = 1; i < N; i++)
		{
			prev = lnx(prev, i, x);
			mas[i] = prev;
		}
		answer1 = straight_sum(mas);
		answer2 = reverse_sum(mas);
		answer3 = pairwise_sum(mas);
		function = logf(1 + x);
		printf("ln(1+x) = %.8f\n", function);
		free(mas);
		break;
	default:
		printf("Ошибка в выборе операции");
		break;
	}
	printf("| Аргумент X |       function    |         Проверка         |    Абсолютная ошибка    |    Относительная ошибка   |\n");
	printf("Прямое суммирование\n");
	printf("|   %5.2f    | %15.8f |     %16.8f     |     %15.8f     |     %16.8f%%     |\n", x, answer1, function, fabsf((float)function - answer1), fabsf(((float)function - answer1) / function) * 100.f);
	printf("Обратное суммирование\n");
	printf("|   %5.2f    | %15.8f |     %16.8f     |     %15.8f     |     %16.8f%%     |\n", x, answer2, function, fabsf((float)function - answer2), fabsf(((float)function - answer2) / function) * 100.f);
	printf("Попарное суммирование\n");
	printf("|   %5.2f    | %15.8f |     %16.8f     |     %15.8f     |     %16.8f%%     |\n", x, answer3, function, fabsf((float)function - answer3), fabsf(((float)function - answer3) / function) * 100.f);
	return 0;
}