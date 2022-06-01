#include <iostream>
#include "SLAU.h"

using namespace std;


int main() {
	int dimension;

	cout << "please enter dimension of matrix and vector: ";
	cin >> dimension;

	int choice = 1;
	bool random_fill;
	while (choice) {
		cout << "Please choose filling method for matrix A and vector b: \n\n 1 - Random\n 2 - Manual\n\nPlease enter the number: ";
		cin >> choice;

		if (choice == 1) {
			random_fill = true;
			choice = 0;
		}
		else if (choice == 2) {
			random_fill = false;
			choice = 0;
		}
		else {
			cout << "Error! Invalid number of filling method" << endl;
		}
	}

	try {
		SLAU<double> A(dimension);
		my_vector<double> b(dimension);

		if (random_fill) {
			for (int i = 0; i < dimension; ++i) {
				A[i].random_fill(i);
			}
			b.random_fill(dimension);
		}
		else {
			cout << "\nManual filling: A(row, column)" << endl;

			for (int i = 0; i < dimension; ++i) {
				for (int j = 0; j < dimension; ++j) {
					cout << "A(" << i + 1 << ',' << j + 1 << "): ";
					cin >> A[i][j];
				}
			}

			for (int i = 0; i < dimension; ++i) {
				cout << "b(" << i + 1 << "): ";
				cin >> b[i];
			}
		}

		cout << "\nYour matrix:\n" << endl;

		for (int i = 0; i < dimension; ++i) {
			cout << "| ";

			for (int j = 0; j < dimension + 1; ++j) {
				if (j != dimension) {
					cout << A[i][j] << '\t';
				}
				else {
					cout << "| " << b[i];
				}
			}

			cout << "| ";
			cout << "\n" << endl;
		}

		A.resolve(b);
	}
	catch (const char* exception) {
		cout << exception << endl;
	}

	return 0;
}