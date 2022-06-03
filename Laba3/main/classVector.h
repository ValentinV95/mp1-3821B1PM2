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

	classVector(int size = 7)
	{
		this->size = size;
		vector = new T[size];
	}
	classVector(const classVector& vect)
	{
		this->size = vect.size;
		this->vector = new T[size];
		memcpy(vector, vect.vector, size * sizeof(T));
	}
	~classVector() { delete[] vector; }

	int get_size() { return size; }

	T& operator[] (const int i) { return vector[i]; }
    void swap(int f, int s)
	{
		T k;
		k = vector[f];
		vector[f] = vector[s];
		vector[s] = k;
	}
	void resize(int new_size)
	{
		size = new_size;
		delete[] vector;
		vector = new T[size];
	}
	
	const T operator * (classVector<T>& s) const 
	{
		if (size == s.size)
		{
			T scal = (T) 0;

			for (int i = 0; i < size; i++)
				scal += vector[i] * s[i];
			return scal;
		}
		else throw exception("Длины векторов различны ");
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
	if (vec.get_size() <= 10) cout << "[";
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

