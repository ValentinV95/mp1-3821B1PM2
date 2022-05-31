#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

#define eps    0.00000001

template <typename T>
class MVector {
protected:
	T* arr;
	int size;
public:
	MVector() {}

	MVector(int n) {
		this->size = n;
		this->arr = new T[n];
	}

	MVector(const MVector<T>& other) {
		this->size = other.size;
		this->arr = new T[this->size];
		for (int i = 0; i < this->size;i++) {
			this->arr[i] = other.arr[i];
		}
	}

	void show_vec() {
		for (int i = 0; i < this->size;i++) {
			cout << this->arr[i] << "   ";
		}
		cout << endl;
	}

	int Getsize() { return size; }

	T* Getarr() { return arr; }

	void Add_MVec() {
		cout << "Введите вектор b" << endl;
		for (int i = 0;i < size;i++) { cin >> arr[i]; }
	}

	void RAdd_MVec() {
		srand(time(0));
		for (int i = 0;i < size;i++) {
			arr[i] = (rand() % 100) + ((double)(rand() % 101) / 100.0);
		}
	}

	T& operator[](const int k) { return this->arr[k]; }

	MVector<T> operator+ (const MVector<T>& other) const {
		MVector<T> ans;
		ans.size = this->size;
		ans.arr = new T[this->size];
		for (int i = 0; i < this->size;i++) {
			ans.arr[i] = this->arr[i] + other.arr[i];
		}
		return ans;
	}

	MVector<T>& operator+= (const MVector<T>& other) {
		for (int i = 0; i < this->size;i++) {
			this->arr[i] += other.arr[i];
		}
		return *this;
	}

	MVector<T> operator- (const MVector<T>& other) const {
		MVector<T> ans;
		ans.size = this->size;
		ans.arr = new T[this->size];
		for (int i = 0; i < this->size;i++) {
			ans.arr[i] = this->arr[i] - other.arr[i];
		}
		return ans;
	}

	MVector<T>& operator-= (const MVector<T>& other) {
		for (int i = 0; i < this->size;i++) {
			this->arr[i] -= other.arr[i];
		}
		return *this;
	}

	const T operator* (const MVector<T>& other) const {
		T ans = 0;
		for (int i = 0; i < this->size;i++) {
			ans += this->arr[i] * other.arr[i];
		}
		return ans;
	}

	MVector<T> operator* (T n) {
		MVector<T> ans;
		ans.size = this->size;
		ans.arr = new T[this->size];
		for (int i = 0; i < this->size;i++) {
			ans.arr[i] = this->arr[i] * n;
		}
		return ans;
	}

	const MVector<T>& operator= (const MVector<T>& other) {
		for (int i = 0; i < this->size;i++) {
			this->arr[i] = other.arr[i];
		}
		return *this;
	}

	void Newvec(const int n) {
		this->arr = new T[n];
		for (int i = 0; i < n; i++)
			this->arr[i] = 0;
	}

	~MVector() { delete[] arr; }
};

template <typename T>
class MMatrix :public MVector <MVector<T>> {

public:
	MMatrix() {}

	MMatrix(int n) : MVector <MVector<T>>(n) {
		this->size = n;
		for (int i = 0; i < this->size;i++) {
			this->arr[i].Newvec(this->size);
		}
	}

	void Add_MMat() {
		for (int i = 0;i < this->size;i++) {
			cout << "Введите " << i + 1 << "столбец матрицы" << endl;
			for (int j = 0;j < this->size;j++) {
				cin >> this->arr[i][j];
			}
		}
	}

	void RAdd_MMat() {
		srand(time(0));
		for (int i = 0;i < this->size;i++) {
			this->arr[i].Newvec(this->size);
			for (int j = 0;j < this->size;j++) {
				this->arr[i][j] = rand() % 101 + ((double)(rand() % 101) / 100.0);
			}
		}
		for (int k = 0;k < this->size;k++) {
			this->arr[k][k] = (rand() % 1000) + 100 + ((double)(rand() % 101) / 100.0);
		}
	}

	void Show_mat() {
		for (int i = 0;i < this->size;i++) {
			for (int j = 0;j < this->size;j++) {
				cout << this->arr[i][j] << "   ";
			}
			cout << endl;
		}
	}

	void swap(int i1, int i2, MVector<T>& other) {
		T temp;
		MVector<T> arrtemp(this->size);
		for (int i = 0;i < this->size;i++) {
			arrtemp[i] = this->arr[i1][i];
			this->arr[i1][i] = this->arr[i2][i];
			this->arr[i2][i] = arrtemp[i];
		}
		temp = other[i1];
		other[i1] = other[i2];
		other[i2] = temp;
	}

