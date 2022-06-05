#include <iostream>
#include <clocale>
#include <cmath>
#include <ctime>
#define epsilon 0.000000001

using namespace std;

template<typename T>
class MyVector
{
public:
    T* arr;
	int size;
	
	MyVector(int size = 5)
	{
		this->size = size;
		this->arr = new T[size];
	}

	MyVector(const MyVector<T>& other)
	{
		this->size = other.size;
		this->arr = new T[size];
		
		for (int i = 0; i < size; i++)
		{
			this->arr[i] = other.arr[i];
		}
	}

	void resize(int size)
	{
		this->size = size;
		delete[] this->arr;
		this->arr = new T[size];
	}

    
	T& operator[](int i)
	{
		return this->arr[i];
	}

	MyVector<T>& operator = (const MyVector<T>& other)
	{
		this->size = other.size;

		delete[] this->arr;

		this->arr = new T[size];

		for (int i = 0; i < size; i++)
		{
			this->arr[i] = other.arr[i];
		}
		return *this;
	}

	~MyVector()
	{
		delete[] this->arr;
	}
};

template<typename T>
class MyMatrix : public MyVector<MyVector<T>>
{
public:
	MyMatrix(int size = 5) : MyVector<MyVector<T>>(size)
	{
		for (int i = 0; i < size; i++)
		{
			this->arr[i].resize(size);
		}
	}

	MyVector<T>& operator[](int i)
	{
		return this->arr[i];
	}
};

template<typename T>
class slau : public MyMatrix<T>
{
public:
	slau(int size = 5) : MyMatrix<T>(size) {}
	
	void check(MyMatrix<T>& A, MyVector<T>& X_arg, MyVector<T>& B)
	{
		for (int i = 0; i < this->size; i++)
		{
			T elb = 0;
			for (int j = 0; j < this->size; j++)
			{
				elb += X_arg[j] * A[i][j];
			}
			if (fabs(B[i] - elb) > epsilon)
			{
				cout << "Решение неверное" << endl;
				return;
			}
		}
		cout << "Решение верное" << endl;
		
	}
	
	void find_max(int col, int& max)
	{
	    max = col;
		for (int line = col + 1; line < this->size; line++)   
		{
			if (fabs(this->arr[max][col]) < fabs(this->arr[line][col]))
			{
				max = line;
			}
		}
	}
	
	void division_lines(int col, MyVector<T>& B)
	{
	    for (int line = col; line < this->size; line++)   
		{
			for (int col_tmp = this->size; col_tmp > col - 1; col_tmp--)
			{

				if (this->arr[line][col] == 0)
				{
					throw 0;
				}
				
				if (col_tmp != this->size)
				{
				    this->arr[line][col_tmp] /= this->arr[line][col];
				}
				else
				{
					B[line] /= this->arr[line][col];
				}
				

			}
		}
	}
	
	void subtract_lines(int col, MyVector<T>& B)
	{
	    
		for (int line = col + 1; line < this->size; line++)
		{
			for (int col_tmp = col; col_tmp < this->size + 1; col_tmp++)
			{
				if (col_tmp != this->size)
				{
				    this->arr[line][col_tmp] -= this->arr[col][col_tmp];
				}
				else
				{
						B[line] -= B[col];
				}
			}
		}
		
	}
	
	void swap(MyVector<T>& B, int line, int i)
	{
	    T elb;
		MyVector<T> vA(this->arr[i]);
		this->arr[i] = this->arr[line];
		this->arr[line] = vA;

		elb = B[i];
		B[i] = B[line];
		B[line] = elb;
	}
	
	void fill_and_show(MyVector<T>& B, MyVector<T>& X_arg)
	{
	    X_arg[this->size - 1] = B[this->size - 1];
		for (int line_x = this->size - 2; line_x >= 0; line_x--)
		{
			for (int col_x = line_x + 1; col_x < this->size; col_x++)
			{
				B[line_x] -= (this->arr[line_x][col_x] * X_arg[col_x]);
			}
			X_arg[line_x] = B[line_x];
			cout << "X_arg" << this->size - (line_x + 1) << " = " << X_arg[line_x] << endl;
		}
		cout << "X_arg" << this->size << " = " << X_arg[this->size - 1] << endl;
	}

	void GAUSS(MyVector<T>& B)
	{
		int max_line;
		MyVector<T> other_B(B);
		MyVector<T> X_arg(this->size);
		MyMatrix<T> A_copy(this->size);
		
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				A_copy[i][j] = this->arr[i][j];
			}
		}
		
		for (int col = 0; col < this->size; col++)   
		{
		    find_max(col, max_line);
		    
			swap(B, col, max_line);
			
			division_lines(col, B);
            
            if (col < this->size - 1)     
			{
			    subtract_lines(col, B);
			}
			
		}
        fill_and_show(B, X_arg);

		check(A_copy, X_arg, other_B);
	}
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
	int size;
	cout << "Введите размер матрицы: ";
	cin >> size;

	int fillnum;
	cout << "Выберите способ заполнения: 1 - Рандомный 2 - Ручной \nНомер: ";
	cin >> fillnum;

	slau<double> A(size);
	MyVector<double> B(size);
	
	if (fillnum == 1)
	{
		for (int i = 0; i < size; i++)
		{
		    for (int j = 0; j < size; j++)
		    {
		    	if (j != i)
		    	{
		    		A[i][j] = 1 + rand() % 3;
		    	}
		    	else
		    	{
		    		A[i][j] = size*1000 + rand() % (size*10000);
		    	}
		    }
		    B[i] = rand() % 100;
		}
	}
	
	else if (fillnum == 2) 
	{
		cout << "\nРучное заполнение:" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
				cin >> A[i][j];
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << "B[" << i + 1 << "]: ";
			cin >> B[i];
		}
	}
	else
	{
	    cout << "Неверный номер способа заполнения";
	    exit(fillnum);
	}
	
    try
	{
		A.GAUSS(B);
	}
	catch (const int e)
	{
	    cout << "ERROR:";
		cout << e << endl;
	}

	return 0;
}