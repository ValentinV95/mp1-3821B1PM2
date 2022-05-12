// lab_method_Gauss.cpp : реализация метода гаусса ведущим элементом 
//в квадратных матрицах

#include <iostream>
#include <locale.h>

template <typename T>
class myVector {
public:
    T* arr;
    int size;
public:
    myVector()
    {
        size = 0;
        arr = new T[1];
    }

    myVector(int n)
    {
        this->size = n;
        this->arr = new T[n];
    }

    myVector(const T* arr, int n)
    {
        this->size = n;
        this->arr = new T[n];
        for (int i = 0; i < n; i++)
            this->arr[i] = arr[i];
    }

    int& GetSize()
    {
        return size;
    }

    T& operator[](const int index)     ////
    {
        return arr[index];
    }

    void operator=(const myVector <T>& a)
    {
        for (int i = 0; i < a.size; i++)
            arr[i] = a.arr[i];
    }

    void resize(const int _size)
    {
        this->size = _size;
        delete[] arr;
        this->arr = new T[_size];

        for (int i = 0; i < _size; i++)
            this->arr[i] = 0;
    }

    ~myVector() 
    { 
        delete[] this->arr;
    }
};

template <typename T>
class Gauss_exceptions :public std::exception {
private:
    myVector<T> error_string;
public:
    Gauss_exceptions(const char* message, myVector<T>& error_string) : std::exception(message)
    {
        this->error_string.resize(error_string.GetSize());
        this->error_string = error_string;
    }

    void Get_error_string(int Size)
    {
        for (int i = 0; i < Size; i++)
            std::cout << error_string[i] << "\t";
        std::cout << "\n";
    }

    ~Gauss_exceptions() {}
};

template <typename T>
class myMatrix:public myVector <myVector <T>> {
protected:
    int size_string;
    int size_column;
public:
    myMatrix(const int n) : myVector <myVector <T>>(n)
    {
        size_column = n;
        size_string = 1;
    }

    void show()
    {
        for (int i = 0; i < size_column; i++)
        {
            for (int j = 0; j < size_string; j++)
                std::cout << this->arr[i][j] << "\t";
            std::cout << "\n";
        }
    }

    void Add_arr(const int size_str)
    {
        size_string = size_str;
        for (int i = 0; i < size_column; i++)
        {
            this->arr[i].resize(size_string);
            std::cout << "Введите коэфициенты " << i+1 << " уравнения: " << std::endl;
            for (int j = 0; j < size_string; j++)
                std::cin >> this->arr[i][j];
        }        
    }

    int max_index(const int j)
    {
        int id = 1;
        for (int i = 0; i < size_column; i++)
            if (this->arr[i][j] > this->arr[id][j])
                id = i;

        return id;
    }

    void swap(int first_id, int second_id)
    {
        myVector <T> tmp(size_string);
        tmp = this->arr[first_id];
        this->arr[first_id] = this->arr[second_id];
        this->arr[second_id] = tmp;
    }

    T multiply_matrixA(const myVector<T>& x, T* res)                   //перемножение матрицы левого столбца на вектор
    {
        for (int i = 0; i < size_column; i++)
            res[i] = 0;

        for (int i = 0, k = 0; i < size_column; i++, k++)
            for (int j = 0; j < size_string-1; j++)
                res[k] += this->arr[i][j] * x.arr[j];

        return *res;
    }

    ~myMatrix() {}
};

template <typename T>
class SLAU: public myMatrix<T>
{
public:
    SLAU(const int _size_column) :myMatrix<T>(_size_column) {}

    int check(const T* res)                       //проверка правильности решения
    {
        myVector<T> X(res, this->size_string-1);
        T* tmp = new T [this->size_column];
        *tmp = this->multiply_matrixA(X, tmp);

        for (int i = 0; i < this->size_column; i++)
        {
            if (tmp[i] == this->arr[i][this->size_string-1]) {}
            else 
            {
                std::cout << "ERROR: решение не корректно\n" << std::endl;
                return 0;
            }
        }
        delete[] tmp;

        std::cout << "Получен правильный результат\n" << std::endl;
        return 0;
    }

    void revers_motion()                                 //обратный ход метода Гаусса
    {
        T* result = new T [this->size_string-1];

        int k = this->size_string-1;

        for (int i = this->size_column-1; i >= 0; i--)
        {
            k -= 1;
            result[k] = this->arr[i][this->size_string - 1];
            for (int j = this->size_string - 2; j > k; j--)
                result[k] -= (this->arr[i][j] * result[k+1]);
        }

        for (int i = 0; i < this->size_string - 1; i++)
            std::cout << "X" << i << " = " << result[i] << std::endl;

        check(result);

        delete[] result;
    }

    void solve() //реализация метода гаусса
    {
        for (int this_row = 0, this_str = 0; this_str < this->size_column; this_row++, this_str++) // проход по каждому столбцу, проход по каждой строке
        {
            if (this_row < this->size_string)
            {
                int id = this->max_index(this_row); // нахождение максимального элемента в выбранном столбце

                if (this_str < id)
                    this->swap(this_str, id); // ставит строку с максимальным элементом наверх

                int tmp = 0;
                for (int i = 1; i < this->size_column; i++)
                {
                    for (int j = 0; j < this->size_string - 1; j++)
                        if (this->arr[i][j] != 0)
                            tmp = 1;
                    if (this->arr[i][this->size_string - 1] != 0 && tmp == 0)
                        throw Gauss_exceptions<T>("Система не совместна", this->arr[i]);
                }

                for (int i = this_str; i < this->size_column; i++) // делит в каждой строке каждый последующий элемент на выбранный элемент
                {    
                    for (int j = this_row+1; j < this->size_string; j++)
                        this->arr[i][j] /= this->arr[i][this_row];
                    this->arr[i][this_row] = 1;
                }     

                for (int i = this_str + 1; i < this->size_column; i++) // из всех последующих строчек вычитает выбранную строчку
                    for (int j = this_row; j < this->size_string; j++)
                        this->arr[i][j] -= this->arr[this_str][j];
            }
        }
        this->show();

        revers_motion();
    }

    ~SLAU() {}
};

void Input_size(int& size_string, int& size_column)
{
    std::cout << "Введите количество неизвестных:" << std::endl;
    std::cin >> size_string;
    size_column = size_string;
    size_string++;
    
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int size_string;
    int size_column;

    Input_size(size_string, size_column);

    SLAU <double> slu(size_column);

    slu.Add_arr(size_string);

    try 
    {
        slu.solve(); 
    }
    catch (Gauss_exceptions<double>& ex)
    {
        std::cout << "ERROR:" << std::endl;
        ex.Get_error_string(size_string);
        std::cout << ex.what() << std::endl;
    }
}
