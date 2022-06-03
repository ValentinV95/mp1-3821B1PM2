#include "classMatrix.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class SLAU
{
private:
    classMatrix<double> A;
    classVector<double> B;
    classVector<double> X;
    int size;
public:
    SLAU(int size, bool generation) :A(size), X(size), B(size) 
    {
        this->size = size;
        if (generation)
            this->generation(size);
        else
        {
            cin >> A;
            cin >> B;
        }
    }
    classVector<double>& solve() 
    {
        classMatrix<double> _A(A); 
        classVector<double> _B(B);

        if (size <= 10)
        {
            cout << "Матрица:\n\n";
            print();
            cout << "\n\n";
        }
        for (int j = 0; j < size; j++)
        {
            double r;
            int max = j;

            for (int i = j + 1; i < size; i++)
                if (abs(A[max][j]) < abs(A[i][j]))
                    max = i;
            if (j != max)
            {
                A.swap(j, max);
                B.swap(j, max);
            }

            if (A[max][j] == 0)
                cout << "Система несовместна" << endl;
                
            for (int i = j + 1; i < size; i++)
            {
                if (A[j][j] != 0)
                    r = A[i][j] / A[j][j];
                else
                    throw exception("Деление на ноль ");

                A[i] -= A[j] * r;
                B[i] -= B[j] * r;
            }
        }
        for (int i = size - 1; i >= 0; i--)
        {
             double sum = 0;
             for (int j = i + 1; j < size; j++)
                 sum += A[i][j] * X[j];
                  X[i] = (B[i] - sum) / A[i][i];
        }
        if (size <= 10) cout << "X = " << X << endl;
   
        if (prov(_A,_B))
        {
            if (prov(_A, _B))
                cout << "Верно " << endl;
            else
                cout << "Неверно " << endl;
        }
        return X;
    }
    bool prov(classMatrix<double>& _A, classVector<double>& _B)
    {
        classVector<double> mult_res = _A * X; 

        for (int i = 0; i < size; i++)
        {
            if (abs(mult_res[i] - _B[i]) > 0.0000000000001)
                return false;
        }
        return true;
    }
    void print()
    {
        if (size <= 10)
        {
            cout << fixed;
            for (int i = 0; i < size; i++)
            {
                cout << "|";
                for (int j = 0; j < size; j++)
                {
                    cout.width(10);
                    cout << setprecision(5)
                        << A[i][j] << ' ';
                }
                cout << " |";
                cout.width(10);
                cout << setprecision(5)
                    << B[i] << "  |" << '\n';
            }
        }
    }
    void generation(int size)
    {
        double minimal = -10.0;
        double maximal = 10.0;
        srand(700);

        for (int i = 0; i < size; i++)
        {
            B[i] = minimal + (double)(rand()) / (double)(RAND_MAX / (maximal - minimal));
            for (int j = 0; j < size; j++)
            {
                A[i][j] = minimal + (double)(rand()) / (double)(RAND_MAX / (maximal - minimal));
                if (i == j)
                    A[i][j] = size * maximal + (double)(rand()) / (double)(RAND_MAX / (size * maximal));
            }
        }
    }
};




