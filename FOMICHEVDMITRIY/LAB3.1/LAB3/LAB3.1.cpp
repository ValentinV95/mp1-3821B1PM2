#include <iostream>
#include <cmath>
#include <ctime>
#define epsilon 0.000001

//Класс вектор
template <class T> class vector
{
protected:
	int size;
	T* data = nullptr;
public:
	vector(int _size = 1): size(_size)
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
			if (abs(num) < epsilon)
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

	T& at(int i)
	{
		if ((-1 < i) && (i < size))
			return data[i];

		else
			throw "\n\nВЫХОД ЗА ПРЕДЕЛЫ МАССИВА ВЕКТОРА\n\n";
	}

	void resize(int new_size)
	{
		delete[] data;
		size = new_size;
		data = new T[size];
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

// Умножение числа на вектор 
template <class T>
vector<T> operator * (T num, const vector<T>& other)
{
	vector<T> third(other);

	for (int i = 0; i < third.get_size(); i++)
		third[i] *= num;

	return third;
}

// Класс матрица
template <typename T>
class matrix : public vector<vector<T>>
{
public:
	matrix(int _size = 1) : vector<vector<T>>(_size)
	{
		for (int i = 0; i < _size; i++)
			this->data[i].resize(_size);
	}

	matrix(matrix& other) : vector<vector<T>>(other.get_size())
	{
		for (int i = 0; i < this->size; i++)
			this->data[i] = other[i];
	}

	void set_matrix()
	{
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
			{
				std::cout << "Enter element of " << i + 1 << " row and " << j + 1 << " column: ";
				std::cin >> this->data[i][j];
			}
	}

	void get_matrix()
	{
		std::cout << "Matrix:\n";
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
				std::cout << " " << this->data[i][j] << " ";

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	T& at(int i, int j)
	{
		if (((-1 < i) && (i < this->size)) && ((-1 < j) && (j < this->size)))
			return this->data[i][j];

		else
			throw "\n\nВЫХОД ЗА ПРЕДЕЛЫ МАССИВА МАТРИЦЫ\n\n";
	}

	vector<T>& operator [] (int i)
	{
		return this->data[i];
	}

};

// Меняет местами два вектора
template <class T>
void swap(vector<T>* one, vector<T>* other)
{
	vector<T> temp;

	temp = *one;
	*one = *other;
	*other = temp;
}

// Меняет местами два числа
template <class T>
void swap(T* one, T* other)
{
	T temp;

	temp = *one;
	*one = *other;
	*other = temp;
}

// Сравнивает элементы из фиксированного столбца и возвращает номер самого большого
template <class T>
int compare(matrix<T>& array, int column_number)
{
	int max_element_number = column_number;
	T max = array[column_number][column_number];

	for (int i = column_number; i < array.get_size(); i++)
	{
		if (abs(max) < abs(array[i][column_number]))
		{
			max = array[i][column_number];
			max_element_number = i;
		}
	}

	return max_element_number;
}

// Создание матрицы случайных значений
template <class T>
void random_matrix(matrix<T>& one, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			one[i][j] = static_cast<T>(-1000) + rand() % 3000;
	}
}

// Создание вектора случайных значений
template <class T>
void random_vector(vector<T>& one, int size)
{
	for (int i = 0; i < size; i++)
		one[i] = static_cast<T>(-1000) + rand() % 3000;
}

// Вычисление погрешности вычислений
template<class T>
vector<T> check(matrix<T>& A, vector<T>& x, vector<T>& b)
{
	int size = A.get_size();
	vector<T> error(size);
	T temp = static_cast<T>(0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			temp += A[i][j] * x[j];

		error[i] = abs(b[i] - temp);
		temp = 0;
	}

	return error;
}

// Сравнение погрешностей и вывод информации о них
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

// Класс СЛАУ
template <class T>
class SLAU
{
private:
	int size;
	matrix<T> A;
	vector<T> b;
	vector<T> x;
	vector<T> error;
public:
	SLAU(int _size, int status): size(_size), A(size), b(size)
	{
        if(status == 1)
		{
			A.set_matrix();
			b.set_vector();
		}

		else
		{
			random_matrix<T>(A, size);
			random_vector<T>(b, size);
		}

		x = GAUSS(A, b);
		error = check(A, x, b);
	}

	void get_SLAU()
	{
		int choice = 1;

		if (size > 20)
		{
			std::cout << "\nКоличество элементов в расширенной матрице слишком большое.\nЧтобы увидеть матрицу нажмите - 1. Чтобы пропустить - любую цифру.\n";
			std::cout << "Ваш выбор: ";
			std::cin >> choice;
		}

		if (choice == 1)
		{
			std::cout << std::endl;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
					std::cout << " " << A.at(i, j);

				std::cout << " | " << b.at(i) << std::endl;
			}
		}

		if (size > 20)
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

		if (size > 20)
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

		std::cout << "\n\nСамая большая погрешность: " << max << "; Самая маленькая погрешность: " << min << "; Средняя погрешность: " << avg << ";\n\n";
		std::cout << std::endl;
	}

	vector<T> GAUSS(matrix<T>& A, vector<T>& b)
	{
		int max;
		matrix<T> temp_matrix(A);
		vector<T> temp_vector(b);

		for (int j = 0; j < size - 1; j++)
		{
			if (abs(temp_matrix[j][j]) < epsilon)
				temp_matrix[j][j] = static_cast<T>(0);

			max = compare(temp_matrix, j);
			swap<T>(&temp_matrix[max], &temp_matrix[j]);
			swap<T>(&temp_vector[max], &temp_vector[j]);
			max = j;

			for (int i = 1 + j; i < size; i++)
			{
				if (temp_matrix[i][j] > 0)
				{
					if (abs(temp_matrix[max][j]) < epsilon)
						throw("Деление на ноль");
					else
						temp_vector[i] -= temp_matrix[i][j] * temp_vector[max] / temp_matrix[max][j];

					temp_matrix[i] -= temp_matrix[i][j] * temp_matrix[max] / temp_matrix[max][j];
				}

				if (temp_matrix[i][j] < 0)
				{
					if (abs(temp_matrix[max][j]) < epsilon)
						throw("Деление на ноль");
					else
						temp_vector[i] += static_cast<T>(-1) * temp_matrix[i][j] * temp_vector[max] / temp_matrix[max][j];
					temp_matrix[i] += static_cast<T>(-1) * temp_matrix[i][j] * temp_matrix[max] / temp_matrix[max][j];
				}
			}
		}

		vector<T> X;
		X.zero_vector(size);

		if (abs(temp_matrix[size - 1][size - 1]) < epsilon)
			throw("\n\nБольше одного решения или система неопределенная\n\n");

		else
		{
			X[size - 1] = temp_vector[size - 1] / temp_matrix[size - 1][size - 1];

			for (int i = size - 2; i > -1; i--)
			{
				T temp = static_cast<T>(0);

				for (int j = 0; j < size; j++)
					temp += X[j] * temp_matrix[i][j];

				if (abs(temp_matrix[i][i]) < epsilon)
				{
					throw("\n\nБольше одного решения или система неопределенная\n\n");
				}

				else
					X[i] = (temp_vector[i] - temp) / temp_matrix[i][i];
			}
		}

		return X;
	}
};

// Меню
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
			SLAU<double> first(x, choice);
			first.get_SLAU();
			break;
		}
		case 2:
		{
			SLAU<double>first(x, choice);
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
		exit(-1);
	}
	return 0;
}