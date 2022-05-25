#pragma once
#include "ClassVector.h"
#include <stdio.h>      
#include <time.h>
template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix(size_t stolb, const Vector<T>& stroka) : Vector<Vector<T>>(stolb, stroka) {}
};


template <typename T>
class Gauss : public Matrix<T> {
public:
	Gauss(size_t stolb, const Vector<T>& stroka) : Matrix<T>(stolb, stroka) {};


Vector<T> Otvet(int &a) {

	size_t razmer = this->GetSize(); 
	Vector<T> otvet(razmer);
	size_t max; 
	a = 0;
	int zero = 0;
	
	for (size_t i = 0; i < razmer; i++) {
		zero = 0;
		for (size_t j = i + 1; j < razmer; j++) 
			if ((*this)[i][j] == 0) zero++;
		if (zero == razmer) a=3;
	}


	for (size_t i = 0; i < razmer; i++) {
		max = i;
		for (size_t j = i + 1; j < razmer; j++) {
			if ((*this)[i][j] * (*this)[i][j] > (*this)[i][max] * (*this)[i][max]) max = j;
		}
		swap<Vector<T>>((*this)[i], (*this)[max]); 
		(*this)[i] = (*this)[i] / (*this)[i][i];
		for (size_t j = i + 1; j < razmer; j++) (*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i]);
	}

	for (int i = razmer - 1; i >= 0; i--) {
		otvet[i] = (*this)[i][razmer];
		for (int j = razmer - 1; j >= i + 1; j--)   otvet[i] = otvet[i] - (*this)[i][j] * otvet[j];
	}
	int check = 1;
	for (int i = 0; i < razmer; i++)
		check = check * (*this)[i][i];
	if (check != 0)
		return otvet;
	else {
		a=1;
		return otvet;
	}
}
void random()
{
	size_t raz = this->GetSize();
	srand(time(NULL));
	for (int i = 0; i < raz; i++)
		for (int j = 0; j < raz+1; j++)
		{
			(*this)[i][j] = rand();
		}
	
}
};


