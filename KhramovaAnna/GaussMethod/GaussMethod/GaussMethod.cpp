#include <iostream>
#include <exception>
#include <locale.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

template <typename T>
class myvector {
protected:
	T* mas;
	int size;
public:
	myvector(int size=5) {
		this->size = size;
		mas = new T[size];
	}
	myvector(const myvector& vec) {
		this->size = vec.size;
		mas = new T[size];
		for (int i = 0; i < size; i++) {
			mas[i] = vec.mas[i];
		}
	}

	myvector(int size, T num) {
		this->size = size;
		mas = new T[size];
		for (int i = 0; i < size; i++)
			mas[i] = num;
	}
	myvector operator +(const myvector& vec) {
		if (this->size != vec.size) throw exception("vectors have different dimensions");
		myvector res(size);
		for (int i = 0; i < size; i++)
			res.mas[i] = this->mas[i] + vec.mas[i];
		return res;
	}

	T operator*(const myvector& vec) {
		T result_of_scal = 0;
		if (this->size == vec.size) {
			for (int i = 0; i < vec.size; i++) {
				result_of_scal = result_of_scal + ((this->mas[i]) * vec.mas[i]);
			}
			return result_of_scal;
		}

		else {
			throw exception("vectors have different dimensions");
		}
	}
	myvector operator -(const myvector& vec) {
		if (this->size != vec.size) throw exception("vectors have different dimensions"); //СЂР°Р·РЅС‹Р№ СЂР°Р·РјРµСЂ РІРµРєС‚РѕСЂРѕРІ
		myvector res(size);
		for (int i = 0; i < size; i++)
			res.mas[i] = this->mas[i] - vec.mas[i];
		return res;
	}
	myvector operator*(const T& num) {
		myvector res(size);
		for (int i = 0; i < size; i++)
			res.mas[i] = this->mas[i] * num;
		return res;
	}

	myvector operator/ (const T& num) {
		myvector res(size);
		for (int i = 0; i < size; i++)
			res.mas[i] = this->mas[i] / num;
		return res;
	}
	myvector& operator+= (const myvector& vec) {
		if (this->size != vec.size) throw exception("vectors have different dimensions");

		for (int i = 0; i < size; i++)
			mas[i] += vec.mas[i];

		return *this;
	}

	myvector& operator-= (const myvector& vec) {
		if (this->size != vec.size) throw exception("vectors have different dimensions");

		for (int i = 0; i < size; i++)
			mas[i] -= vec.mas[i];

		return *this;
	}
	myvector& operator =(const myvector& vec) {
		if (this->size != vec.size) {
			this->size = vec.size;
			delete[] mas;
			mas = new T[size];
		}
		for (int i = 0; i < size; i++) {
			mas[i] = vec.mas[i];
		}
		return *this;
	}
	T& operator [](int i) {
		return mas[i];
	}
	~myvector() {
		delete[] mas;
	}

	int get_size() {
		return size;
	}
	void resize(int new_size) {
		size = new_size;
		delete[] mas;
		mas = new T[size];
	}
	void random() {
		srand(777);
		for (int i = 0; i < size; i++)
			mas[i] = rand() / 1000;

	}
	void swap(int a, int b)
	{
		T temp;
		temp = mas[a];
		mas[a] = mas[b];
		mas[b] = temp;
	}
};
template <class T>
ostream& operator<< (ostream& ost, myvector <T>& vec) {
	cout << "[";
	for (int i = 0; i < vec.get_size() - 1; i++) {
		cout << vec[i] << "\t";
	}
	cout << vec[vec.get_size() - 1] << "]\n";
	cout << "\n";
	return ost;
}
template <class T>
istream& operator>> (istream& ist, myvector<T>& vec) {
	for (int i = 0; i < vec.get_size(); i++) {
		cout << "b[" << i + 1 << "] = ";
		cin >> vec[i];
	}
	return ist;
}

template <typename T>
class mymatrix : public myvector<myvector<T>> {
public:
	mymatrix(int size) : myvector<myvector<T>>(size) {
		this->size = size;
		for (int i = 0; i < size; i++) {
			this->mas[i].resize(size);
		}
	}
	mymatrix(mymatrix& matr) :myvector<myvector<T>>(matr.get_size())
	{
		for (int i = 0; i < this->size; i++)
		{
			this->mas[i] = matr[i];
		}
	}
	myvector<T>& operator[](int i) {
		return this->mas[i];
	}

