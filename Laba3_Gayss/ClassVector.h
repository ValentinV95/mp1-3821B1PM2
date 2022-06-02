#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::exception;
using std::ostream;
using std::istream;

template <typename T>
void swap(T& a, T& b) {
	if (&a != &b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

template <typename T>
class Vector
{
protected:
	T* mas;
	size_t size;
public:

	Vector() {
		size = 0;
		mas = new T[0];
	}
	Vector(size_t size) {
		this->size = size;
		mas = new T[size];
	}
	Vector(size_t size, T elm) {
		this->size = size;
		mas = new T[size];
		for (size_t i = 0; i < size; i++)
			mas[i] = elm;
	}
	Vector(const Vector& vec)
	{
		size = vec.size;
		mas = new T[size];
		for (size_t i = 0; i < size; i++)
			mas[i] = vec.mas[i];
	}

	Vector operator+ (const Vector& vec) {
		if (this->size != vec.size) throw exception("Проблема с размерностью векторов.");
		Vector res = *this;
		for (size_t i = 0; i < size; i++)
			res.mas[i] += vec.mas[i];
		return res;
	}

	Vector operator- (const Vector& vec) {
		if (this->size != vec.size) throw exception("Проблема с размерностью векторов.");

		Vector res = *this;
		for (size_t i = 0; i < size; i++)
			res.mas[i] -= vec.mas[i];

		return res;
	}

	Vector operator-= (const Vector& vec) {
		if (this->size != vec.size) throw exception("Проблема с размерностью векторов.");

		for (size_t i = 0; i < size; i++)
			mas[i] -= vec.mas[i];

		return *this;
	}

	Vector operator*(const T& number) {
		Vector res = *this;
		for (size_t i = 0; i < size; i++)
			res.mas[i] *= number;

		return res;
	}

	const T operator * (Vector<T>& other) const
	{
		if (size == other.size)
		{
			T scalar_res = static_cast <T> (0);

			for (int i = 0; i < size; i++)
				scalar_res += mas[i] * other[i];

			return scalar_res;
		}
		else throw exception("Проблема с размерностью векторов.");
	}

	Vector operator/ (const T& number) {
		Vector res = *this;
		for (size_t i = 0; i < size; i++)
			res.mas[i] /= number;
		return res;
	}

	Vector& operator= (const Vector& vec) {
		if (size != vec.size) {
			size = vec.size;
			delete[] mas;
			mas = new T[size];
		}
		for (size_t i = 0; i < size; i++)
			mas[i] = vec.mas[i];

		return *this;
	}

	~Vector() {
		delete[] mas;
	}

	T& operator [](size_t i) const
	{
		return(mas[i]);
	}

	size_t GetSize() { return size; }

	friend ostream& operator<< (ostream& ost, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++)
			ost << vec.mas[i] << " ";
		ost << endl;
		return ost;
	}
	friend istream& operator>> (istream& ist, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++)
			ist >> vec.mas[i];

		return ist;
	}
};

