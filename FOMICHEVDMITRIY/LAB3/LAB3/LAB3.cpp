#include <iostream>
#include <cmath>
#include <ctime>

template <typename T>
T module(T one)
{
	if (one >= 0)
	{
		return one;
	}

	else
	{
		return -one;
	}
}

template <class T> class vector
{
private:
	int size;
	T* data = nullptr;
	int count = 0;
public:
	vector()
	{}

	vector(int _size): size(_size)
	{
		data = new T[size];
	}

	vector(const vector& other)
	{
		this->size = other.size;

		this->data = new T[this->size];

		for (int i = 0; i < this->size; i++)
			this->data[i] = other.data[i];
	}

    T& operator [] (int i)
	{
		return data[i];
	}

	const vector& operator = (const vector& other)
	{
		if (this != &other)
		{
			delete[] this->data;
			this->size = other.size;

			this->data = new T[this->size];

			for (int i = 0; i < this->size; i++)
				this->data[i] = other.data[i];
		}

		return *this;
	}

	vector operator * (T num) const
	{
		vector other(*this);

		for (int i = 0; i < other.size; i++)
			other.data[i] *= num;

		return other;
	}

	vector operator / (T num) const
	{
		vector other(*this);

		for (int i = 0; i < other.size; i++)
		{
			if (module<T>(num) < 0.000001)
				throw "ДЕЛЕНИЕ НА НОЛЬ!\n";
			else
				other.data[i] /= num;
		}

		return other;
	}

	vector& operator += (const vector& other)
	{
		for (int i = 0; i < this->size; i++)
			this->data[i] += other.data[i];

		return *this;
	}

	vector& operator -= (const vector& other)
	{
		for (int i = 0; i < this->size; i++)
			this->data[i] -= other.data[i];

		return *this;
	}

	T at(int i)
	{
		if ((-1 < i) && (i < size))
			return data[i];

		else
			throw "\n\nВЫХОД ЗА ПРЕДЕЛЫ МАССИВА ВЕКТОРА\n\n";
	}

	void set_vector()
	{
		data = new T[size];

		for (int i = 0; i < size; i++)
		{
			std::cout << "Enter vector's " << i + 1 << " element: ";
			std::cin >> data[i];
		}
	}

	void zero_vector(int _size)
	{
		size = _size;

		data = new T[size];

		for (int i = 0; i < size; i++)
			data[i] = static_cast<T>(0);
	}

	void get_vector()
	{
		std::cout << "Vector: ";

		for (int i = 0; i < size; i++)
			std::cout << data[i] << " ";

		std::cout << "\n";
		std::cout << std::endl;
	}

	const int get_size()
	{
		return this->size;
	}

	~vector()
	{
		delete[] data;
		data = nullptr;
		size = 0;
	}
};

template <class T>
vector<T> operator * (T num, const vector<T>& other)
{
	vector<T> third(other);

	for (int i = 0; i < third.get_size(); i++)
		third[i] *= num;

	return third;
}

template <typename T>
class matrix : public vector<vector<T>>
{
private:
	int row;
	T** matrix_data = nullptr;
public:
	matrix()
	{}

	matrix(int _size): row(_size)
	{
		matrix_data = new T * [row];

		for (int i = 0; i < row; i++)
			matrix_data[i] = new T[row];
	}

	matrix(const matrix& other)
	{
		this->row = other.row;

		this->matrix_data = new T*[this->row];

		for (int i = 0; i < this->row; i++)
		{
			this->matrix_data[i] = new T[this->row];

			for (int j = 0; j < this->row; j++)
				this->matrix_data[i][j] = other.matrix_data[i][j];
		}
	}

	T* operator [](int i)
	{
			return matrix_data[i];
	}

	void set_matrix()
	{
		for (int i = 0; i < row; i++)
		{
			matrix_data[i] = new T[row];

			for (int j = 0; j < row; j++)
			{
				std::cout << "Enter element of " << i + 1 << " row and " << j + 1 << " column: ";
				std::cin >> matrix_data[i][j];
			}
		}
	}

