#include <iostream>
#include <exception>
#include <locale.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

template <class T> class Vector
{
protected:
	T* massive;
	int size;
public:
	Vector(int size = 5)
	{
		this->size = size;
		massive = new T[size];
	}
	Vector(const Vector& vec)
	{
		size = vec.size;
		massive = new T[size];
		for (int i = 0; i < size; i++)
		{
			massive[i] = vec.massive[i];
		}
	}
	~Vector()
	{
		delete[] massive;
	}

	int Get_size()
	{
		return size;
	}

	void random(int size)
	{
		double min = -100.0;
		double max = 100.0;
		srand(1000);
		for (int i = 0; i < size; i++)
		{
			massive[i] = min + (double)(rand()) / (double)(RAND_MAX / (max - min));
		}
	}

	Vector& operator=(const Vector other)
	{
		delete[] massive;
		this->size = other.size;
		massive = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->massive[i] = other.massive[i];
		}
		return *this;
	}

	Vector<T>& operator +=(Vector<T> other)
	{
		for (int i = 0; i < size; i++)
		{
			massive[i] += other[i];
		}
		return *this;
	}

	T& operator[](int index)
	{
		if (index > size)
		{
			throw exception("Выход за границу массива");
		}
		else
		{
			return this->massive[index];
		}
	}

	void resize(int new_size)
	{
		delete[] massive;
		size = new_size;
		massive = new T[size];
	}

	void swap(int i, int j)
	{
		T a = massive[i];
		massive[i] = massive[j];
		massive[j] = a;
	}

	const T operator*(Vector<T> &a) const
	{
		T scalar = (T) 0;
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				scalar += massive[i] * a[i];
			}
		}
		return scalar;
	}

	const Vector<T> operator*(const T a) const 
	{
		Vector<double> num(size);
		for (int i = 0; i < size; i++)
		{
			num[i] = massive[i] * a;
		}
		return num;
	}

	const Vector<T> operator+ (const Vector<T>& a) const
	{
		Vector<T> tmp(size);
		for (int i = 0; i < size; i++)
		{
			tmp[i] = massive[i] + a[i];
		}
		return tmp;
	}
};

template<class T> class Matrix : public Vector<Vector<T>>
{
private:
	int size;

public:
	Matrix(int size) : Vector<Vector<T>>(size)
	{
		this->size = size;
		for (int i = 0; i < size; i++)
		{
			this->massive[i].resize(size);
		}
	}

	Matrix(Matrix& mat):Vector<Vector<T>>(mat.Get_size())
	{
		this->size = mat.size;
		for (int i = 0; i < size; i++)
		{
			this->massive[i] = mat[i];
		}
	}

	int Get_size()
	{
		return size;
	}

	void random(int size)
	{
		double min = -100.0;
		double max = 100.0;
		srand(1000);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				this->massive[i][j] = min + (double)(rand()) / (double)(RAND_MAX / (max - min));
				if (i == j)
				{
					this->massive[i][j] = size*max + (double)(rand()) / (double)(RAND_MAX / (size*max));
				}
			}
		}
	}

	Vector<T>& operator [](int index)
	{
		if (index > size)
		{
			throw exception("Выход за границу массива");
		}
		else
		{
			return this->massive[index];
		}
	}

	const Vector<T> operator *(Vector<T>& a)
	{
		Vector<T> vec(size);
		for (int i = 0; i < size; i++)
		{
			vec[i] = this->massive[i] * a;
		}
		return vec;
	}

	void show()
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; i < this->size; j++)
			{
				cout << this->massive[i][j];
			}
			cout << endl;
		}
	}

};

template<class T> ostream& operator <<(ostream& out, Vector<T>& vec)
{
	cout << "[";
	for (int i = 0; i < vec.Get_size() - 1; i++)
	{
		cout << vec[i] << " ";
	}
	cout << vec[vec.Get_size() - 1] << "]\n";
	return out;
};

template<class T> istream& operator >>(istream& in, Vector<T>& vec)
{
	for (int i = 0; i < vec.Get_size(); i++)
	{
		cout << "vec[" << i + 1 << "] =";
		cin >> vec[i];
	}
	return in;
};