	myvector<T> operator*(myvector<T>& vec) {
		myvector<T> res(this->size);
		for (int i = 0; i < this->size; i++)
			res[i] = this->mas[i] * vec;
		return res;
	}
	void random() {
		srand(time(NULL));
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				this->mas[i][j] = rand() / 1000;
			}
		}
	}
	void Print() {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++)
				cout << this->mas[i][j];
			cout << endl;
		}
	}
};

template <class T>
ostream& operator<< (ostream& ost, mymatrix <T>& matr) {
	cout << "[";
	for (int i = 0; i < matr.get_size(); i++) {
		for (int j = 0; j < matr.get_size(); j++)
			cout << matr[i][j] << "\t";
	}
	cout << "\n\n";
	return ost;
}
template <class T>
istream& operator>> (istream& ist, mymatrix<T>& matr) {
	for (int i = 0; i < matr.get_size(); i++) {
		for (int j = 0; j < matr.get_size(); j++) {
			cout << "A[" << i + 1 << "][" << j + 1 << "] =  ";
			cin >> matr[i][j];
		}
	}
	return ist;
}

class SLAU
{
private:
	mymatrix<double> matr;
	myvector<double> otvet;
	myvector<double> vec;
	int size;
public:
	SLAU(int size, bool random) :matr(size), otvet(size), vec(size) {
		this->size = size;
		if (random == 1) {
			this->vec.random();
			this->matr.random();
		}
		else {
			cin >> vec;
			cin >> matr;
		}
	}
	bool solve() { 
		mymatrix<double> A(matr); 
		myvector<double> B(vec);

		if (size <= 8) {
			cout << "Your SLAU\n\n";
			Print();
			cout << "\n\n";
		}
		for (int j = 0; j < size; j++) {
			double alpha;

			int maxJ = j;
			for (int i = j + 1; i < size; i++) {
				if (abs(matr[maxJ][j]) < abs(matr[i][j]))
					maxJ = i;
			}
			if (j != maxJ) {
				matr.swap(j, maxJ);
				vec.swap(j, maxJ);
				if (size <= 10) {
					cout << "swap " << j + 1 << " with " << maxJ + 1 << "\n\n";
					Print();
					cout << "\n\n";
				}
			}
			if (matr[maxJ][j] == 0) {
				cout << "System matrix contains zero column!" << endl;
				return false;
			}

			for (int i = j + 1; i < size; i++) {
				if (matr[j][j] != 0)
					alpha = matr[i][j] / matr[j][j];
				else
					throw exception("division on zero");

				matr[i] -= matr[j] * alpha;
				vec[i] -= vec[j] * alpha;
			}
			if (size <= 8) {
				cout << "Step " << j + 1 << ":\n";
				Print();
				cout << "\n\n";
			}
		}
		for (int i = size - 1; i >= 0; i--) {
			double summ = 0;
			for (int j = i + 1; j < size; j++)
				summ += matr[i][j] * otvet[j];

			otvet[i] = (vec[i] - summ) / matr[i][i];
		}
		cout << "Otvet = " << otvet << endl;

		if (check(A, B))
			cout << "correctly ";
		else
			cout << "incorrectly ";

		return true;
	}
	bool check(mymatrix<double>& A, myvector<double>& B) {
		myvector<double> mult_res = A * otvet; 

		for (int i = 0; i < size; i++) {
			if (abs(mult_res[i] - B[i]) > 0.0000000000001)
				return false;
		}
		return true;
	}
	void Print() {
		for (int i = 0; i < size; i++) {
			cout << "|";
			for (int j = 0; j < size; j++) {
				cout.width(10);
				cout << matr[i][j] << ' ';
			}
			cout << " |";
			cout.width(10);
			cout << vec[i] << "  |" << '\n';
		}
	}

};

int main() {
	int size;
	bool Rand;

	cout << "enter size" << endl;
	cin >> size;
	cout << "enter 1 for random completion, enter 0 for self-completion" << endl;
	cin >> Rand;
	cout << endl;

	SLAU G(size, Rand);

	try {
		if (G.solve())
			cout << "Solved!" << endl;
	}
	catch (exception& ex)
	{
		cout << "ERROR!" << ex.what() << "\n\n";
	}

}
