#include <iostream> 
#include <clocale> 
#include <ctime> 
#include <cmath> 

using namespace std;
#define EPSILON 0.0000000001

template<typename T>
class myVector
{
protected:
	T* arr;
	int size;
public:
	myVector(int in = 1)
	{
		if (in < 0)
		{
			throw "Создание массива с отрицательным размером";
		}
		size = in;
		arr = new T[size];
	}
	myVector(const myVector<T>& a)
	{
		this->size = a.size;
		this->arr = new T[a.size];
		for (int i = 0; i < a.size; i++)
		{
			this->arr[i] = a.arr[i];
		}
	}
	void resize(int r)
	{
		size = r;
		delete[] arr;
		arr = new T[r];
	}
	void arr_random(int d)
	{
		for (int i = 0; i < this->size; i++)
		{
			arr[i] = rand() % 101;;
		}
	}
	myVector<T>& operator = (const myVector<T>& a)
	{
		resize(a.size);
		for (int i = 0; i < a.size; i++)
		{
			this->arr[i] = a.arr[i];
		}
		return *this;
	}
	T& operator[](int t)
	{
		if (t >= this->size)
		{
			throw "Индекс массива выходит за пределы";
		}
		return this->arr[t];
	}
	~myVector()
	{
		delete[] arr;
	}
};
template<typename T>
class myMatrix : public myVector<myVector<T>>
{
public:
	myMatrix(int n = 1) : myVector<myVector<T>>(n)
	{
		for (int i = 0; i < n; i++)
		{
			this->arr[i].resize(n);
		}
	}
	myVector<T>& operator[](int m)
	{
		if (m >= this->size)
		{
			throw "Индекс массива выходит за пределы";
		}
		return this->arr[m];
	}
};
template<typename T>
class SLAU : public myMatrix<T>
{
private:
	void create_copy(myMatrix<T>& copy)
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				copy[i][j] = this->arr[i][j];
			}
		}
	}
	void check(myMatrix<T>& A, myVector<T>& b, myVector<T>& x)
	{
		cout << "\nПроверка правильности решения:\n" << endl;
		bool solution_correct = true;
		T _x;
		for (int i = 0; i < this->size; i++)
		{
			_x = 0;
			for (int j = 0; j < this->size; j++)
			{
				_x += x[j] * A[i][j];
			}
			if (fabs(b[i] - _x) > EPSILON)
			{
				cout << "Решение неверно" << endl;
				solution_correct = false;
				break;
			}
		}
		if (solution_correct)
		{
			cout << "Решение правильное" << endl;
		}
	}
public:
	SLAU(int slau_size = 1) : myMatrix<T>(slau_size)
	{}
	void solve(myVector<T>& b)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->arr[i][i] == 0)
			{
				cout << "Система не имеет решения или имеет более одного решения" << endl;
				return;
			}
		}
		int max_j;
		myMatrix<T> A_copy(this->size);
		create_copy(A_copy);
		myVector<T> b_copy(b);
		myVector<T> x(this->size);
		for (int i = 0; i < this->size; i++)
		{
			max_j = i;
			for (int j = i + 1; j < this->size; j++)
			{
				if (fabs(this->arr[max_j][i]) < fabs(this->arr[j][i]))
				{
					max_j = j;
				}
			}
			if (i != max_j)
			{
				myVector<T> tmp_vector;
				tmp_vector = this->arr[i];
				this->arr[i] = this->arr[max_j];
				this->arr[max_j] = tmp_vector;
				T tmp = b[i];
				b[i] = b[max_j];
				b[max_j] = tmp;
			}
			for (int j = i; j < this->size; j++)
			{
				for (int i_tmp = this->size; i_tmp > i - 1; i_tmp--)
				{
					if (this->arr[j][i] == 0)
					{
						throw "\nОшибка нулевого деления";
					}
					else
					{
						if (i_tmp == this->size)
						{
							b[j] /= this->arr[j][i];
						}
						else
						{
							this->arr[j][i_tmp] /= this->arr[j][i];
						}
					}
				}
			}
			if (i < this->size - 1)
			{
				for (int j = i + 1; j < this->size; j++)
				{
					for (int i_tmp = i; i_tmp < this->size + 1; i_tmp++)
					{
						if (i_tmp == this->size)
						{
							b[j] -= b[i];
						}
						else
						{
							this->arr[j][i_tmp] -= this->arr[i][i_tmp];
						}
					}
				}
			}
		}
		int z;
		bool s = true;
		cout << "\nОтвет:\n" << endl;
		for (int j = 0; j < this->size; j++)
		{
			z = 0;
			for (int i = 0; i < this->size; i++)
			{
				if (this->arr[j][i] == 0)
				{
					z++;
				}
			}
			if (z == this->size && b[j] != 0)
			{
				cout << "\nНет решений" << endl;
				return;
			}
			else if (z == this->size && b[j] == 0)
			{
				s = false;
			}
		}
		if (s)
		{
			x[this->size - 1] = b[this->size - 1];
			for (int j_x = (this->size - 2); j_x > -1; j_x--)
			{
				for (int i_x = j_x + 1; i_x < this->size; i_x++)
				{
					b[j_x] -= (this->arr[j_x][i_x] * x[i_x]);
				}
				x[j_x] = b[j_x];
			}
			for (int i = 0; i < this->size; i++)
			{
				cout << "x" << i + 1 << " = " << x[i] << endl;
			}
			check(A_copy, b_copy, x);
		}
		else
		{
			cout << "\nБесконечно много решений" << endl;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(static_cast<unsigned>(time(0)));
	int select;
	cout << "Размер матрицы: ";
	cin >> select;
	int sel;
	cout << "Выбор метода заполнения для матрицы A и вектора b: \n\n 1 - Случайное заполнение \n 2 - Ручное заполнение \n\n";
	cin >> sel;
	bool arr_random = true;
	if (sel == 2)
	{
		arr_random = false;
	}
	else if (sel != 1 && sel != 2)
	{
		cout << "Недопустимый номер способа заполнения" << endl;
		exit(0);
	}
	try
	{
		SLAU<double> A(select);
		myVector<double> b(select);
		if (arr_random)
		{
			for (int i = 0; i < select; i++)
			{
				A[i].arr_random(i);
			}
			b.arr_random(select);
		}
		else
		{
			for (int i = 0; i < select; i++)
			{
				for (int j = 0; j < select; j++)
				{
					cout << "A(" << i + 1 << ',' << j + 1 << "): ";
					cin >> A[i][j];
				}
			}
			for (int i = 0; i < select; i++)
			{
				cout << "b(" << i + 1 << "): ";
				cin >> b[i];
			}
		}
		for (int i = 0; i < select; i++)
		{
			for (int j = 0; j < select + 1; j++)
			{
				if (j != select)
				{
					cout << A[i][j] << "  ";
				}
				else
				{
					cout << "| " << b[i];
				}
			}
			cout << "\n" << endl;
		}
		A.solve(b);
	}
	catch (const char* exception)
	{
		cout << exception << endl;
	}
	return 0;
}