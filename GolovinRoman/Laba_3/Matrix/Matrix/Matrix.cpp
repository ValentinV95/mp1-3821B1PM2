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

template<typename T = double> 
class Container
{
private:
    unsigned int length, last;
    T *data;
public:
	Container(unsigned int length=1)
    {
        if (length)
        {
			this->length = length;
			last = 0;
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
        this->last = c.last;

        data = new T[this->length];
        for (unsigned int i=0;i< this->length;++i)
        {
            this->data[i] = c.data[i];
        }
    }

    ~Container()
    {
        delete[] data;
        last = 0;
        length = 0;
    }

    void append(const T &a)
    {
        if (length==last)
        {
            T *tmp = new T[length * 2];
            for (unsigned int i=0;i<last;++i)
            {
                tmp[i] = data[i];
            }
            delete[] data;
            length *= 2;
            data = tmp;
        }

		data[last] = a;
		last++;
    }

    void swap(unsigned int first,unsigned int second)
	{
		if (first < last || second < last)
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

    void addData(unsigned int first, unsigned int second, double k)
    {
        if (first<last || second<last)
        {
			T tmp = data[second];
			tmp *= k;
			data[first] += tmp;
        }
        else
        {
            throw std::out_of_range("Index out of range in addData(unsigned int first, unsigned int second, double k)");
        }
    }

    unsigned int getLength() const {return last;}

    T const &operator [](int ind) const {return data[ind];} 

    T &operator [](int ind) { return data[ind]; }

    void operator +=(const Container<T> &c)
    {
        if (c.last==last)
        {
            for (int i=0;i<last;++i)
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

    Container<T> &operator *=(const T c)
    {
        for (int i=0;i<length;++i)
        {
            data[i] *= c;
            if(fabs(data[i]) < eps)
            {
                data[i] = 0.0;
            }
        }

        return *this;
    }

    T operator *(const Container<T> &c) const
    {
        T res = 0;
        for (int i = 0; i < last; ++i)
        {
            res +=this->data[i] * c.data[i];
        }

        if (std::fabs(res)<eps)
        {
            res = 0.0;
        }

        return res;
    }

    Container operator =(const Container &c)
    {
        if (&(*this) != &c)
        {
			length = c.length;
			last = c.last;

			delete[] data;

			data = new T[c.length];

			for (unsigned int i = 0; i < c.last; ++i)
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

    Container<T> operator *(const Container<T> &m) const
    {
        Matrix res;

        for (unsigned int i=0;i<m.getLength();i++)
        {
            res.Add(Matrix::operator[](i)*m);
        }

        return res;
    }

    void append(const Container<T>& c)
    {
        if (this->getHeight())
        {
            if (Matrix::operator[](0).getLength() == c.getLength())
            {
                Matrix::Container::append(c);
            }
            else
            {
                throw std::exception("All rows of the matrix must be the same length");
            }
        }
        else
        {
            Matrix::Container::append(c);
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
        X.addData(first, second, k);
        A1.addData(first, second, k);
    }

    void swap(unsigned int first, unsigned int second)
    {
		A1.swap(first, second);
		X.swap(first, second);
    }
public:
    SLAE(){}

    SLAE(Matrix<double> A,Container<double> B)
    {
		this->A = A;
        this->A1 = A;
		this->B = B;
        X = B;

        printSist();
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
				A1[g - 1] *= (1 / A1[g - 1][g - 1]);
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
				Container<double> tmp;
				double sum = 0;
				for (int j = 0; j < size - 1; j++)
				{
					double rnd = min + std::fmod(rand(), (max - min));
					sum += fabs(rnd);
					tmp.append(rnd);
				}
				tmp.append(sum + 1);
				tmp.swap(i, size - 1);
				A.append(tmp);
			}

			A1 = A;

			for (int i = 0; i < size; i++)
			{
				B.append(min + std::fmod(rand(), (max - min)));
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
    SLAE sl;
    unsigned int size;
    std::cout << "Enter size ";
    std::cin >> size;
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
