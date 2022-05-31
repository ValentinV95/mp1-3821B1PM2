#include <iostream>
#include <locale.h>
template <typename T>
void swap(T& vec1, T& vec2)
{
	T temp = vec1;
	vec1 = vec2;
	vec2 = temp;
}
template<typename T>
class Vector
{
protected:
	int size;
	T* mas;
public:
	Vector() :Vector(0)
	{

	}
	Vector(int size)
	{
		this->size = size;
		this->mas = new T[size];
	}
	Vector(int size, T val)
	{
		this->size = size;
		mas = new T[size];
		for (int i = 0; i < size; i++)
		{
			mas[i] = val;
		}
	}
	Vector(const Vector& other_vect)
	{
		this->size = other_vect.size;
		this->mas = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->mas[i] = other_vect.mas[i];
		}
	}
	~Vector()
	{
		delete[]mas;
	}
	T& GetMas()
	{
		return *this->mas;
	}
	Vector& operator=(const Vector& other_vect)
	{
		if (this->size == other_vect.size)
		{
			for (int i = 0; i < size; i++)
			{
				this->mas[i] = other_vect.mas[i];
			}
		}
		else
		{
			delete[] this->mas;
			this->size = other_vect.size;
			this->mas = new T[other_vect.size];
			for (int i = 0; i < other_vect.size; i++)
			{
				this->mas[i] = other_vect.mas[i];
			}
		}
		return *this;
	}
	bool operator== (const Vector& other_vect)
	{
		bool flag = true;
		if (this->size != other_vect.size)
		{
			flag = false;
			return flag;
		}
		else
		{
			for (int i = 0; i < other_vect.size; i++)
			{
				if (this->mas[i] != other_vect.mas[i])
				{
					flag = false;
					return flag;
				}
			}
			return flag;
		}
	}
	Vector operator+ (const Vector& other_vect)
	{
		Vector temp(other_vect.size);
		for (int i = 0; i < other_vect.size; i++)
		{
			temp.mas[i] = mas[i] + other_vect.mas[i];
		}
		return temp;
	}
	Vector operator- (const Vector& other_vect)
	{
		Vector temp(other_vect.size);
		for (int i = 0; i < other_vect.size; i++)
		{
			temp.mas[i] = mas[i] - other_vect.mas[i];
		}
		return temp;
	}
	Vector operator* (const T& scalar)
	{
		Vector temp(this->size);
		for (int i = 0; i < this->size; i++)
		{
			temp.mas[i] = mas[i] * scalar;
		}
		return temp;
	}
	Vector operator/ (const T& scalar)
	{
		if (scalar != 0)
		{
			Vector temp(this->size);
			for (int i = 0; i < this->size; i++)
			{
				temp.mas[i] = mas[i] / scalar;
			}
			return temp;
		}
		else
		{
			throw std::exception("Деление на ноль");
		}
	}
	T& operator [](int i)
	{
		return(mas[i]);
	}
	friend::std::istream& operator>> (std::istream& ist, const Vector& mas)
	{
		for (int i = 0; i < mas.size; i++)
		{
			ist >> mas.mas[i];
		}
		return ist;
	}
	friend::std::ostream& operator<< (std::ostream& ost, const Vector& mas)
	{
		for (int i = 0; i < mas.size; i++)
		{
			std::cout << "x" << (i + 1) << " = ";
			ost << mas.mas[i] << "\n";
		}
		ost << std::endl;
		return ost;
	}
	Vector operator*(const Vector& other_vect) const
	{
		if (size == mas.size)
		{
			double res = 0;
			for (int i = 0; i < size; i++)
			{
				res += mas[i] * other_vect.GetMas(i);
			}
			return res;
		}
		else
		{
			throw std::exception("Длины векторов не совпадают");
		}
	}
};
template <typename T>
class Matrix : public Vector<Vector<T>>
{
public:
	Matrix(int size, const Vector<T>& vectr) : Vector<Vector<T>>(size, vectr)
	{

	}
};
template <typename T>
class SLAU :public Matrix<T>
{
public:
	SLAU(int size, const Vector<T>& vectr) : Matrix<T>(size, vectr) {}

	Vector<T> GaussMethod()
	{
		int size = this->size;
		Vector<T> answer(size, 0);
		Vector<T> array(size, 0);
		int max;
		int counter = 0;
		for (int i = 0; i < size; i++)
		{
			max = i;
			for (int j = i + 1; j < size; j++)
			{
				if ((*this)[i][j] * (*this)[i][j] > (*this)[i][max] * (*this)[i][max])
				{
					max = j;
				}
			}
			if (i != max)
			{
				swap <Vector<T>>((*this)[i], (*this)[max]);
			}
			counter = 0;
			if ((*this)[i][i] != 0)
			{
				(*this)[i] = (*this)[i] / (*this)[i][i];
				for (int j = i + 1; j < size; j++)
				{
					(*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i]);
				}
				for (int j = 0; j < i; j++)
				{
					(*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i]);
				}
			}
			else
			{
				std::cout << "На диагонали присутствует 0, значит решение не единственное." << std::endl;
			}
		}
		counter = 0;
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = size - 1; j >= 0; j--)
			{
				if ((*this)[i][j] == 0)
				{
					counter++;
				}
			}
			if (counter == size && (*this)[i][size] != 0)
			{
				std::cout << "Несовместная система уравнений" << std::endl;
				exit(0);
			}
			counter = 0;
			break;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = size - 1; j >= 0; j--)
			{
				if ((*this)[i][j] == 1)
				{
					answer[j] = (*this)[j][size];
				}
			}
		}
		T* P;
		P = new T[size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				P[i] = (*this)[i][j] * answer[j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			if (abs(P[i] - array[i]) < 0.000000000001)
			{
				std::cout << "Проверка прошла успешно" << std::endl;
				return answer;
				break;
			}
			else
			{
				std::cout << (*this);
				std::cout << "Проверка не прошла" << std::endl;
				return answer;
				break;
			}
		}
		delete[] P;
	}
};
int main()
{
	int size;
	int choose = 0;
	enum { enter = 1, random };
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите размер матрицы - ";
	std::cin >> size;
	std::cout << std::endl;
	Vector<double> vectr(size + 1);
	SLAU<double> slau(size, vectr);
	SLAU<double> array(size, vectr);
	std::cout << "Выберите метод:\n1. Числа вводятся с клавиатуры\n2. Рандомные числа\n" << std::endl;
	std::cin >> choose;
	switch (choose)
	{
	case(enter):
		std::cout << "Введите Сиситему Линейных Алгебраических Уравнений:\n" << std::endl;
		std::cout << "Вводите числа в строчку, затем нажмите 'enter', чтобы ввести следующую строчку\n" << std::endl;
		std::cin >> slau;
		break;
	case(random):
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size + 1; j++)
			{
				slau[i][j] = (rand() % 201 - 50);
				std::cout << " ";
				std::cout << slau[i][j];
			}
			std::cout << std::endl;
		}
		break;
	default:
		std::cout << "Неправильный выбор операции" << std::endl;
		break;
	}
	Vector<double> answer(size);
	array = slau;
	answer = slau.GaussMethod();
	std::cout << "Ответ:" << std::endl;
	try
	{
		std::cout << answer;
	}
	catch (std::exception& ex)
	{
		std::cout << "Ошибка: " << ex.what();
	}
	std::cout << std::endl;
	return (0);
}