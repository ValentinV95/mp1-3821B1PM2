#pragma once

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cmath>


using namespace std;



class MyException : public exception //������� ����������
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
			cout << "  <!> ������ ������: �������� ������������ � ������������ ������\n";
		}
		if (var == 2)
		{
			cout <<"\n  <!> ������ � ����: ������� ������������ ���������� �� ����\n";
		}
		if (var == 3)
		{
			cout << "\n <!> X ����� ����������� ��������� ������� \n";
		}
		if (var == 4)
		{
			cout << "\n <!> ������� ����� ������ ������ \n";
		}
	}
};