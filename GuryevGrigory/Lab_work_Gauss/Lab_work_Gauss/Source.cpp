#include<iostream>
#include<locale.h>

using namespace std;

template<typename T>
class _Vector
{
private:
	int sz=1;
public:
	T* arr = NULL;
	_Vector(int size=1)
	{
		sz = size;
		arr = new T[sz];
	
	}
	~_Vector()
	{
		sz = 0;
		delete[](arr);
	}
	int& Lenght()
	{
		return sz;
	}
	void resize(int size)
	{
		T* temparr = new T[size];
		if (arr != NULL)
		{
			for (int i = 0; i < min(sz, size); i++)
			{
				temparr[i] = arr[i];
			}

			delete[] arr;
		}
		arr = new T[size];
		arr = temparr;
	}
	void vecpt()
	{
		cout << "|";
		for (int i = 0; i < sz; i++)
		{
			cout << arr[i] << " ";
		}
		cout << "|" << endl;
	}
	T& operator [](int index)
	{
		return arr[index];
	}
	void operator = (_Vector<T>& vector)
	{
		if (this != &vector)
		{
			if (arr != NULL) { delete[](arr); }
			sz = vector.Lenght();
			arr = new T[sz];
			for (int i = 0; i < sz; i++)
			{
				arr[i] = vector[i];
			}
				
		}
		//return *this;
	}

	void swap_elem(int index_i, int index_j)
	{
		T a = this->arr[index_i];
		this->arr[index_i] = this->arr[index_j];
		this->arr[index_j] = a;
	}

	void Set_Vector()
	{
		for (int i = 0; i < sz; i++)
		{
			T a;
			cin >> a;
			arr[i] = a;
		}
	}
};

template<typename T>
class mat :public _Vector<_Vector<T>>
{
private:
	int size_str;
	int size_col;
public:

	mat(int se=1,int col=1):_Vector<_Vector<T>>(col)
	{
		size_str = se;
		size_col = col;
		for (int i = 0; i < size_str; i++)
		{
			this->arr[i].resize(size_col);
		}
	}
	_Vector<T>& operator [](int index)
	{
		return this->arr[index];
	}
	void setmat()
	{
		for (int i = 0; i < size_str; i++)
		{

			_Vector<T> vec(size_col);
			vec.Set_Vector();
			this->arr[i] = vec;
		}
	}
	void resize_mat(int s, int c)
	{
		_Vector<T>* temparr = new _Vector<T>[s];
		if (this->arr != NULL)
		{
			for (int i = 0; i < min(size_str, s); i++)
			{
				temparr[i] = this->arr[i];
			}

			delete[] this->arr;
		}
		size_str = s;
		size_col = c;
		this->arr = new _Vector<T>[s];
		this->arr = temparr;
		for (int i = 0; i < size_str; i++)
		{
			this->arr[i].resize(size_col);
		}
		
	}
	void printmat()
	{
		for (int i = 0; i < size_str; i++)
		{
			this->arr[i].vecpt();
		}
		cout << "=========================" << endl;
	}
	void swap_strings(int index_i,int index_j)
	{
		_Vector<T> temparr(size_str);
		temparr = this->arr[index_i];
		this->arr[index_i] = this->arr[index_j];
		this->arr[index_j] = temparr;
	}
	int column_max(int col_ind)
	{
		int maxind = 1;
		for (int i = 0; i < size_col; i++)
		{
			if (this->arr[i][col_ind] > abs(this->arr[maxind][col_ind]))
			{
				maxind = i;
			}
		}
		return maxind;
	}
};

template<class T>
class gauss_elim_method
{
private:
	int size;
	T target_val;
	mat<T> mat_x;
	_Vector<T> B_vec;
	_Vector<T> Answer;
public:
	gauss_elim_method(int se, T tarval):mat_x(se,se),B_vec(se),Answer(se)
	{
		size = se;
		for (int i = 0; i < se; i++)
		{
			Answer[i] = 0;
		}
		Answer.vecpt();
	}
	void check()
	{
		for (int i = 0; i < size; i++)
		{

		}
	}
	void set_gauss_mat() {
		cout << "Введите матрицу" << endl;
		mat_x.setmat();
		cout << "Введите вектор" << endl;
		B_vec.Set_Vector();
		cout << "Ваша матрица" << endl;
		mat_x.printmat();
	}
	void gauss_forward()
	{
		for (int s = 0;s < size ; s++)
		{

				int Max_index_col = mat_x.column_max(s);
				if (s < Max_index_col)
				{
					mat_x.swap_strings(s, Max_index_col);
					B_vec.swap_elem(s, Max_index_col);
				}


				for (int i = 0; i < size-1; i+=2)
				{
					for (int j = 0; j < size; j++)
					{
						if (this->mat_x[i][j] == mat_x[i + 1][j])
						{
							if (B_vec[i] != B_vec[i + 1])
							{
								throw exception("несовместная система уравнений");
							}
						}
					}
				}

				for (int i = s; i < size; i++)
				{
					if (mat_x[i][s] == 0)
					{
						throw exception("деление на ноль");
					}
					for (int j = s+1 ; j < size; j++)
					{
						mat_x[i][j] /= mat_x[i][s];
					}
					B_vec[i] /= mat_x[i][s];
					mat_x[i][s] = 1;
				}

				for (int i = s + 1; i < size; i++)
				{
						for (int j = s; j < size; j++)
						{
							mat_x[i][j] -= mat_x[s][j];
						}
						//cout << B_vec.Lenght() << endl;
						B_vec[i] -= B_vec[s];
				}

		}
	}
	void gauss_backward()
	{
		for (int s = size - 1; s >= 0; s--)
		{
			Answer[s] = B_vec[s];
			for (int i = s + 1, q = 1; i < size; i++, q++)
			{
				Answer[s] -=(Answer[s + q] * mat_x[s][i]);
			}
		}
	}
	_Vector<T>& Gauss_elimination_method()
	{
		mat<T> check_mat(size,size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				check_mat[i][j] = mat_x[i][j];
			}
		}
		_Vector<T> check_vector(size);
		for (int i = 0; i < size; i++)
		{
			check_vector[i] = B_vec[i];
		}
		gauss_forward();
		mat_x.printmat();

		B_vec.vecpt();
		gauss_backward();
		cout << "Ответ:";
		Answer.vecpt();
		int truevals = 0;
		for (int i = 0; i < size; i++)
		{
			T gg = 0;
				for (int j = 0; j < size; j++)
				{
					gg += Answer[j] * check_mat[i][j];
				}
			if (check_vector[i] - gg <= target_val)truevals++;

		}
		if (truevals == size)
		{
			cout << "Алгоритм работает правильно" << endl;
		}
	
		return Answer;
	}
};

int main()
{
	setlocale(LC_ALL, "russian");
	int se;
	int sc;
	cin >> se;
	gauss_elim_method<double> gm(se, 0.00001f);
	gm.set_gauss_mat();
	try {
		gm.Gauss_elimination_method();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}