#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

template <typename T>
class Vector
{
private:
	int size = 0;
public:
	T* array = NULL;

	Vector(int i = 1)
	{
		size = i;
		array = new T[size];
	}
	~Vector()
	{
		size = 0;
		delete[](array);
	}
	void resize(int _size)
	{
		T* tmp = new T[_size];
		if (array != NULL)
		{
			for (int i = 0; i < std::min(size, _size); i++)
			{
				tmp[i] = array[i];
			}
			delete[](array);
		}
		size = _size;
		array = tmp;
	}

	T& operator [](int index)
	{
		return array[index];
	}

	Vector<T>& operator = (Vector<T>& vector)
	{
		if (this != &vector)
		{
			if (array != NULL) delete[](array);
			size = vector.GetVectorSize();
			array = new T[size];
			for (int i = 0; i < size; i++)
			{
				array[i] = vector[i];
			}
		}
		return *this;
	}

	int GetVectorSize()
	{
		return size;
	}

	void SwapElem(int FirstId, int SecondId)
	{
		T tmp = array[FirstId];
		array[FirstId] = array[SecondId];
		array[SecondId] = tmp;
	}

	void ShowVector()
	{
		std::cout << "( ";
		for (int i = 0; i < size; i++)
		{
			std::cout << array[i] << " ";
		}
		std::cout << ")^T";
	}


	void SetVectorValue()
	{
		for (int i = 0; i < size; i++)
		{
			std::cin >> array[i];
		}
	}


	void GenerateRandomVector()
	{
		std::srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i < size; i++)
		{
			array[i] = static_cast<T>(std::rand() % 5 * 1.0 + (std::rand() % 1000 * 1.0 / 1000));
		}
	}
};

template<typename T>
class Matrix :public Vector< Vector<T> >
{
private:
	int ColumnSize, StringSize;
public:
	Matrix(int _ColumnSize = 1, int _StringSize = 1) :Vector< Vector<T> >(_ColumnSize)
	{
		ColumnSize = _ColumnSize;
		StringSize = _StringSize;
		for (int i = 0; i < ColumnSize; i++)
		{
			this->array[i].resize(_StringSize);
		}
	}

	~Matrix() {}

	int IndexMaxElemOnColumn(int ColumnNumber, int first = 0)
	{
		int MaxIndex = first;
		for (int i = first; i < ColumnSize; i++)
		{
			if (abs(this->array[i][ColumnNumber]) > abs(this->array[MaxIndex][ColumnNumber]))
			{
				MaxIndex = i;
			}
		}
		//std::cout << endl << "max index = " << MaxIndex << endl;
		return MaxIndex;
	}

	void SetElemOnColumn(int ColumnNumber, T elem, int first = 0)
	{
		for (int i = first; i < ColumnSize; i++)
		{
			this->array[i][ColumnNumber] = elem;
		}
	}

	Vector<T>& operator [](int index)
	{
		return this->array[index];
	}

	void SwapString(int FirstString, int SecondString)
	{
		Vector<T> Tmp(StringSize);
		Tmp = this->array[FirstString];
		this->array[FirstString] = this->array[SecondString];
		this->array[SecondString] = Tmp;
	}

	void ShowMartrix()
	{
		for (int i = 0; i < ColumnSize; i++)
		{
			std::cout << "| ";

			for (int j = 0; j < StringSize; j++)
			{
				std::cout << setiosflags(ios::left) << setw(9) << this->array[i][j];
			}
			std::cout << " |";
			std::cout << endl;
		}
	}

	void SetMatrixValue()
	{
		for (int i = 0; i < ColumnSize; i++)
		{
			for (int j = 0; j < StringSize; j++)
			{
				std::cin >> this->array[i][j];
			}
		}
	}

	void GenerateMatrixValue()
	{
		std::srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i < ColumnSize; i++)
		{
			for (int j = 0; j < StringSize; j++)
			{
				this->array[i][j] = static_cast<T>(std::rand() % 5 * 1.0 + (std::rand() % 100 * 1.0 / 100));
			}
		}
		for (int i = 0; i < std::min(ColumnSize, StringSize); i++)
		{
			this->array[i][i] += static_cast <T>(6.0 * StringSize);
		}
	}

	int GetColumnSize()
	{
		return ColumnSize;
	}
	int GetStringSize()
	{
		return StringSize;
	}
};


