﻿#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <exception>
#include <conio.h>
#include <cmath>
double Rasbros = DBL_EPSILON*100000; //процент допустимой погрешности при проверке корректности 10**(-11), он нужен так как в проверке используется алгоритм 
double procent_error = 0;       //подсчета числа b который в случае с числами с плавающей запятой при перемножение может давать погрешность(в том числе и потому-что он не может правильно высчитывать обыкновенные дроби)
using namespace std;

class Myexception
{
private:
    int k;
public:
    Myexception(int k):k(k){}
    const char* what() const throw()
    {
        const char* d = "unknown_exception";
        if (k == 1) d = "bad_array_new_length";
        if (k == 2) d = "out_of_range";
        if (k == 3) d = "different_lengh_vectors";
            return d;
    }
};
template<class T>class Vecktor
{
public:

    T* mas;
    int size = 0;


    Vecktor(){}
    Vecktor(int n)
    {
        size = n;
        if (size <= 0) throw Myexception(1);
        mas = new T[size];
    }
    void resize(int n)
    {
        if (size != 0)
        delete[]mas;
        mas = new T[n];
        size = n;
    }
    ~Vecktor()
    {
        delete[]mas;
    }

    // Необходимые перегрузки для строчечных преобразований +вывод вектора
    Vecktor& operator=(Vecktor& a)
    {
        size = a.size;
        delete[]mas;
        mas = new T[a.size];
        for (int i = 0; i < a.size; i++)
        {
            mas[i] = a.mas[i];

        }
        return *this;
    } 
    Vecktor& operator*=(T s)
    {
        for (int i = 0; i < size; i++)
        {
            mas[i] *= s;
        }
        return *this;
    }
    Vecktor& operator-=(Vecktor& a)
    {
        if (a.size != size)
        {
            throw Myexception(3);
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                mas[i] -= a.mas[i];
            }
        }
            return *this;
    }
    ostream& operator<<(ostream& out)
    {
        cout << "(";
        for (int i = 0; i < size-1; i++)
        {
            cout << mas[i] << ", ";
        }
        out << "";
        cout << mas[size-1]<< ")";
        return out;
    }

    T operator[](int i)
    {
        if (size <= i) throw Myexception(2);
        return mas[i];
    }

    void set() // Задать значения вектору
    {
        cout << "Введите вектор b" << endl;
        for (int i = 0; i < size; i++)
        {
            cin >> mas[i];
        }
    }
    void setr(int s) // Задает случайные значения вектору
    {
        for (int i = 0; i < size; i++)
        {
            mas[i] = rand()%1000;
        }
    }
};
template<class T>class Matrix : public Vecktor<Vecktor<T>>
{
public:
    Matrix(int n) :Vecktor<Vecktor<T>>(n) // Изменение размеров матрицы созданной автоматически по конструктору унаследованного вектора векторов
    {

        for (int i = 0; i < n; i++)
        {
            this->mas[i].resize(n);
        }
    }
    void set() // Задать значение матрице
    {
        for (int i = 0; i < this->size; i++)
        {
            cout << "Введите строчку коэффициентов номер " << i+1 << endl;
            for (int j = 0; j < this->size; j++)
            {
                cin >> this->mas[i].mas[j];
            }
        }
    }
    ostream& operator<<(ostream& out) // Вывод матрицы
    {
        for (int i = 0; i < this->size; i++)
        {
            for (int j = 0; j < this->size; j++)
            {
                cout << this->mas[i].mas[j] << " ";
            }
            cout << endl;
        }
        out << "" << endl;
        return out;
    }
};
template<class T>class SLAU : public Matrix<T>
{
public:

    Vecktor<T> b;
    Vecktor<T> x;
    SLAU(int n):Matrix<T>(n) // Задать значение матрице при создании
    {
        this->set();
    }
    SLAU(int n,int s) :Matrix<T>(n) // Задает случайные значения матрице при создании
    {
        for (int i = 0; i < n; i++)
        {
            this->mas[i].resize(n);
            for (int j = 0; j < n; j++)
            {
                this->mas[i].mas[j] = rand() % 10;
                if (i == j)
                {
                    this->mas[i].mas[j] = rand() % 100000000000+100000000000.0;
                }
            }
        }
    }
    double Check( Vecktor<T>& B,Matrix<T>& M) // Проверка корректности вектора x с учетом позволенной погрешности "Rasbros"
    {                                         // Возвращает максимально возникшую погрешность превышающую "Rasbros"
        Vecktor<T> Check;
        double maxxrange = 0,range = 0;
        Check.resize(this->size);
        bool flg = true;
        for (int i = 0; i < this->size; i++)
        {
            Check.mas[i] = 0;
            for (int j = 0; j < this->size; j++)
            {
                Check.mas[i] += M.mas[i].mas[j] * x.mas[j];
            }
            range = abs(Check.mas[i] - B[i]);
            if (range >= Rasbros)
            {
                if (range > maxxrange)
                    maxxrange = range;
            }
        }
        return maxxrange;
    }
    void Method_Gaussa(Vecktor<T> &b1,Vecktor<T> &X) 
    {

        Vecktor<T> B;
        x.resize(this->size);
        for (int i = 0; i < this->size; i++)
        {
            x.mas[i] = 0;
        }
        Matrix<T> M(this->size);
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
                M.mas[i].mas[j] = this->mas[i].mas[j];

        b.resize(this->size);
        b = b1;




            for (int i = 0; i < this->size; i++)
            {
                T maxx = this->mas[i].mas[i];
                int maxi = i;
                for (int j = i+1; j < this->size; j++)
                {
                    if (abs(this->mas[j].mas[i]) > maxx)
                    {
                        maxi = j;
                        maxx = this->mas[j].mas[i];
                    }
                }



                    Vecktor<T> tmp1;
                    T B;
                    tmp1.resize(this->size);

                            B = b.mas[maxi];
                            b.mas[maxi] = b.mas[i];
                            b.mas[i] = B;

                            tmp1 = this->mas[maxi];
                            this->mas[maxi] = this->mas[i];
                            this->mas[i] = tmp1;






                if (this->mas[i].mas[i] != 0)
                {
                    Vecktor<T> tmp;
                    tmp.resize(this->size);
                    for (int j = 0; j < i; j++)
                    {
                        if (this->mas[j].mas[i] != 0)
                        {
                            tmp = this->mas[i];
                            tmp *= this->mas[j].mas[i] / this->mas[i].mas[i];
                            b.mas[j] -= b.mas[i] * this->mas[j].mas[i] / this->mas[i].mas[i];
                            this->mas[j] -= tmp;
                        }
                    }
                    for (int j = i + 1; j < this->size; j++)
                    {
                        if (this->mas[j].mas[i] != 0)
                        {
                            tmp = this->mas[i];
                            tmp *= this->mas[j].mas[i] / this->mas[i].mas[i];
                            b.mas[j] -= b.mas[i] * this->mas[j].mas[i] / this->mas[i].mas[i];
                            this->mas[j] -= tmp;
                        }
                    }
                }
            }
            int k,flg = 0;
            for (int i = this->size - 1; i >= 0; i--)
            {
                k = 0;
                for (int j = 0; j < this->size; j++)
                {
                    if (this->mas[i].mas[j] != 0) k++;
                }
                if (k == 0) flg = 1;
                if (k == 0 && b.mas[i] != 0)
                {
                    cout << "( ";
                    this->mas[i] << cout <<" | " << b.mas[i] << " ) СЛАУ не совместна!";

                }
                x.mas[i] = b.mas[i];
                for (int j = this->size - 1; j >= 0; j--)
                {
                    if (j != i)
                    {
                        x.mas[i] -= this->mas[i].mas[j] * x.mas[j];
                    }
                }
                if (this->mas[i].mas[i] != 0)
                x.mas[i] /= this->mas[i].mas[i];
            }
            double max_pogresh = Check(b1,M);
            if (max_pogresh > 0)
            {
                cout << "x isnot correct on " << max_pogresh << endl;
                procent_error++;
            }
            X = x;
    }
};

