#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <iomanip>

/////////////////////////////////////////////////////////////////////
//                    Created by Golovin Roman                     //
//                      License K.S.T.P.E.                         //
/////////////////////////////////////////////////////////////////////

double eps = 0.0000000000001;

template<class T = double> 
class Container
{
private:
    unsigned int length;
    T *data = nullptr;
public:
	Container(unsigned int length=1):length(length)
    {
        if (length)
        {
			this->length = length;
			data = new T[this->length];
        }
        else
        {
            throw std::exception("Length may not be equal to zero");
        }
    }

    Container(const Container &c) 
    {
        this->length = c.length;

        data = new T[this->length];
        for (unsigned int i=0;i<this->length;++i)
        {
            this->data[i] = c.data[i];
        }
    }

    ~Container()
    {
        delete[] data;
        length = 0;
    }

    void resize(unsigned int newSize)
    {
        if (newSize)
        {
            T* tmp = new T[newSize]{0};
			length = newSize;
			for (unsigned i = 0; i < length; i++)
			{
				tmp[i] = data[i];
			}
            delete[] data;
            data = tmp;
        }
        else
        {
            throw std::exception("New size may not be equal to 0");
        }
    }

    void swap(unsigned int first,unsigned int second)
	{
		if (first < length || second < length)
		{
			if (first != second)
			{
				T tmp = data[first];
				data[first] = data[second];
				data[second] = tmp;
			}
		}
		else
		{
			throw std::out_of_range("Index out of range in swap(unsigned int first,unsigned int second)");
		}
	}

    unsigned int getLength() const {return length;}

    const T &operator [](int ind) const {return data[ind];} 

    T& operator[](int ind) { return data[ind]; }

    void operator +=(const Container<T> &c)
    {
        if (c.length==length)
        {
            for (int i=0;i<length;++i)
            {
                data[i] += c.data[i];
                if(fabs(data[i]) < eps)
                {
                    data[i] = 0.0;
                }
            }
        }
        else
        {
            throw std::invalid_argument("Vectros length are not the same");
        }
    }

    Container<T> operator *(const T c)
    {
        Container<T> res(length);
        for (int i=0;i<length;++i)
        {
            res[i] = data[i]*c;
            if(fabs(res[i]) < eps)
            {
                res[i] = 0.0;
            }
        }

        return res;
    }

    T operator *(const Container<T> &c) const
    {
        T res = 0;
        for (int i = 0; i < length; ++i)
        {
            res += this->data[i] * c.data[i];
        }

        if (std::fabs(res)<eps)
        {
            res = 0.0;
        }

        return res;
    }

    Container<T> operator =(const Container<T> &c)
    {
        if (&(*this) != &c)
        {
			length = c.length;
			delete[] data;
			data = new T[c.length];

			for (unsigned int i = 0; i < c.length; ++i)
			{
				data[i] = c.data[i];
			}
        }

        return c;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& strm,const Container<T> &c)
{
    unsigned int length = c.getLength();
    for (unsigned int i = 0; i < length;++i)
	{
		std::cout << std::setprecision(3) << std::setw(5) << c[i] <<' ';
	}

	return strm;
}

template<typename T = double>
class Matrix:public Container<Container<typename T>>
{
public:
    Matrix(unsigned int height):Container<Container<T>>(height)
    {
        for (unsigned int i=0;i<height;i++)
        {
            this->operator[](i).resize(height);
        }
    }

    unsigned int getColumnMaxInd(unsigned int columnInd) const
    {
        unsigned int res = columnInd;
        for (unsigned int i = columnInd;i<getHeight();i++)
        {
            if (std::fabs(Matrix::operator[](i)[columnInd]) > std::fabs(Matrix::operator[](res)[columnInd]))
            {
                res = i;
            }
        }

        if (Matrix::operator[](res)[columnInd])
        {
            return res;
        }
        else
        {
            return -1;
        }
    }

    unsigned int getHeight() const { return this->getLength();}

    unsigned int getWidth() const { return this->operator[](0).getLength();}

    Container<T> const &operator [](int ind) const {return Matrix::Container::operator[](ind);}

    Container<T> &operator [](int ind) {return Matrix::Container::operator[](ind);}

    const Matrix<T> &operator =(const Matrix<T> &m)
    {
        Matrix::Container::operator=(m);
        return *this;
    }
};

template<typename T>
std::ostream& operator <<(std::ostream& strm, const Matrix<T> &c)
{
    std::cout <<"\n";
    unsigned int length = c.getLength();
    for (unsigned int i = 0; i < length;++i)
    {
        std::cout << c[i] <<"\n";
    }

    std::cout << "\n";

    return strm;
}

//System of linear algebraic equations
class SLAE
{
private:
    Matrix<double> A;
    Matrix<double> A1;