template<typename T>
class SLU
{
private:
	Matrix<T> matrix;
	Vector<T> vector;
	Vector<T> answer;
	T precision;         //чтобы при прямом ходе не возникали числа порядка 1e300 вместо 0 добавил переменную с точностью, всё что меньше неё по модулю будет считаться 0
	int _ShowIteration = 0;
public:
	SLU(Matrix<T>& _matrix, Vector<T>& _vector, T precision = 0.000001) : matrix(_matrix.GetColumnSize(), _matrix.GetStringSize()),
		vector(_vector.GetVectorSize()), answer(_matrix.GetStringSize())
	{
		this->precision = precision;
		for (int i = 0; i < _matrix.GetColumnSize(); i++)
		{
			for (int j = 0; j < _matrix.GetStringSize(); j++)
			{
				matrix[i][j] = _matrix[i][j];
			}
		}
		for (int i = 0; i < _vector.GetVectorSize(); i++)
		{
			vector[i] = _vector[i];
		}
		for (int i = 0; i < _matrix.GetStringSize(); i++)
		{
			answer[i] = 0;
		}

	}

	void Swap(int FirstString, int SecondString) //меняет строки в СЛУ
	{
		matrix.SwapString(FirstString, SecondString);
		vector.SwapElem(FirstString, SecondString);

	}

	void ShowIteration()
	{
		_ShowIteration = 1;
	}

	void DontShowIteration()
	{
		_ShowIteration = 0;
	}

	Vector<T>& GAUSS() // Прямой и обратный ход метода Гаусса
	{

		ForwardCourse();
		std::cout << endl; matrix.ShowMartrix(); vector.ShowVector(); std::cout << endl << endl;
		ReverseCourse();
		std::cout << endl << "Answer vector :" << endl; answer.ShowVector();
		return answer;
	}


	void ForwardCourse()
	{
		if (matrix.GetColumnSize() != vector.GetVectorSize())
		{
			throw exception("Matrix size Error!"); 
		}
		else
		{
			for (int StringNum = 0, ColumnNum = 0; StringNum < matrix.GetStringSize() && ColumnNum < matrix.GetColumnSize(); StringNum++)
			{

				if (_ShowIteration) { std::cout << endl; matrix.ShowMartrix(); vector.ShowVector(); std::cout << endl << endl; }

				int IndexOfMax = matrix.IndexMaxElemOnColumn(StringNum, ColumnNum);    // Находим индекс максимального элемента в столбце
				if (abs(matrix[IndexOfMax][StringNum]) <= precision)                   // Если максимальный элемен оказался 0 (меньше погрешности) то все остальные элементы в этом столбце также равны нулю, значит нужно перейти на следующую колонку
				{
					matrix.SetElemOnColumn(StringNum, 0.0, ColumnNum);
					ColumnNum++;
					continue;
				}
				if (IndexOfMax != ColumnNum)                                           // Если мы не находимся на позиции с максимальным элементом то нужно поменять строки местами
				{
					Swap(IndexOfMax, ColumnNum);
					if (_ShowIteration) { std::cout << endl; matrix.ShowMartrix(); vector.ShowVector(); std::cout << endl << endl; }
				}

				T ElemNow = matrix[ColumnNum][StringNum];                              // Переменная хранит текущий элемент, т.е. максимальный
				if (abs(ElemNow) < precision)
				{
					throw exception("ERROR (деление на 0)");                       // Если текущий элемент оказался 0, то произойдёт деление на 0 на следующем этапе
				}
				else
				{
					for (int i = ColumnNum + 1; i < matrix.GetColumnSize(); i++)   // Поэлементно прибавляем к каждой строке текущую строчку умноженную на определённый коэффицент с цель занулить столбец
					{
						T Coefficient = -(matrix[i][StringNum]) / ElemNow;     // Здесь могло произойти деление на 0
						for (int j = StringNum; j < matrix.GetStringSize(); j++)
						{
							matrix[i][j] += Coefficient * matrix[ColumnNum][j];         // Прибавляем к каждому элементу строки соответсвующий элемент исходной строки умноженный на коэффицент
							if (abs(matrix[i][j]) < precision) { matrix[i][j] = 0; }    // Достаточно малые числа принимаем равными 0
						}
						vector[i] += Coefficient * vector[ColumnNum];          // Аналогичная операция и с вектором
						if (abs(vector[i]) < precision) { vector[i] = 0; }
					}
					ColumnNum++;
				}
			}
		}
	}