template<class T> ostream& operator <<(ostream& out, Matrix<T>& mat)
{
	cout << fixed;
	for (int i = 0; i < mat.Get_size(); i++)
	{
		cout << "|";
		for (int j = 0; j < mat.Get_size(); j++)
		{
			cout.width(10);
			cout << setprecision(5)<< mat[i][j] << " ";
		}
		cout << "|";
		cout.width(10);
		cout << setprecision(5)<<"\n";
	}
	cout << "\n\n";
	return out;
};

template<class T> istream& operator >>(istream& in, Matrix<T>& mat)
{
	for (int i = 0; i < mat.Get_size(); i++)
	{
		for (int j = 0; j < mat.Get_size(); j++)
		{
			cout << "mat[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> mat[i][j];
		}
	}
	return in;
};

class SLAU
{
private:
	int size;
	Matrix<double> mat;
	Vector<double> vec;
	Vector<double> res;
public:
	SLAU(int size, bool random) : mat(size), vec(size), res(size)
	{
		this->size = size;
		if (random)
		{
			mat.random(size);
			vec.random(size);
		}
		else
		{
			cin >> mat;
			cin >> vec;
		}
	}

	~SLAU()
	{}

	Vector<double>& solve()
	{
		Matrix<double> Mat(mat);
		Vector<double> Vec(vec);

		if (size <= 10)
		{
			cout << "Исходная матрица:\n";
			show();
			cout << "\n\n";
		}
		for (int j = 0; j < size; j++)
		{
			double k;
			int maxJ = j;
			for (int i = j + 1; i < size; i++)
			{
				if (abs(mat[maxJ][j]) < abs(mat[i][j]))
				{
					maxJ = i;
				}	
			}
			if (j != maxJ)
			{
				mat.swap(j, maxJ);
				vec.swap(j, maxJ);
			}
			if (mat[maxJ][j] == 0)
			{
				throw exception("Система несовместна");
			}
			for (int i = j + 1; i < size; i++)
			{
				if (mat[j][j] != 0)
				{
					k = mat[i][j] / mat[j][j];
				}
				else
				{
					throw exception("деление на 0");
				}
				mat[i] += mat[j] * (-k);
				vec[i] += vec[j] * (-k);
			}
		}
		for (int i = size - 1; i >= 0; i--)
		{
			double summ = 0;
			for (int j = i + 1; j < size; j++)
			{
				summ += mat[i][j] * res[j];
			}
			res[i] = (vec[i] - summ) / mat[i][i];
		}
		
		if (examination(Mat, Vec))
		{
			cout << "Всё верно\n" << endl;
		}	
		else
		{
			cout << "Ошибка!!!!!\n" << endl;
		}
		return res;
	}
	bool examination(Matrix<double>& Mat, Vector<double>& Vec)
	{
		Vector<double> exam = Mat * res;
		if (size <= 10)
		{
			cout << "Проверка:\n";
			cout << "B = " << exam;
		}
		for (int i = 0; i < size; i++)
		{
			if (abs(exam[i] - Vec[i]) >= 0.0000000001)
			{
				return false;
			}
		}
		return true;
	}
	void show()
	{
		cout << fixed;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout.width(10);
				cout << setprecision(5)
					<< mat[i][j] << ' ';
			}
			cout << "|";
			cout.width(10);
			cout << setprecision(5)
				<< vec[i] <<"\n";
		}
	}
};


int main()
{
	int size;
	setlocale(LC_ALL, "Russian");
	bool Random;

	cout << "Введите n, где nxn размерность матрицы: " << endl;
	cin >> size;
	cout << "Если Вы хотите автоматически заполнить матрицу - введите 1, самостоятельный ввод - введите 0" << endl;
	cin >> Random;
	cout << endl;

	SLAU Gauss(size, Random);

	try
	{
		cout << "X = " << Gauss.solve() << endl;
	}
	catch (exception& ex)
	{
		cout << "Ошибка: " << ex.what();
	}
	cout << endl;
	return 0;
}
