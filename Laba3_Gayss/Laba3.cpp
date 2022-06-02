#include <iostream>
#include "ClassVector.h"
#include "Matrix1.h"
#include <stdio.h>      
#include <time.h>
#include <locale.h>


int main() {
	int N;
	int k;
	setlocale(LC_ALL, "Rus");
	cout << "Введите число N, размерность квадратной матрицы: ";
	cin >> N;
	cout << endl;
	Vector<double> stroka(N);
	Gauss systema(N, stroka);
	Vector<double> otvet(N);
	cout << "Нажмите 1, если вы хотите ввести матрицу вручную" << endl;
	cout << "Нажмите 2, если вы хотите заполнить матрицу случайными числами" << endl;
	cin >> k;
	if (k == 1)
	{
		cout << "Введите систему линейных уравнений: " << endl;
		cin >> systema;
	}
	if (k == 2)
	{
		systema.random();
		cout << "Исходная система:\n";
		cout << systema;
	}
	try
	{
		otvet = systema.Solve();
		cout << "Треугольная система: " << endl;
		cout << systema;
		cout << "Вектор решений: " << endl;
		cout << otvet << endl;

	}
	catch (exception error)
	{
		cout << "Ошибка " << error.what() << endl;
	}

	return (0);
}
