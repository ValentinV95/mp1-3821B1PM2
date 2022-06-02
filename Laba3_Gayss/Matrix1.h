#pragma once
#include "ClassVector.h"
#include <stdio.h>      
#include <time.h>
#include<iomanip>
template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix(size_t stolb, const Vector<T>& stroka) : Vector<Vector<T>>(stolb, stroka) {}

	const Vector<T> operator * (Vector<T>& other)
	{
		Vector<T> res(this->size);
		for (int i = 0; i < this->size; i++)
		{
			res[i] = this->mas[i] * other;
		}
		return res;
	}
};

class Gauss {
private:
	size_t size;
	Matrix<double> mat;
	Vector<double> vec;
	Vector<double> res;
public:
	Gauss(size_t stolb, const Vector<double>& stroka) : mat(stolb, stroka), vec(stolb), res(stolb)
	{
		this->size = stolb;
	}

	size_t GetSize() { return size; }

	Vector<double>& Solve()
	{
		Matrix<double> matCopy(mat);
		Vector<double> vecCopy(vec);

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
				swap(mat[j], mat[maxJ]);
				swap(mat[j], mat[maxJ]);
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
				mat[i] -= mat[j] * k;
				vec[i] -= vec[j] * k;
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

		if (examination(matCopy, vecCopy))
		{
			cout << "Решено!\n" << endl;
		}
		else
		{
			cout << "Решено с ошибкой!\n" << endl;
		}
		return res;
	}
	bool examination(Matrix<double>& Mat, Vector<double>& Vec)
	{
		Vector<double> exam = Mat * res;
		for (int i = 0; i < size; i++)
		{
			if (abs(exam[i] - Vec[i]) >= 0.0000000001)
			{
				return false;
			}
		}
		return true;
	}
	void random()
	{
		double low = -5.0;
		double max = 5.0;

		srand(static_cast <unsigned> (time(0)));

		for (int i = 0; i < size; i++)
		{
			vec[i] = low + ((double)(rand()) / ((double)(RAND_MAX / (max - low))));
			for (int j = 0; j < size; j++)
			{
				mat[i][j] = low + ((double)(rand()) / ((double)(RAND_MAX / (max - low))));
				if (i == j)
					mat[i][j] = size * max + ((double)(rand()) / ((double)(RAND_MAX / (size * max))));
			}
		}
	}
	friend ostream& operator << (ostream& out, Gauss& system);
	friend istream& operator >> (istream& in, Gauss& system);
};
ostream& operator << (ostream& out, Gauss& system)
{
	cout << std::fixed;
	for (int i = 0; i < system.GetSize(); i++)
	{
		cout << "|";
		for (int j = 0; j < system.GetSize(); j++)
		{
			cout.width(10);
			cout << std::setprecision(5)
				<< system.mat[i][j] << ' ';
		}
		cout << " |";
		cout.width(10);
		cout << std::setprecision(5)
			<< system.vec[i] << "  |" << '\n';
	}
	cout << "\n\n";
	return out;
}
istream& operator >> (istream& in, Gauss& system)
{
	for (int i = 0; i < system.GetSize(); i++)
	{
		for (int j = 0; j < system.GetSize(); j++)
		{
			cout << "mat[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> system.mat[i][j];
		}
	}
	for (int i = 0; i < system.size; i++)
	{
		cout << "vec[" << i + 1 << "] = ";
		cin >> system.vec[i];
	}
	return in;
}