	void sum(int i1, int i2, MVector<T>& other, T n) {
		for (int i = 0;i < this->size;i++) {
			this->arr[i1][i] += this->arr[i2][i] * n;
		}
		other.arr[i1] += other.arr[i2] * n;
	}

	int maxi(int j) {
		int max = j;
		for (int i = j + 1;i < this->size;i++) {
			if (abs(this->arr[max][j]) < abs(this->arr[i][j])) {
				max = i;
			}
		}
		return max;
	}

	const MMatrix<T>& operator= (const MMatrix<T>& other) {
		if (this->arr != other.arr) {
			for (int i = 0;i < this->size; i++) {
				for (int j = 0;j < this->size;j++) {
					this->arr[i][j] = other.arr[i][j];
				}
			}
		}
		return *this;
	}
};

template <typename T>
class SLAU {
private:
	MVector<T> X;
	MVector<T> b;
	MMatrix<T> A;
	int size;
public:
	SLAU(int size) :A(size), b(size), X(size) {
		int ch;
		cout << "Input 1 for random creation or 2 for creation with keyboard" << endl;
		cin >> ch;
		switch (ch) {
		case 1:
			A.RAdd_MMat(); b.RAdd_MVec();
			break;
		case 2:
			A.Add_MMat(); b.Add_MVec();
			break;
		default:
			cout << "Вы ввели неправильное значение" << endl;
			break;
		}
		this->size = size;
		solve();
	}

	void Show_sist(int size) {
		cout << fixed;
		for (int i = 0;i < size;i++) {
			for (int j = 0;j < size;j++) {
				cout << setprecision(3) << setw(10) << this->A[i][j];
			}
			cout << " | " << setprecision(3) << b[i] << endl;
		}
		cout << "\n\n";
	}

	bool solve() {
		bool fl = 0;
		MVector<T> Nb(b);
		MMatrix<T> NA(size); NA = A;
		if (this->size <= 15) {
			Show_sist(this->size);
		}

		for (int j = 0; j < this->size; j++) {
			T per;
			int maxj = A.maxi(j);
			if (maxj != j) {
				A.swap(maxj, j, b);
				cout << "Поменяли местами местами строки:" << maxj + 1 << " и " << j + 1 << endl;
			}
			for (int i = j + 1; i < this->size; i++) {
				if (A[j][j] == 0)  throw exception("Попытка деления на ноль");
				else { per = (A[i][j] / A[j][j]); }
				for (int l = 0;l < this->size;l++) {
					A[i][l] = A[i][l] - (A[j][l] * per);
				}
				b[i] -= b[j] * per;
			}
			if (this->size <= 15) {
				Show_sist(this->size);
			}
		}

		for (int i = 0;i < this->size;i++) {
			fl = 0;
			for (int j = 0;j < this->size;j++) {
				if (A[i][j] != 0) { fl = 1; }
			}
			if (fl == 0) {
			throw exception("Существует нулевая строка, система являестя несовместной");
			}
			if (A[i][i] == 0) throw exception("На диагонали есть 0, значит решение не одно");
		}
		
		for (int i = 0; i < this->size; i++) { X[i] = 1; }

		for (int i = this->size - 1; i >= 0;i--) {
			double dsx = 0;
			for (int j = i + 1; j < this->size;j++) {
				dsx += A[i][j] * X[j];
			}
			X[i] = (b[i] - dsx) / A[i][i];
		}
		cout << "Вектор X: ";
		X.show_vec();
		cout << "\n";
		Chec_gauss(NA, Nb);
		return true;
	}


	bool Chec_gauss(MMatrix<T>& CA, MVector<T>& Cb) {
		MVector<T> mult(this->size);
		for (int i = 0;i < this->size; i++) {
			T ans = 0;
			for (int j = 0;j < this->size;j++) {
				ans += CA[i][j] * X[j];
			}
			mult[i] = ans;
		}
		for (int i = 0;i < this->size; i++) {
			if (abs(mult[i] - Cb[i]) > eps) {
				return false;
				cout << "Answer is wrong" << "\n";
			}
		}
		cout << "Answer is right" << "\n";
		return true;
	}
};


int main() {
	setlocale(LC_ALL, "Russian");

	int size;
	cout << "Введите размер вектора" << endl;
	cin >> size;
	try {
		SLAU<double> slu(size);
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}