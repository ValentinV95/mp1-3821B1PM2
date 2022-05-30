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
    bool solve(bool check) 
    {
        classMatrix<double> OrigA(A); 
        classVector<double> OrigB(B);

        if (size <= 10)
        {
            cout << "Your massiv:\n\n";
            print_system();
            cout << "\n\n";
        }
        for (int j = 0; j < size; j++)
        {
            double alpha;

            int maxJ = j;
            for (int i = j + 1; i < size; i++)
            {
                if (abs(A[maxJ][j]) < abs(A[i][j]))
                    maxJ = i;
            }
            if (j != maxJ)
            {
                A.swap(j, maxJ);
                B.swap(j, maxJ);
                if (size <= 10)
                {
                    cout << "swap " << j + 1 << " with " << maxJ + 1 << "\n\n";
                    print_system();
                    cout << "\n\n";
                }
            }
            if (A[maxJ][j] == 0)
            {
                cout << "System matrix contains zero column!" << endl;
                return false;
            }

            for (int i = j + 1; i < size; i++)
            {
                if (A[j][j] != 0)
                    alpha = A[i][j] / A[j][j];
                else
                    throw exception("attempt to divide by 0");

                A[i] -= A[j] * alpha;
                B[i] -= B[j] * alpha;
            }
        }
        for (int i = size - 1; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < size; j++)
                sum += A[i][j] * X[j];

            X[i] = (B[i] - sum) / A[i][i];
        }
        cout << "X = " << X << endl;
        if (check)
        {
            if (correct_check(OrigA, OrigB))
                cout << "Correctly ";
            else
                cout << "Incorrectly ";
        }
        return true;
    }
    bool correct_check(classMatrix<double>& OrigA, classVector<double>& OrigB)
    {
        classVector<double> mult_res = OrigA * X; 

        for (int i = 0; i < size; i++)
        {
            if (abs(mult_res[i] - OrigB[i]) > 0.0000000000001)
                return false;
        }
        return true;
    }
    void print_system()
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
    void generation(int size)
    {
        double LO = -10.0;
        double HI = 10.0;

        srand(static_cast <unsigned> (time(0)));

        for (int i = 0; i < size; i++)
        {
            B[i] = LO + (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HI - LO))));
            for (int j = 0; j < size; j++)
            {
                A[i][j] = LO + (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HI - LO))));
                if (i == j)
                    A[i][j] = size * HI + (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (size * HI))));
            }
        }
    }
};
