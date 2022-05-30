#include <iostream>
#include <cmath>
#include <ctime>

template<class T>
class vector
{
protected:
    T* mas;
    int size;
public:
    vector(int size_)
    {
        mas = new T[size_];
        size = size_;
    }
    vector()
    {
        mas = new T[0];
        size = 0;
    }
    vector(vector& s)
    {
        size = s.size;
        mas = new T[size];
        for (int i = 0; i < size; i++)
        {
            mas[i] = s.mas[i];
        }
    }
    ~vector()
    {
        delete[] mas;
    }
    int get_size()
    {
        return size;
    }
    T& operator[] (int i)
    {
        return mas[i];
    }
    void set_vector()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cin >> mas[i];
        }
    }
    void print_vector()
    {
        std::cout << "{ ";
        for (int i = 0; i < size; ++i)
        {
            std::cout << mas[i] << ", ";
        }
        std::cout << "}" << std::endl;
    }
    void division_val(T val)
    {
        for (int i = 0; i < size; ++i)
        {
            mas[i] /= val;
        }
    }
    void resize(int size_)
    {
        delete[] mas;
        mas = new T[size_];
        size = size_;
    }
    void swap_rows(int i1, int i2)
    {
        T tmp;
        tmp = mas[i1];
        mas[i1] = mas[i2];
        mas[i2] = tmp;
    }
};

template<class T>
class matrix : public vector<vector<T>>
{
public:
    matrix(int size) : vector<vector<T>>(size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->mas[i].resize(size);
        }
    }
    matrix() : vector<vector<T>>() {}
    matrix(matrix& s)
    {
        this->size = s.size;
        this->mas = new vector<T>[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->mas[i].resize(this->size);
            for (int j = 0; j < this->size; j++)
            {
                this->mas[i][j] = s.mas[i][j];
            }
        }
    }
    void print_matrix()
    {
        std::cout << std::endl;
        for (int i = 0; i < this->size; ++i)
        {
            std::cout << std::endl;
            for (int j = 0; j < this->size; ++j)
                std::cout << this->mas[i][j] << " ";
        }
        std::cout << std::endl;
    }
    vector<T> multiply_vec(vector<T>& s)
    {
        vector<T> res(this->size);
        for (int i = 0; i < this->size; i++)
        {
            T tmp = 0;
            for (int j = 0; j < this->size; j++)
                tmp += (this->mas[i][j] * s[j]);
            res[i] = tmp;
        }
        return res;
    }
    void swap_rows(int i1, int i2)
    {
        T tmp;
        for (int i = 0; i < this->size; ++i)
        {
            tmp = this->mas[i1][i];
            this->mas[i1][i] = this->mas[i2][i];
            this->mas[i2][i] = tmp;
        }
    }
};

template<class T>
class SLAU
{
private:
    matrix<T> A;
    vector<T> Y;
    vector<T> X;
    int rows;
public:
    SLAU(int size_)
    {
        rows = size_;
    }
    void set_SLAU()
    {
        A.resize(rows);
        Y.resize(rows);
        X.resize(rows);
        for (int i = 0; i < rows; ++i)
        {
            A[i].resize(rows);
            for (int j = 0; j < rows; ++j)
            {
                std::cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
                std::cin >> A[i][j];
            }
            std::cout << "Y[" << i + 1 << "] = ";
            std::cin >> Y[i];
        }
    }
    void print_SLAU()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                std::cout << "(" << A[i][j] << ")" << "*x" << j + 1;
                if (j < rows - 1)
                    std::cout << " + ";
            }
            std::cout << " = " << Y[i] << std::endl;
        }
    }

    vector<T> Gauss()
    {
        matrix<T> a(A);
        vector<T> y(Y);
        int k, imax = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                int k = 0;
                for (; k < rows; k++)
                {
                    if ((a[j][k] > 0.0000001) && (a[k][j] > 0.0000001))
                        break;
                }
                if ((k == rows) && (y[j] < 0.0000001))
                {
                    std::cout << "\nThe solution is not the only one";
                    return 0;
                }
                else if (((k == rows) && (y[j] > 0.0000001)) || (j == rows))
                {
                    throw std::exception("There are no solutions");
                    return 0;
                }
            }
            imax = i;
            for (int j = i + 1; j < rows; j++)
            {
                if (abs(a[imax][i]) < abs(a[j][i]))
                    imax = j;
            }
            a.swap_rows(imax, i);
            y.swap_rows(imax, i);
            a.print_matrix();
            y.print_vector();
            y[i] /= a[i][i];
            a[i].division_val(a[i][i]);
            a.print_matrix();
            y.print_vector();
            for (int j = i + 1; j < rows; j++)
            {
                double tmp = a[j][i];
                for (k = 0; k < rows; k++)
                {
                    a[j][k] -= a[i][k] * tmp;
                }
                y[j] -= y[i] * tmp;
            }
            a.print_matrix();
            y.print_vector();
        }
        y[rows - 1] /= a[rows - 1][rows - 1];
        a[rows - 1][rows - 1] /= a[rows - 1][rows - 1];
        for (int i = rows - 1; i >= 0; i--)
        {
            X[i] = y[i];
            for (int j = 0; j < i; j++)
                y[j] = y[j] - a[j][i] * X[i];
        }
        std::cout << "\nX = ";
        X.print_vector();
        correct_check();
        return X;
    }
    void fill_rand()
    {
        std::srand(time(0));
        A.resize(rows);
        Y.resize(rows);
        X.resize(rows);
        for (int i = 0; i < rows; ++i)
        {
            A[i].resize(rows);
            Y[i] = (((double)rand()) / 5000.0) - 3.0;
            for (int j = 0; j < rows; ++j)
            {
                A[i][j] = (((double)rand()) / 5000.0) - 3.0;
                if (i == j)
                    A[i][j] = rows * 5.0 + (((double)rand()) / ((50000.0 / (rows * 5.0))));
            }
        }
    }
    void correct_check()
    {
        A.multiply_vec(X).print_vector();
        for (int i = 0; i < rows; i++)
        {
            if (abs(A.multiply_vec(X)[i] - Y[i]) > 0.0000001)
            {
                std::cout << "\n Solved incorrectly!" << std::endl;
                return;
            }
        }
        std::cout << "\n Solved correctly!" << std::endl;
    }
};


int main()
{
    int n, type;
    {
        std::cout << "\nInput size: ";
        std::cin >> n;
        SLAU<double> a(n);
        std::cout << "Press 0 to enter the system from the keyboard and 1 to randomly generate the system: ";
        std::cin >> type;
        if (type == 0)
            a.set_SLAU();
        else if (type == 1)
            a.fill_rand();
        else
        {
            std::cout << "ERROR!";
            return 0;
        }
        std::cout << std::endl;
        if (n < 10)
            a.print_SLAU();
        std::cout << std::endl;
        try
        {
            a.Gauss();
        }
        catch (std::exception& ex)
        {
            std::cout << ex.what();
        }
    }
    return 0;
}