	void get_matrix()
	{
		std::cout << "Matrix:\n";
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
				std::cout << " " << matrix_data[i][j] << " ";

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	const int get_row()
	{
		return row;
	}

	T at(int i, int j)
	{
		if (((-1 < i) && (i < row)) && ((-1 < j) && (j < row)))
			return matrix_data[i][j];

		else
			throw "\n\nВЫХОД ЗА ПРЕДЕЛЫ МАССИВА МАТРИЦЫ\n\n";
	}

	~matrix()
	{
		for (int i = 0; i < row; i++)
			delete[] matrix_data[i];

		delete[] matrix_data;

		matrix_data = nullptr;
		row = 0;
	}
};

template <class T>
void swap(T* one, T* other)
{
	T temp;

	temp = *one;
	*one = *other;
	*other = temp;
}

template <class T>
void swap(vector<T>* one, vector<T>* other)
{
	vector<T> temp;

	temp = *one;
	*one = *other;
	*other = temp;
}

template <class T>
int compare(vector<T>* array, int array_size, int row_number)
{
	int max_element_number = row_number;
	T max = array[row_number][row_number];

	for (int i = row_number; i < array_size; i++)
	{
		if (module<T>(max) < module<T>(array[i][row_number]))
		{
			max = array[i][row_number];
			max_element_number = i;
		}
	}

	return max_element_number;
}

template <class T>
void random_matrix(matrix<T>& one, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			one[i][j] = static_cast<T>(-1000) + rand() % 3000;
	}
}

template <class T>
void random_vector(vector<T>& one, int size)
{
	for (int i = 0; i < size; i++)
		one[i] = static_cast<T>(-1000) + rand() % 3000;
}

template<class T>
vector<T> check(matrix<T>& A, vector<T>& x, vector<T>& b)
{
	int size = A.get_row();
	vector<T> error(size);
	T temp = static_cast<T>(0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			temp += A[i][j] * x[j];

		error[i] = module<T>(b[i] - temp);
		temp = 0;
	}

	return error;
}

template <class T>
void compare(vector<T>& x, int size,T* max, T* min, T* avg)
{
	*max = static_cast<T>(0);
	*min = x[0];
	*avg = static_cast<T>(0);

	for (int i = 0; i < size; i++)
	{
		if (*max <= x[i])
			*max = x[i];

		if (x[i] <= *min)
			*min = x[i];

		*avg += x[i];
	}

	*avg /= size;
}

template <class T>
class SLAU : public matrix<T>
{
private:
	matrix<T> A;
	vector<T> b;
	vector<T> x;
	vector<T> error;
	int info = 0;
public:
	SLAU(const matrix<T>& _A, const vector<T>& _b): A(_A), b(_b)
	{
			x = GAUSS(A, b);
			error = check(A, x, b);
	}

	void get_SLAU()
	{
		int choice = 1;

		if (A.get_row() > 20)
		{
			std::cout << "\nКоличество элементов в расширенной матрице слишком большое.\nЧтобы увидеть матрицу нажмите - 1. Чтобы пропустить - любую цифру.\n";
			std::cout << "Ваш выбор: ";
			std::cin >> choice;
		}

		if (choice == 1)
		{
			std::cout << std::endl;
			for (int i = 0; i < A.get_row(); i++)
			{
				for (int j = 0; j < A.get_row(); j++)
					std::cout << " " << A.at(i, j);

				std::cout << " | " << b.at(i) << std::endl;
			}
		}

		if (info == 0)
		{
			if (A.get_row() > 20)
			{
				std::cout << "\nКоличество элементов в векторе решений слишком большое.\nЧтобы увидеть вектор нажмите - 1. Чтобы пропустить - любую цифру.\n";
				std::cout << "Ваш выбор: ";
				std::cin >> choice;
			}

			if (choice == 1)
			{
				std::cout << std::endl << "Вектор решений = ";
				x.get_vector();
			}

			if (A.get_row() > 20)
			{
				std::cout << "\nКоличество элементов в векторе погрешностей слишком большое.\nЧтобы увидеть вектор нажмите - 1. Чтобы пропустить - любую цифру.\n";
				std::cout << "Ваш выбор: ";
				std::cin >> choice;
			}

			if (choice == 1)
			{
				std::cout << std::endl << "Вектор погрешностей = ";
				error.get_vector();
			}

			T max, min, avg;

			compare<T>(error, error.get_size(), &max, &min, &avg);

			std::cout << "\nСамая большая погрешность: " << max << "; Самая маленькая погрешность: " << min << "; Средняя погрешность: " << avg << ";\n";
			std::cout << std::endl;
		}

		else
		{
			std::cout << "\n\nБольше одного решения или система неопределенная\n\n";
			info = 0;
		}
	}

