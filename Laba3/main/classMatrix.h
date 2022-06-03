#include"classVector.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
class classMatrix : public classVector<classVector<T>>
{
public:
    int get_size()
    {
        return this->size;
    }
    
    classMatrix(int size) : classVector<classVector<T>>(size)
    {
        for (int i = 0; i < size; i++)
        {
            this->vector[i].resize(size);
        }
    }
    classMatrix(classMatrix& mas) :classVector<classVector<T>>(mas.get_size())
    {
        for (int i = 0; i < this->size; i++)
        {
            this->vector[i] = mas[i];
        }
    }

    const classVector<T> operator * (classVector<T>& other)
    {
        classVector<T> res(this->size);
        for (int i = 0; i < this->size; i++)
        {
            res[i] = this->vector[i] * other;
        }
        return res;
    }
    classVector<T>& operator [](int index)
    {
        return this->vector[index];
    }
};

template<class T>
istream& operator >> (istream& in, classMatrix<T>& mat)
{
    for (int i = 0; i < mat.get_size(); i++)
    {
        for (int j = 0; j < mat.get_size(); j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> mat[i][j];
        }
    }
    return in;
}

template<class T>
ostream& operator << (ostream& out, classMatrix<T>& Matrix)
{
    cout << fixed;
    for (int i = 0; i < Matrix.get_size(); i++)
    {
        cout << "|";
        for (int j = 0; j < Matrix.get_size(); j++)
        {
            cout.width(10);
            cout << setprecision(5)
                << Matrix[i][j] << ' ';
        }
        cout << " |";
        cout.width(10);
        cout << setprecision(5) << "\n";

    }
    cout << "\n\n";
    return out;
}

