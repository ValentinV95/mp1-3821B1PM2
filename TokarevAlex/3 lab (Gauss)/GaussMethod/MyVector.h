#include <cstring>
#include <iostream>
using namespace std;

template <class T>
class MyVector
{
protected:
	int size;
	T* vector;

public:

	MyVector(const int size = 5)
	{
		this->size = size;
		vector = new T[size];
	}
	MyVector(const MyVector<T> &other)
	{
		this->size = other.size;
		this->vector = new T[size];
		memcpy(vector, other.vector, size*sizeof(T));
	}
	~MyVector() { delete[] vector; }

	int get_size() { return size; }

	T& operator[] (const int i) { return vector[i]; }

	void resize(int new_size)
	{
		size = new_size;
		delete[] vector;
		vector = new T[size];
	}
	void swap(int first_str, int second_str)
	{
		T temp;
		temp = vector[first_str];
		vector[first_str] = vector[second_str];
		vector[second_str] = temp;
	}
	const T operator * (MyVector<T>& other) const //scalar mult
	{
		T scalar_res = static_cast <T> (0);

		if (size == other.size)
		{
			for (int i = 0; i < size; i++)
				scalar_res += vector[i] * other[i];
		}
		return scalar_res;
	}
	MyVector<T> operator * (const T a)
	{
		MyVector<T> res(size);

		for (int i = 0; i < size; i++)
			res[i] = vector[i] * a;

		return res;
	}
	const MyVector<T>& operator = (const MyVector<T>& other)
	{
		if (vector == other.vector)
			return *this;

		size = other.size;
		resize(size);
		memcpy(vector, other.vector, size * sizeof(T));
		return *this;
	}
	MyVector<T>& operator -= (MyVector<T> other)
	{
		for (int i = 0; i < size; i++)
			vector[i] -= other[i];

		return *this;
	}
};

template<class T>
ostream& operator << (ostream& out, MyVector<T>& vec)
{
	cout << "[";
	for (int i = 0; i < vec.get_size() - 1; i++)
		cout << vec[i] << ' ';

	cout << vec[vec.get_size() - 1] << "]\n";
	cout << "\n";
	return out;
}

template <class T>
istream& operator >> (istream& in, MyVector<T>& vec)
{
	for (int i = 0; i < vec.get_size(); i++)
	{
		cout << "B[" << i + 1 << "] = ";
		cin >> vec[i];
	}
	return in;
}

