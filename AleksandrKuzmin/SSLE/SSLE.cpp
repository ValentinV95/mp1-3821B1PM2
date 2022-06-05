#include <iostream>
#include <cmath>
#include <ctime>


using namespace std;

template<typename T>
class MyVector
{
protected:
	T* Coords;
	int size;

public:
	MyVector(int entrSize = 1)
	{
		if (entrSize < 0)
		{
			throw "Creating an array with a negative size";
		}
		size = entrSize;
		Coords = new T[size];
	}

	MyVector(const MyVector<T>& another)
	{
		this->size = another.size;
		this->Coords = new T[another.size];
		for (int i = 0; i < another.size; i++)
		{
			this->Coords[i] = another.Coords[i];
		}
	}

	void RandomFilling(int index)
	{
		for (int i = 0; i < size; i++)
		{
			if (i != index || index == size)
			{
				Coords[i] = 2 + rand() % 7;
			}
			else
			{
				Coords[i] = 12 + (size * size - size) * 7 + rand() % (7 * size);
			}
		}
	}


	void Resize(int rsize)
	{
		size = rsize;

		delete[] Coords;

		Coords = new T[rsize];
	}

	T& operator[](int index)
	{
		if (index >= size)
		{
			throw "Array index out of range";
		}
		return Coords[index];
	}

	MyVector<T>& operator = (const MyVector<T>& another)
	{
		Resize(another.size);

		for (int i = 0; i < another.size; i++)
		{
			this->Coords[i] = another.Coords[i];
		}
		return *this;
	}

	~MyVector()
	{
		delete[] Coords;
	}
};

template<typename T>
class Matrix : public MyVector<MyVector<T>>
{
public:
	Matrix(int matrix_size = 1) : MyVector<MyVector<T>>(matrix_size)
	{
		for (int i = 0; i < matrix_size; i++)
		{
			this->Coords[i].Resize(matrix_size);
		}
	}

	MyVector<T>& operator[](int index)
	{
		if (index >= this->size)
		{
			throw "Array index out of range";
		}
		return this->Coords[index];
	}
};

template<typename T>
class SSLE : public Matrix<T>     //SSLE - system of solutions of linear equations
{
private:
	void CreateTempCopy(Matrix<T>& tempCopy)
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				tempCopy[i][j] = this->Coords[i][j];
			}
		}
	}

	void Check(Matrix<T>& A, MyVector<T>& b, MyVector<T>& x)
	{
		cout << "\nThe solution is correct:\n" << endl;
		bool SolutionCorrect = true;
		T _x;
		for (int i = 0; i < this->size; i++)
		{
			_x = 0;
			for (int j = 0; j < this->size; j++)
			{
				_x += x[j] * A[i][j];
			}
			if (fabs(b[i] - _x) > 0.0000000001)
			{
				cout << "No" << endl;
				SolutionCorrect = false;
				break;
			}
		}

		if (SolutionCorrect)
		{
			cout << "Yes" << endl;
		}
	}