	void ReverseCourse()
	{
		for (int ColumnNum = matrix.GetColumnSize() - 1; ColumnNum >= 0; ColumnNum--)
		{
			int FirstNotNullElem = 0;
			for (FirstNotNullElem = 0; FirstNotNullElem < matrix.GetStringSize() && matrix[ColumnNum][FirstNotNullElem] == 0; FirstNotNullElem++) {} // Находим первый ненулевой элемент в строчке
			if (FirstNotNullElem == matrix.GetStringSize())  // Если он совпал с размером матрицы, значит вся строка состоит из 0 и нужно проверить совместная ли СЛУ
			{
				if (vector[ColumnNum] != 0)
				{
					throw exception("ERROR 000....00 | not 0 (несовместная система уравнений)");
				}
			}
			else         // Т.к. у СЛУ может быть несколько решений, то будем находить хотябы одно из них
			{
				T result = 0;   // Будем выражать базисный х, соответсвующий первому ненулевому элементу через другие
				for (int i = FirstNotNullElem + 1; i < matrix.GetStringSize(); i++)
				{
					result += answer[i] * matrix[ColumnNum][i];       // На моменте создания класса вектор answer состоит из нулей, поэтому все свободные элементы равны 0 
				}
				answer[FirstNotNullElem] = (vector[ColumnNum] - result) / matrix[ColumnNum][FirstNotNullElem];
				if (abs(answer[FirstNotNullElem]) < precision) { answer[FirstNotNullElem] = 0; }
			}
		}
	}

	void Check()
	{
		for (int i = 0; i < matrix.GetColumnSize(); i++)
		{
			T result = 0; // Осуществляем проверку
			for (int j = 0; j < matrix.GetStringSize() - 1; j++)
			{
				result += matrix[i][j] * answer[j];
				std::cout << "( " << matrix[i][j] << " )*( " << answer[j] << " ) + ";
			}
			result += matrix[i][matrix.GetStringSize() - 1] * answer[matrix.GetStringSize() - 1];
			std::cout << "( " << matrix[i][matrix.GetStringSize() - 1] << " )*( " << answer[matrix.GetStringSize() - 1] << " ) = " << result;
			if (abs(result - vector[i]) < precision)  // Если модуль разности полученного значения и действительного достаточно мал, то они считаются совпадающим 
			{
				std::cout << " Its right!\n";
			}
			else
			{
				std::cout << " Not right!\n";
				throw exception("ERROR NOT RIGHT RESULT!");
			}
		}

	}
};

int main()
{
	int col, str, choose;
	setlocale(LC_ALL, "Russian");
	std::cout << "enter the size of the matrix : " << endl;
	std::cin >> col;
	std::cin >> str;


	Matrix <double>A(col, str);
	Vector<double> vector(col);
	Vector<double> ans(str);

	std::cout << "Choose input method :\n\t1 - enter the matrix yourself \n\t2 - generate it automatically " << endl;
	std::cin >> choose;
	if (choose == 1)
	{
		std::cout << endl << "Enter matrix :\n";
		A.SetMatrixValue();
		std::cout << endl;
		A.ShowMartrix();
		std::cout << endl << "Enter vector:\n";
		vector.SetVectorValue();
		std::cout << endl;
		vector.ShowVector();
	}
	else
	{
		vector.GenerateRandomVector();
		A.GenerateMatrixValue();
		std::cout << endl;
		A.ShowMartrix();
		std::cout << endl;
		vector.ShowVector();
	}


	SLU<double> S(A, vector, 0.00001);

	std::cout << "\nShow the execution of the Gauss method?\n\t1 - Yes \n\t0 - No " << endl;
	std::cin >> choose;
	if (choose == 1)
	{
		S.ShowIteration();
	}
	else
	{
		S.DontShowIteration();
	}

	try
	{
		ans = S.GAUSS();

		std::cout << "\n\nNeed to check?\n\t1 - Yes \n\t0 - No " << endl;
		std::cin >> choose;
		if (choose == 1)
		{
			S.Check();
		}
	}
	catch (const std::exception& exp)
	{
		std::cout << endl << exp.what() << endl;
	}
}
