#include <cstring>
#include <iostream>
using namespace std;

template <class T>
class classVector
{
protected:
	int size;
	T* vector;

public:

	classVector(const int size = 5)
	{
		this->size = size;
		vector = new T[size];
	}
	classVector(const classVector<T>& other)
	{
		this->size = other.size;
		this->vector = new T[size];
		memcpy(vector, other.vector, size * sizeof(T));
	}
	~classVector() { delete[] vector; }

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
	const T operator * (classVector<T>& other) const 
	{
		if (size == other.size)
		{
			T scalar_res = static_cast <T> (0);

			for (int i = 0; i < size; i++)
				scalar_res += vector[i] * other[i];

			return scalar_res;
		}
		else throw exception("Dot product of vectors of different lengths");
	}
	classVector<T> operator * (const T a)
	{
		classVector<T> res(size);

		for (int i = 0; i < size; i++)
			res[i] = vector[i] * a;

		return res;
	}
	const classVector<T>& operator = (const classVector<T>& other)
	{
		if (vector == other.vector)
			return *this;

		size = other.size;
		resize(size);
		memcpy(vector, other.vector, size * sizeof(T));
		return *this;
	}
	classVector<T>& operator -= (classVector<T> other)
	{
		for (int i = 0; i < size; i++)
			vector[i] -= other[i];

		return *this;
	}
};

template<class T>
ostream& operator << (ostream& out, classVector<T>& vec)
{
	cout << "[";
	for (int i = 0; i < vec.get_size() - 1; i++)
		cout << vec[i] << ' ';

	cout << vec[vec.get_size() - 1] << "]\n";
	cout << "\n";
	return out;
}

template <class T>
istream& operator >> (istream& in, classVector<T>& vec)
{
	for (int i = 0; i < vec.get_size(); i++)
	{
		cout << "B[" << i + 1 << "] = ";
		cin >> vec[i];
	}
	return in;
}