public:
	SSLE(int SSLE_size = 1) : Matrix<T>(SSLE_size)
	{

	}

	void Solution(MyVector<T>& b)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->Coords[i][i] == 0)
			{
				cout << "System has more than one solution or none at all" << endl;
				return;
			}
		}

		
		Matrix<T> A_copied(this->size);
		CreateTempCopy(A_copied);
		MyVector<T> b_copied(b);
		MyVector<T> x(this->size);
		int maxRow;

		for (int column = 0; column < this->size; column++)
		{
			maxRow = column;
			for (int row = column + 1; row < this->size; row++)
			{
				if (fabs(this->Coords[maxRow][column]) < fabs(this->Coords[row][column]))
				{
					maxRow = row;
				}
			}

			if (column != maxRow)
			{
				T tmp;
				MyVector<T> tmpVector;

				tmp = b[column];
				b[column] = b[maxRow];
				b[maxRow] = tmp;

				tmpVector = this->Coords[column];
				this->Coords[column] = this->Coords[maxRow];
				this->Coords[maxRow] = tmpVector;
			}

			for (int row = column; row < this->size; row++)
			{
				for (int column_tmp = this->size; column_tmp > column - 1; column_tmp--)
				{

					if (this->Coords[row][column] == 0)
					{
						throw "\nDivision by zero";
					}
					else
					{
						if (column_tmp == this->size)
						{
							b[row] /= this->Coords[row][column];
						}
						else
						{
							this->Coords[row][column_tmp] /= this->Coords[row][column];
						}
					}

				}
			}

			if (column < this->size - 1)
			{
				for (int row = column + 1; row < this->size; row++)
				{
					for (int column_tmp = column; column_tmp < this->size + 1; column_tmp++)
					{
						if (column_tmp == this->size)
						{
							b[row] -= b[column];
						}
						else
						{
							this->Coords[row][column_tmp] -= this->Coords[column][column_tmp];
						}
					}
				}
			}
		}

		bool onlySolution = true;
		int ZeroCounter;
		cout << "\nSolution:\n" << endl;

		for (int row = 0; row < this->size; row++)
		{
			ZeroCounter = 0;
			for (int column = 0; column < this->size; column++)
			{
				if (this->Coords[row][column] == 0)
				{
					ZeroCounter++;
				}
			}

			if (ZeroCounter == this->size && b[row] != 0)
			{
				cout << "\nNo solutions" << endl;
				return;
			}
			else if (ZeroCounter == this->size && b[row] == 0)
			{
				onlySolution = false;
			}
		}

		if (onlySolution)
		{
			x[this->size - 1] = b[this->size - 1];

			for (int row_x = (this->size - 2); row_x > -1; row_x--)
			{
				for (int column_x = row_x + 1; column_x < this->size; column_x++)
				{
					b[row_x] -= (this->Coords[row_x][column_x] * x[column_x]);
				}
				x[row_x] = b[row_x];
			}

			for (int i = 0; i < this->size; i++)
			{
				cout << "x" << i + 1 << " = " << x[i] << endl;
			}

			Check(A_copied, b_copied, x);
		}
		else
		{
			cout << "\nInfinitely many solutions" << endl;
		}
	}
};

int main()
{
	
	cout << "Square matrix dimension: ";
	int Dimension;
	cin >> Dimension;

	cout << "Select the fill method for matrix A and vector b : \n\n 1 - Random filling \n 2 - Manual filling \n\nEnter the number: ";
	int select;
	cin >> select;

	srand(static_cast<unsigned>(time(0)));

	bool RandomFilling = true;
	if (select == 2)
	{
		RandomFilling = false;
	}
	else if (select != 1 && select != 2)
	{
		cout << "Look at screen again, and make right choice" << endl;
		exit(0);
	}

	try
	{
		SSLE<double> A(Dimension);
		MyVector<double> b(Dimension);

		if (RandomFilling)
		{
			for (int i = 0; i < Dimension; i++)
			{
				A[i].RandomFilling(i);
			}
			b.RandomFilling(Dimension);
		}
		else 
		{
			cout << "\nManual filling: A[row][column]" << endl;

			for (int i = 0; i < Dimension; i++)
			{
				for (int j = 0; j < Dimension; j++)
				{
					cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
					cin >> A[i][j];
				}
			}

			for (int i = 0; i < Dimension; i++)
			{
				cout << "b(" << i + 1 << "): ";
				cin >> b[i];
			}
		}

		cout << "\nExtended matrix:\n" << endl;
		for (int i = 0; i < Dimension; i++)
		{

			for (int j = 0; j < Dimension + 1; j++)
			{
				if (j != Dimension)
				{
					cout << A[i][j] << "   ";
				}
				else
				{
					cout << "| " << b[i];
				}
			}
			cout << "\n" << endl;
		}

		A.Solution(b);
	}
	catch (const char* Exeption)
	{
		cout << Exeption << endl;
	}

	return 0;
}
