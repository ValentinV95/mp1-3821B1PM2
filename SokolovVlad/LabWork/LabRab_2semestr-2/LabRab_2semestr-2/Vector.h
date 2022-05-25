#pragma once

#include"Exceptions.h"


template<class T>class Vector
{
public:

	T* array = new T;
	int size = 1;


	Vector() {}
	Vector(int n)
	{
		size = n;
		array = new T[size];
	}

	void change_size(int n)
	{
		array = new T[n];
		size = n;
	}

	void set() //  -->  b:        ( Ax=b ) 
	{
		cout << "\n\n        > Введите значение вектора b\n";
		for (int i = 0; i < size; i++)
		{
			cin >> array[i];
		}
	}

	~Vector()
	{
		delete[]array;
	}

	// --------------- [ Перегрузки оппераций ] -------------------- //

	Vector& operator=(Vector& a)
	{

		array = new T[a.size];
		for (int i = 0; i < a.size; i++)
		{
			array[i] = a.array[i];

		}
		return *this;
	}

	Vector& operator-=(Vector& a)
	{
		for (int i = 0; i < size; i++)
		{
			array[i] -= a.array[i];
		}
		return *this;
	}

	Vector& operator*=(T s)
	{
		for (int i = 0; i < size; i++)
		{
			array[i] *= s;
		}
		return *this;
	}

	T operator[](int i)
	{
		return array[i];
	}

	ostream& operator<<(ostream& out)
	{
		cout << "(";
		for (int i = 0; i < size - 1; i++)
		{
			cout << array[i] << ", ";
		}
		out << "";
		cout << array[size - 1] << ")";
		return out;
	}
};