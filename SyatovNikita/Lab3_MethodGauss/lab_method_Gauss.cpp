// lab_method_Gauss.cpp : реализаци€ метода гаусса ведущим элементом
//

#include <iostream>

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

    T& operator[](const int index)     ////
    {
        return arr[index];
    }

    void operator=(const myVector <T>& a)
    {
        for (int i = 0; i < size; i++)
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
        delete[] arr;
    }
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
            {
                std::cout << this->arr[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    void Add_arr(const int size_str)
    {
        size_string = size_str;
        for (int i = 0; i < size_column; i++)
        {
            this->arr[i].resize(size_string);
            std::cout << "¬ведите коэфициенты " << i+1 << " уравнени€: " << std::endl;
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

    ~myMatrix() {}
};

template <typename T>
class SLAU: public myMatrix<T>
{
public:
    SLAU(const int _size_column) :myMatrix<T>(_size_column) {}

    void solve()                                                    //реализаци€ метода гаусса
    {
        for (int this_row = 0, this_str = 0; this_str < this->size_column; this_row++, this_str++)        // проход по каждому столбцу, проход по каждой строке
        {
            if (this_row < this->size_string)
            {
                int id = this->max_index(this_row);                                                           // нахождение максимального элемента в выбранном столбце

                if (this_str < id)
                    this->swap(this_str, id);                                                                 // ставит строку с максимальным элементом наверх
                    

                for (int i = this_str; i < this->size_column; i++)                                            // делит в каждой строке каждый последующий элемент на выбранный элемент
                {    
                    for (int j = this_row+1; j < this->size_string; j++)
                        this->arr[i][j] /= this->arr[i][this_row];
                    this->arr[i][this_row] = 1;
                }     

                for (int i = this_str + 1; i < this->size_column; i++)                                        // из всех последующих строчек вычитает выбранную строчку
                    for (int j = this_row; j < this->size_string; j++)
                        this->arr[i][j] -= this->arr[this_str][j];
            }
        }
    }

    ~SLAU() {}
};

void Input_size(int& size_string, int& size_column)
{
    std::cout << "¬ведите количество неизвестных:" << std::endl;
    std::cin >> size_string;
    size_string++;
    std::cout << "¬ведите количество уравнений:" << std::endl;
    std::cin >> size_column;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int size_string;
    int size_column;

    Input_size(size_string, size_column);

    SLAU <double> slu(size_column);

    slu.Add_arr(size_string);

    slu.solve();
    
    slu.show(); 
}
