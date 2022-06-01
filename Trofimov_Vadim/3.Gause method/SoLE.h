#pragma once
#include <time.h>

#include "itsMatrix.h"
#define epsilon 0.0000000000001

class SoLE
{
private:
	Matrix<double> A;
	Vector<double> x;
	Vector<double> b;
	int rank_;
public:
	SoLE(int rank, bool doGeneration) : A(rank), x(rank), b(rank) {
		rank_ = rank;
		if (doGeneration == true) {
			double HV = 5, LV = -5;
			std::srand(static_cast <unsigned> (time(NULL)));
			for (int i = 0; i < rank; ++i) {
				b[i] = LV + static_cast <double>(rand() % static_cast <int>((HV-LV)*100)) / 100.0 ;
				for (int j = 0; j < rank; ++j) {
					A[i][j]  = LV + static_cast<double> (rand() % static_cast <int>((HV - LV) * 100)) / 100.0;
				}
				A[i][i] = rank * HV + static_cast<double> (rand() % static_cast <int>((HV - LV) * 100)) / 100.0;
			}
		}
		else {
			std::cin >> A;
			std::cin >> b;
		}
	}
	void Gause(bool doCheckCorrect) {
		Matrix<double> baseA(A);
		Vector<double> baseB(b);
		if (rank_ == 1) { x[0] = b[0] / A[0][0]; }
		for (int k = 1; k < rank_; ++k) {
			double a_max = fabs(A[k - 1][k - 1]); ;
			int i_max = k - 1;
			for (int l = k ; l < rank_; ++l) {
				if (fabs(A[l][k- 1]) > a_max) {
					a_max = fabs(A[l][k- 1]);
					i_max = l;
				}
			}
			A.swap(k - 1, i_max); b.swap(k - 1, i_max);
			for (int j = k; j < rank_; ++j) {
				double m = A[j][k - 1] / A[k - 1][k - 1];
				b[j] -= m * b[k - 1];
				for (int i = 0; i < rank_; ++i) {
					A[j][i] -= m * A[k - 1][i];
				}
			}
			for (int i = rank_ - 1; i >= 0; --i) {
				x[i] = b[i] / A[i][i];
				for (int c = rank_ - 1; c > i; --c) {
					x[i] -= A[i][c] * x[c] / A[i][i];
				}
			}
		}
		std::cout <<"Ansver x:\n"<< x;
		if (doCheckCorrect == true) {
			Vector<double>res = baseA * x;
			res -= baseB;
			double N = sqrt(res * res);
			if (N <= epsilon) { std::cout << "Ansver is correct!\n"; }
			else { std::cout << "Ansver is incorect!\n"; }
			std::cout << "Norm = " << N << "\n\n" << std::endl ;
		}
		system("pause");
	}
};