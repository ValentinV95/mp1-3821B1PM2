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
        std::cout << "create Vector[1]\n";
    }

    myVector(int n)
    {
        this->size = n;
        this->arr = new T[n];
        std::cout << "create Vector\n";
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
        std::cout << "delete vector\n";
        delete[] arr;
    }
};

template <typename T>
class myMatrix:public myVector <myVector <T>> {
private:
    int size_string;
    int size_column;
public:
    myMatrix(const int n) : myVector <myVector <T>>(n)
    {
        size_column = n;
        size_string = 1;
        std::cout << "create matrix\n";
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
        std::cout << "by by\n";
    }

    ~myMatrix()  
    { 
        std::cout << "delete matrix\n";
    }
};

void Input_size(int& size_string, int& size_column)
{
    std::cout << "¬ведите количество неизвестных:" << std::endl;
    std::cin >> size_string;
    size_string++;
    std::cout << "¬ведите количество уравнений:" << std::endl;
    std::cin >> size_column;
}

template <typename T>
void Method_Gaus(myMatrix <T>& slu, const int size_string, const int size_column)                 //прототип дл€ рекурсивного метода гаусса
{
    for (int this_row = 0, this_str = 0; this_str < size_column - 1; this_row++, this_str++)    // проход по каждому столбцу, проход по каждой строке
    {            
        int id = slu.max_index(this_row);         // нахождение максимального элемента в выбранном столбце

        if(this_str != id)                        // ставит строку с максимальным элементом наверх
            slu.swap(this_str, id);
                                
        for (int i = this_str; i < size_column; i++)       // делит в каждой строке каждый последующий элемент на выбранный элемент
            for (int j = this_row; j < size_string; j++)
                slu[i][j] = slu[i][j] / slu[i][this_row];

        for (int i = this_str+1; i < size_column; i++)    // из всех последующих строчек вычитает выбранную строчку
            for (int j = this_row; j < size_string; j++)
                slu[i][j] -= slu[this_str][j];
    } 
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int size_string;
    int size_column;

    Input_size(size_string, size_column);

    myMatrix <double> slu(size_column);

    slu.Add_arr(size_string);

    Method_Gaus(slu, size_string, size_column);
    
    slu.show(); 

    std::cout << "good\n";
}