    Container<double> B;
    Container<double> X;
    bool solved = false;

    void addStr(unsigned int first, unsigned int second, double k)
    {
        X[first] += X[second] * k;
        A1[first] += A1[second] * k;
    }

    void swap(unsigned int first, unsigned int second)
    {
		A1.swap(first, second);
		X.swap(first, second);
    }
public:
    SLAE(unsigned int size):A(size),A1(size),B(size),X(size)
    {
        if (size > 2147483647)
        {
            throw std::invalid_argument("Size is to big");
        }
    }

    void solveByGauss()
    {
        unsigned int h = A1.getHeight(), w = A1.getWidth();
        if (h && w && B.getLength())
        {
			for (unsigned int g = 0; g < w; ++g)
			{
				int maxInd = A1.getColumnMaxInd(g);
                if (maxInd==-1)
                {
                    std::cout << "The system has no solutions";
                    return;
                }
				swap(g,maxInd);

				if (A1[g][g])
				{
					for (unsigned int i = g + 1; i < h; ++i)
					{
						if (A1[i][g])
						{
							addStr(i, g, (A1[i][g] / A1[g][g]) * (-1.0));
						}
					}
                }
                else
                {
                    std::cout << "The system has more than one solution";
                    return;
                }
			}

			for (unsigned int g = h; g >= 1; --g)
			{
				for (unsigned int i = g - 1; i >= 1; --i)
				{
					if (A1[i - 1][g - 1])
					{
						addStr(i - 1, g - 1, (A1[i - 1][g - 1] / A1[g - 1][g - 1]) * (-1.0));
					}
				}
				X[g - 1] = X[g - 1] * (1 / A1[g - 1][g - 1]);
                A1[g - 1] = A1[g - 1] * (1 / A1[g - 1][g - 1]);
			}
        }
        else
        {
            throw std::exception("System is not initialized");
        }

        solved = true;
    }

    void printChek()
	{
		if (solved)
		{
			printSist();
			std::cout << "\n";

			std::cout << "A*X" << "\n";
			for (unsigned int i = 0; i < A1.getHeight(); i++)
			{
				double ax = A[i] * X;
				std::cout << std::setprecision(3) << std::setw(5) << ax;
				if (fabs(ax - B[i]) <= eps)
				{
					std::cout << std::setprecision(3) << std::setw(5) << "|A[i]*X - B[i] " << std::setprecision(3) << std::setw(5) << ax - B[i] << " |Correct \n";
				}
				else
				{
					std::cout << " |Wrong\n";
					return;
				}
			}
        }
        else
        {
            throw std::exception("The system has not been resolved");
        }
    }
    
	void printSist()
	{
        if (A.getHeight()<20 && A.getWidth()<20)
        {
			std::cout << "Orig syst " << '\n';
			for (int i = 0; i < A.getHeight(); i++)
			{
				std::cout << A[i] << "|" << B[i] << std::endl;
			}
			std::cout << '\n';

            std::cout << "The unit matrix " << '\n';
            for (int i = 0; i < A.getHeight(); i++)
            {
                std::cout << A1[i] << "|" << X[i] << std::endl;
            }
            std::cout << '\n';
        }
        else
        {
            std::cout << '\n' <<"System is to big to be printed" << '\n';
        }
	}

    void setRandomSyst(unsigned int size)
    {
        if (size < 2147483647)
        {
			srand(time(NULL));

			double min = -10.0, max = 10.0;

			for (int i = 0; i < size; i++)
			{
				Container<double> tmp(size);
				double sum = 0;
				for (int j = 0; j < size - 1; j++)
				{
					double rnd = min + std::fmod(rand(), (max - min));
					sum += fabs(rnd);
                    tmp[j] = rnd;
				}
				tmp[size - 1] = sum + 1;
				tmp.swap(i, size - 1);
				A[i] = tmp;
			}

			A1 = A;

			for (int i = 0; i < size; i++)
			{
				B[i] = min + std::fmod(rand(), (max - min));
			}

			X = B;

			solved = false;
        }
        else
        {
            throw std::invalid_argument("Size is to big");
        }
    }
};

int main()
{
    unsigned int size;
    std::cout << "Enter size ";
    std::cin >> size;
    SLAE sl(size);
	try
	{
		sl.setRandomSyst(size);
		sl.solveByGauss();
		sl.printChek();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
}
