#include <iostream>
#include "SLAU.h"

using namespace std;

int main()
{
	bool generation;
	int size;
	setlocale (LC_ALL, "Russian"); 

	cout << "Введите размерность:" << endl; cin >> size;
	cout << "Массив вводится: \n1) рандомно \n0) с клавиатуры" << endl; cin >> generation;
	cout << endl;

	SLAU Gauss(size, generation); 
	try
	{
		cout << "Решение: " << Gauss.solve() << endl;
	}
	catch (exception& ex)
	{
		cout << "Ошибка " << ex.what() << "\n";
	}
	
	return 0;
}