int main() // Создание СЛАУ с вызовом метода Гаусса, попытка поймать исключение на данном участке
{


    setlocale(LC_ALL, "Russian");
    try {

        //Vecktor<double> s1(3),s2(4);s1.setr(2);s2.setr(3);s1 << cout;s2 << cout;s1 -= s2;s1 << cout;s2 << cout;               //для проверки исключения при вычитании векторов разных размеров

        int N;
        cout << "Введите размер вашей матрицы одним числом N, размер будет N*N" << endl;
        cin >> N;






        //N -= 2*N;                              //для проверки исключения вызванного при создании массива с отрицательным размером(размер СЛАУ поменяется, выведет исключение сразу после указания размера СЛАУ)
        
        
        
        
        SLAU<double> S(N);
        Vecktor<double> b(N);
        Vecktor<double> x(N);

        b.set();



        //cout << x[x.size];                     //для проверки исключения выхода за границы массива(выведет исключения после заполнения СЛАУ)




        S.Method_Gaussa(b,x);// присваевает вектору во втором аргументе вектор x из СЛАУ
        cout << endl << "answer x = ";
        x << cout << endl << "Дальше пойдет цикл проверки корректности, будет написано число обозначающее размер проверяемой матрицы(нажмите любую кнопку)" << endl;
        int s = 1;
        int G = _getch();
            while (s<=300) // Проверил для 0 < s <= 1000, с данной погрешностью все решения верны.
            {
                srand(s*rand()%23);
                SLAU<double> S(s, 1);
                Vecktor<double> b(s);
                b.setr(s);
                Vecktor<double> x(s);
                S.Method_Gaussa(b, x);
                cout << "Решена матрица размера " << s << endl << endl;
                s++;
            }
            procent_error = procent_error / s * 100;
            cout << endl << procent_error << "% Случаев из "<< s-1 << " решений когда погрешность превышала " << Rasbros  << endl;
        }catch (Myexception& e)
        {
            cout << "\n\nexception:" << e.what() << endl;
        }
}