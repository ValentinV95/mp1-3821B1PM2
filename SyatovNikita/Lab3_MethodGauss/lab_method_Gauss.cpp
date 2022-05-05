// lab_method_Gauss.cpp : реализаци€ метода гаусса ведущим элементом
//

#include <iostream>
#include <stdio.h>

template <typename T>
class myVector {
public:
    int size;
    T* arr;
public:
    myVector(int n)
    {
        size = n;
        arr = new T(size);
    }

    T& operator[](const int index)     ////
    {
        return arr[index];
    } 

    void resize(const int _size)
    {
        delete[] arr;
        this->size = _size;
        arr = new T(size);
    }

    ~myVector() {  }
};

template <typename T>
class myMatrix:public myVector <myVector <T>> {
private:
    int size_string;
    int size_column;
public:
    myMatrix(const int m,const int n) : myVector <myVector <T>>(n)
    {
        size_column = n;
        size_string = m;
        for (int i = 0; i < size_column; i++)
            this->arr[i].resize(size_string);
    }

    int max_index(const int& j)
    {
        int id = 1;
        for (int i = 0; i < size_column; i++)
            if (this->arr[i][j] > this->arr[id][j])
                id = i;

        return id;
    }

    ~myMatrix() 
    {
        for (int i = 0; i < size_column; i++)
            delete this->arr[i].arr;
        delete this->arr;
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
void Input_arr(myMatrix <T>& slu, const int size_string, const int size_column)
{
    for (int i = 0; i < size_column; i++)
    {
        //std::cout << "¬ведите коэфициенты " << i+1 << " уравнени€: " << std::endl;
        printf("¬ведите коэфициенты %i уравнени€:\n", i+1);
        for (int j = 0; j < size_string; j++)
            //std::cin >> slu[i][j];
            scanf_s("%lf", &slu[i][j]);
    }        
}



template <typename T>
void swap(myMatrix <T>& slu, int first_id, int second_id)
{
    myVector <T> tmp = slu[first_id];
    slu[first_id] = slu[second_id];
    slu[second_id] = tmp;
}

template <typename T>
void Method_Gaus(myMatrix <T>& slu, const int size_string, const int size_column)                 //прототип дл€ рекурсивного метода гаусса
{
    for (int k = 0; k < size_string; k++)
    {
        //int id = slu.max_index(k);
        int id = 0;
        swap(slu, k, id);

        for (int i = 0; i < size_column; i++)
            for (int j = 0; j < size_string; j++)
                slu[i][j] = slu[i][j] / slu[i][k];

        for (int i = 1; i < size_column; i++)
            for (int j = 0; j < size_string; j++)
                slu[i][j] -= slu[k][j]; 
    } 
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int size_string;
    int size_column;
    Input_size(size_string, size_column);
    myMatrix <double> slu(size_string, size_column);
    Input_arr(slu, size_string, size_column);

    //Method_Gaus(slu, size_string, size_column);

    for (int i = 0; i < size_column; i++)
    {
        for (int j = 0; j < size_string; j++)
            printf("%lf\t", slu[i][j]);
        printf("\n");
    } 

    std::cout << "good";
}