	vector<T> GAUSS(matrix<T>& A, vector<T> b)
	{
		int size = A.get_row();
		vector<T>* vectors;

		vectors = new vector<T>[size];

		for (int i = 0; i < size; i++)
		{
			vectors[i].zero_vector(size + 1);

			for (int j = 0; j < size + 1; j++)
			{
				if (j == size)
					vectors[i][j] = b.at(i);
				else
					vectors[i][j] = A.at(i, j);
			}
		}

		int max;

		for (int j = 0; j < size - 1; j++)
		{
			if (module<T>(vectors[j][j]) < 0.000001)
				vectors[j][j] = static_cast<T>(0);

			max = compare(vectors, size, j);
			swap<T>(&vectors[max], &vectors[j]);
			max = j;

			for (int i = 1 + j; i < size; i++)
			{
				if (vectors[i][j] > 0)
					vectors[i] -= vectors[i][j] * vectors[max] / vectors[max][j];

				if (vectors[i][j] < 0)
					vectors[i] += static_cast<T>(-1) * vectors[i][j] * vectors[max] / vectors[max][j];
			}
		}

		vector<T> X;
		X.zero_vector(size);

		if (round(vectors[size - 1][size - 1]) == 0)
			info = 1;

		else
		{
			X[size - 1] = vectors[size - 1][size] / vectors[size - 1][size - 1];

			for (int i = size - 2; i > -1; i--)
			{
				T temp = static_cast<T>(0);

				for (int j = 0; j < size; j++)
					temp += X[j] * vectors[i][j];

				if (vectors[i][i] == 0)
				{
					info = 1;
					break;
				}

				else
					X[i] = (vectors[i][size] - temp) / vectors[i][i];
			}
		}

		delete[] vectors;
		vectors = nullptr;

		return X;
	}
};

void menu()
{
	int choice;
	int x;

	while (1)
	{
		std::cout << "Выберите тип генерации коэффициентов СЛАУ:\n";
		std::cout << "1) Ручной ввод.\n2) Случайная генерация.\n";
		std::cout << "Ваш выбор: ";
		std::cin >> choice;
		std::cout << std::endl;
		std::cout << "Введите количество неизвестных в СЛАУ: ";
		std::cin >> x;

		if (x <= 0)
			throw "\nКОЛИЧЕСТВО НЕИЗВЕСТНЫХ В СЛАУ НЕ МОЖЕТ БЫТЬ 0 ИЛИ ОТРИЦАТЕЛЬНЫМ ЧИСЛОМ!\n";

		std::cout << std::endl;

		switch (choice)
		{
		case 1:
		{
			vector<double> b(x);
			matrix<double> A(x);
			A.set_matrix();
			b.set_vector();
			SLAU<double>first(A, b);
			first.get_SLAU();
			break;
		}
		case 2:
		{
			vector<double> b(x);
			matrix<double> A(x);
			random_matrix<double>(A, x);
			random_vector<double>(b, x);
			SLAU<double>first(A, b);
			first.get_SLAU();
			break;
		}
		default:
		{
			std::cout << "Такого функционала не существует. Повторите попытку!\n\n";
			break;
		}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	try
	{
		menu();
	}

	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		abort;
	}

	return 0;
}