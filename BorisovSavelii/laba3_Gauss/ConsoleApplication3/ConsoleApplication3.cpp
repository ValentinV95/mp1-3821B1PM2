#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

template<typename T>
class Vector
{
protected:
	T* coordinates;
	int size;

public:
	Vector(int in_size = 1)
	{
		if (in_size < 0)
		{
			throw "Creating array with negative size";
		}
		size = in_size;
		coordinates = new T[size];
	}

	Vector(const Vector<T>& other)
	{
		this->size = other.size;
		this->coordinates = new T[other.size];
		for (int i = 0; i < other.size; i++)
		{
			this->coordinates[i] = other.coordinates[i];
		}
	}

	void resize(int rsize)
	{
		size = rsize;

		delete[] coordinates;

		coordinates = new T[rsize];
	}

	void random_filling(int index)
	{
		for (int i = 0; i < size; i++)
		{
			if (i != index || index == size)
			{
				coordinates[i] = 1 + rand() % 5;
			}
			else
			{
				coordinates[i] = 10 + (size * size - size) * 5 + rand() % (5 * size);
			}
		}
	}

	Vector<T>& operator = (const Vector<T>& other)
	{
		resize(other.size);

		for (int i = 0; i < other.size; i++)
		{
			this->coordinates[i] = other.coordinates[i];
		}
		return *this;
	}

	T& operator[](int index)
	{
		if (index >= size)
		{
			throw "Array index out of bounds";
		}
		return coordinates[index];
	}

	~Vector()
	{
		delete[] coordinates;
	}
};

template<typename T>
class Matrix : public Vector<Vector<T>>
{
public:
	Matrix(int matrix_size = 1) : Vector<Vector<T>>(matrix_size)
	{
		for (int i = 0; i < matrix_size; i++)
		{
			this->coordinates[i].resize(matrix_size);
		}
	}

	Vector<T>& operator[](int index)
	{
		if (index >= this->size)
		{
			throw "Array index out of bounds";
		}
		return this->coordinates[index];
	}
};

template<typename T>
class SLAU : public Matrix<T>
{
private:
	void create_tmp_copy(Matrix<T>& tmp_copy)
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				tmp_copy[i][j] = this->coordinates[i][j];
			}
		}
	}

	void check(Matrix<T>& A, Vector<T>& b, Vector<T>& x)
	{
		cout << "\nChecking the correctness of the solution:\n" << endl;
		bool solution_correct = true;
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
				cout << "The solution is incorrect" << endl;
				solution_correct = false;
				break;
			}
		}

		if (solution_correct)
		{
			cout << "The solution is correct" << endl;
		}
	}

public:
	SLAU(int slau_size = 1) : Matrix<T>(slau_size)
	{

	}

	void solve(Vector<T>& b)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->coordinates[i][i] == 0)
			{
				cout << "The system has no solution or has more than one solutions" << endl;
				return;
			}
		}

		int max_row;
		Matrix<T> A_copy(this->size);
		create_tmp_copy(A_copy);
		Vector<T> b_copy(b);
		Vector<T> x(this->size);

		for (int column = 0; column < this->size; column++)     // create an upper triangular matrix
		{
			max_row = column;
			for (int row = column + 1; row < this->size; row++)    // finding maximum element in a column
			{
				if (fabs(this->coordinates[max_row][column]) < fabs(this->coordinates[row][column]))
				{
					max_row = row;
				}
			}

			if (column != max_row)   // row swap
			{
				T tmp;
				Vector<T> tmp_vector;

				tmp = b[column];
				b[column] = b[max_row];
				b[max_row] = tmp;

				tmp_vector = this->coordinates[column];
				this->coordinates[column] = this->coordinates[max_row];
				this->coordinates[max_row] = tmp_vector;
			}

			for (int row = column; row < this->size; row++)     // row normalization
			{
				for (int column_tmp = this->size; column_tmp > column - 1; column_tmp--)
				{

					if (this->coordinates[row][column] == 0)
					{
						throw "\nZero Devision Error";
					}
					else
					{
						if (column_tmp == this->size)
						{
							b[row] /= this->coordinates[row][column];
						}
						else
						{
							this->coordinates[row][column_tmp] /= this->coordinates[row][column];
						}
					}

				}
			}

			if (column < this->size - 1)      // row subtraction
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
							this->coordinates[row][column_tmp] -= this->coordinates[column][column_tmp];
						}
					}
				}
			}
		}

		int zero_counter;
		bool one_solution = true;
		cout << "\nAnswer:\n" << endl;

		for (int row = 0; row < this->size; row++)      // check for the number of solutions
		{
			zero_counter = 0;
			for (int column = 0; column < this->size; column++)
			{
				if (this->coordinates[row][column] == 0)
				{
					zero_counter++;
				}
			}

			if (zero_counter == this->size && b[row] != 0)
			{
				cout << "\nNo solutions" << endl;
				return;
			}
			else if (zero_counter == this->size && b[row] == 0)
			{
				one_solution = false;
			}
		}

		if (one_solution)     // finding x
		{
			x[this->size - 1] = b[this->size - 1];

			for (int row_x = (this->size - 2); row_x > -1; row_x--)
			{
				for (int column_x = row_x + 1; column_x < this->size; column_x++)
				{
					b[row_x] -= (this->coordinates[row_x][column_x] * x[column_x]);
				}
				x[row_x] = b[row_x];
			}

			for (int i = 0; i < this->size; i++)
			{
				cout << "x" << i + 1 << " = " << x[i] << endl;
			}

			check(A_copy, b_copy, x);
		}
		else
		{
			cout << "\nInfinitely many solutions" << endl;
		}
	}
};

int main()
{
	srand(static_cast<unsigned>(time(0)));

	int dimension;
	cout << "Matrix dimension: ";
	cin >> dimension;

	int select;
	cout << "Choice of filling method for matrix A and vector b: \n\n 1 - Random filling \n 2 - Manual filling \n\nEnter the number: ";
	cin >> select;

	bool random_filling = true;
	if (select == 2)
	{
		random_filling = false;
	}
	else if (select != 1 && select != 2)
	{
		cout << "Invalid number of filling method" << endl;
		exit(0);
	}

	try
	{
		SLAU<double> A(dimension);
		Vector<double> b(dimension);

		if (random_filling)
		{
			for (int i = 0; i < dimension; i++)
			{
				A[i].random_filling(i);
			}
			b.random_filling(dimension);
		}
		else //Manual filling
		{
			cout << "\nManual filling: A(row, column)" << endl;

			for (int i = 0; i < dimension; i++)
			{
				for (int j = 0; j < dimension; j++)
				{
					cout << "A(" << i + 1 << ',' << j + 1 << "): ";
					cin >> A[i][j];
				}
			}

			for (int i = 0; i < dimension; i++)
			{
				cout << "b(" << i + 1 << "): ";
				cin >> b[i];
			}
		}

		cout << "\nExtended matrix:\n" << endl;
		for (int i = 0; i < dimension; i++)
		{

			for (int j = 0; j < dimension + 1; j++)
			{
				if (j != dimension)
				{
					cout << A[i][j] << "    ";
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
	catch (const char* except)
	{
		cout << except << endl;
	}

	return 0;
}
