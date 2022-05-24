#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <exception>
#include <conio.h>
double Rasbros = DBL_EPSILON; //процент допустимой погрешности при проверке корректности 10**(-9)%, он нужен так как в проверке используется алгоритм 
                             //подсчета числа b который в случае с числами с плавающей запятой при перемножение может давать погрешность(в том числе и потому-что он не может правильно высчитывать обыкновенные дроби)
using namespace std;
template<class T>class Vecktor
{
public:

    T* mas = new T;
    int size = 1;


    Vecktor(){}
    Vecktor(int n)
    {
        size = n;
        mas = new T[size];
    }
    void resize(int n)
    {
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
        for (int i = 0; i < size; i++)
        {
            mas[i] -= a.mas[i];
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
    void setr(int s)
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
    SLAU(int n):Matrix<T>(n) // Задать значение матрице коэффициентов для СЛАУ и для вектора b, такого что Ax = b, вектор x зануляется
    {
        this->set();
    }
    SLAU(int n,int s) :Matrix<T>(n) // Задать значение матрице коэффициентов для СЛАУ и для вектора b, такого что Ax = b, вектор x зануляется
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
    int Check( Vecktor<T>& B,Matrix<T>& M) // Проверка корректности вектора x с учетом позволенного процента погрешности
    {
        int D = 0;
        Vecktor<T> Check;
        double range = 0;
        Check.resize(this->size);
        bool flg = true;
        for (int i = 0; i < this->size; i++)
        {
            Check.mas[i] = 0;
            for (int j = 0; j < this->size; j++)
            {
                Check.mas[i] += M.mas[i].mas[j] * x.mas[j];
            }
            if (Check.mas[i] > B[i] && Check.mas[i] != 0)
            {
                range = ((Check.mas[i] - B[i]) / (Check.mas[i])) * 100.0;
            }
            else if (Check.mas[i] < B[i] && B[i] != 0)
            {
                range = ((B.mas[i] - Check.mas[i]) / (B.mas[i])) * 100.0;
            }
            else range = 0;
            if (range >= Rasbros)
            {
                flg = false;
                break;
            }
        }
        if (flg) D = 1;
        return D;
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
        B.resize(this->size);
        B = b1;
        b.resize(this->size);
        b = b1;
            for (int i = 0; i < this->size; i++)
            {
                if (this->mas[i].mas[i] == 0)
                {
                    Vecktor<T> tmp;
                    T B;
                    tmp.resize(this->size);
                    for (int j = i + 1; j < this->size; j++)
                    {
                        if (this->mas[j].mas[i] != 0)
                        {
                            B = b.mas[j];
                            b.mas[j] = b.mas[i];
                            b.mas[i] = B;

                            tmp = this->mas[j];
                            this->mas[j] = this->mas[i];
                            this->mas[i] = tmp;
                            break;
                        }
                    }
                }
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
            int correct = Check(B,M);
            if (correct == 0) cout << " x isnot correct" << endl;
            X = x;
    }
};

int main() // Создание СЛАУ с вызовом метода Гаусса, попытка поймать исключение на данном участке
{
    setlocale(LC_ALL, "Russian");

    try {
        int N;
        cout << "Введите размер вашей матрицы одним числом N, размер будет N*N" << endl;
        cin >> N;
        cout << "Не забывайте что коэффициенты пишутся сначала в строку, а не в столбец" << endl;

        SLAU<double> S(N);
        Vecktor<double> b(N);
        Vecktor<double> x(N);
        b.set();

        S.Method_Gaussa(b,x);// присваевает вектору во втором аргументе вектор x из СЛАУ
        cout << endl << "answer x = ";
        x << cout << endl << "Дальше пойдет цикл проверки корректности, будет написано число обозначающее размер проверяемой матрицы" << endl;
        int s = 0;
        int G = _getch();

            while (s<=200)
            {
                srand(s);
                SLAU<double> S(s, 1);
                Vecktor<double> b(s);
                b.setr(s);
                Vecktor<double> x(s);
                S.Method_Gaussa(b, x);
                cout << s << endl << endl;
                s++;
            }
        }catch (exception& e)
        {
            cout << "exception:" << e.what() << endl;
        }
}