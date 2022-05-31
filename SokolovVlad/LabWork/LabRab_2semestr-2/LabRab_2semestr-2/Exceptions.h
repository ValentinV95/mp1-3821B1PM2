#pragma once

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cmath>


using namespace std;



class MyException : public exception //бросает исключения
{
private:
	int var;
public:
	MyException(int n)
	{
		var = n;
	}
	void show()
	{
		if (var == 1)
		{
			cout << "  <!> Ошибка памяти: неверное расположение в динамической памяти\n";
		}
		if (var == 2)
		{
			cout <<"\n  <!> Ошибка в СЛАУ: нулевые коэффициенты возвращают не ноль\n";
		}
		if (var == 3)
		{
			cout << "\n <!> X имеет бесконечное множество решений \n";
		}
		if (var == 4)
		{
			cout << "\n <!> вектора имеют разный размер \n";
		}
	}
};