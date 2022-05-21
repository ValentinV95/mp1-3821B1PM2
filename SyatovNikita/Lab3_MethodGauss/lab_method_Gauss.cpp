// lab_method_Gauss.cpp : реализация метода гаусса ведущим элементом в квадратных матрицах

#include <iostream>
#include <locale.h>

template <typename T>
class myVector {
protected:
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

    void Add_vec()
    {
        std::cout << "Введите вектор b:" << std::endl;
        for (int i = 0; i < this->size; i++)
                std::cin >> this->arr[i];
    }

    void Add_vecRandom()
    {
        std::srand(time(0));
        for (int j = 0; j < this->size; j++)
        {
            this->arr[j] = (std::rand() % 101) * 10;
        }
    }

    int& GetSize()
    {
        return size;
    }

    T* GetArr()
    {
        return arr;
    }

    T& operator[](const int index)     ////
    {
        if (index >= size)
            throw std::exception("Выход за границы массива");
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
class myMatrix:public myVector <myVector <T>> {
public:
    myMatrix(const int n) : myVector <myVector <T>>(n) {}

    void show(myVector<T>& b)
    {
        for (int i = 0; i < this->size; i++)
        {
            for (int j = 0; j < this->size; j++)
                std::cout << this->arr[i][j] << "\t";
            std::cout << b[i];
            std::cout << "\n";
        }
    }

    void Add_arr()
    {
        for (int i = 0; i < this->size; i++)
        {
            this->arr[i].resize(this->size);
            std::cout << "Введите коэфициенты " << i+1 << " уравнения: " << std::endl;
            for (int j = 0; j < this->size; j++)
                std::cin >> this->arr[i][j];
        }        
    }

    void Add_arrRandom()
    {
        std::srand(time(0));
        for (int i = 0; i < this->size; i++)
        {
            this->arr[i].resize(this->size);

            for (int j = 0; j < this->size; j++)
            {
                this->arr[i][j] = std::rand() % 2 + ((std::rand() % 1000)/1000) + 0.1;
            }
        }

        for (int i = 0, j = 0; i < this->size; i++, j++)
        {
            this->arr[i][j] = (this->arr[i][j] + 1) * ((std::rand() % 100 + 1) * 10);
        }
    }

    int max_index(const int j)
    {
        int id = 1;
        for (int i = 0; i < this->size; i++)
            if (this->arr[i][j] > this->arr[id][j])
                id = i;

        return id;
    }

    T* multiply_matrix(myVector<T>& X)                   //перемножение матрицы левого столбца на вектор
    {
        T* tmp = new T [this->size] {0};

        for (int i = 0; i < this->size; i++)
            for (int j = i; j < this->size; j++)
                tmp[i] += (this->arr[i][j] * X[j]);

        return tmp;

        delete[] tmp;
    }

    ~myMatrix() {}
};

template <typename T>
class SLAU: public myMatrix<T>
{
public:
    SLAU(const int _size) :myMatrix<T>(_size) {}

    void swap(int first_id, int second_id, myVector<T>& b)
    {
        myVector <T> tmp(this->size);
        tmp = this->arr[first_id];
        this->arr[first_id] = this->arr[second_id];
        this->arr[second_id] = tmp;

        T _tmp = b[first_id];
        b[first_id] = b[second_id];
        b[second_id] = _tmp;
    }

    void check(myVector<T>& X, myVector<T>& b)                       //проверка правильности решения
    {
        myVector<T> tmp(this->multiply_matrix(X), this->size);

        std::cout << "Погрешность:" << std::endl;
        for (int i = 0; i < this->size; i++)
            std::cout << tmp[i] - b[i] << std::endl;
    }

    void revers_motion(myVector<T>& X, myVector<T>& b)                                 //обратный ход метода Гаусса
    {
        X[this->size-1] = b[this->size-1]; 

        for (int i = this->size - 2; i >= 0; i--)
        {
            X[i] = b[i];
            for (int j = i+1, q = 1; j < this->size; j++, q++)
            {
                X[i] = X[i] - (X[i+q] * (this->arr[i][j]));
            }
        }

        std::cout << "Ответ:" << std::endl;
        for (int i = 0; i < this->size; i++)
            std::cout << "X" << i+1 << " = " << X[i] << std::endl;

        check(X, b);
    }

    void solve(myVector<T>& b) //реализация метода гаусса
    {
        for (int this_i = 0; this_i < this->size; this_i++) // проход по каждому столбцу, проход по каждой строке
        {
            int id = this->max_index(this_i); // нахождение максимального элемента в выбранном столбце

            if (this_i < id)
                this->swap(this_i, id, b); // ставит строку с максимальным элементом наверх

            int tmp = 0;
            for (int i = 1; i < this->size; i++)
            {
                for (int j = 0; j < this->size - 1; j++)
                    if (this->arr[i][j] != 0)
                        tmp = 1;
                if (this->arr[i][this->size - 1] != 0 && tmp == 0)
                    throw std::exception("Система не совместна");
            }

            for (int i = this_i; i < this->size; i++) // делит в каждой строке каждый последующий элемент на выбранный элемент
            {
                if (this->arr[i][this_i] == 0)
                    throw std::exception("Деление на ноль");
                for (int j = this_i + 1; j < this->size; j++)
                {
                    this->arr[i][j] /= this->arr[i][this_i];
                }
                b[i] /= this->arr[i][this_i];
                this->arr[i][this_i] = 1;
            }

            for (int i = this_i + 1; i < this->size; i++) // из всех последующих строчек вычитает выбранную строчку
            {
                for (int j = this_i; j < this->size; j++)
                    this->arr[i][j] -= this->arr[this_i][j];
                b[i] -= b[this_i];
            }
        }
        myVector<T> X(this->size);
        revers_motion(X, b);
    }

    ~SLAU() {}
};

void Input_size(int& size)
{
    std::cout << "Введите количество неизвестных:" << std::endl;
    std::cin >> size;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int size;

    Input_size(size);

    SLAU <double> slu(size);
    myVector <double> b(size);

    slu.Add_arrRandom(); //slu.Add_arr() - для ввода пользователем
    b.Add_vecRandom();   //b.Add_vec() - для ввода пользователем

    std::cout << "Расширенная матрица:" << std::endl;
    slu.show(b);

    try
    {
        slu.solve(b); 
    }
    catch (std::exception& ex)
    {
        std::cout << "ERROR:" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}
