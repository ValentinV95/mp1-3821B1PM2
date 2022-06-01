#include <iostream>
#include "my_matrix.h"

using namespace std;

template<typename T>
class SLAU : public my_matrix<T> {
private:
	void create_tmp_copy(my_matrix<T>& tmp_copy) {
		for (int i = 0; i < this->size; ++i) {
			for (int j = 0; j < this->size; ++j) {
				tmp_copy[i][j] = this->xy[i][j];
			}
		}
	}

	void check_function(my_matrix<T>& A, my_vector<T>& b, my_vector<T>& x) {
		bool check = true;
		T check_x;
		for (int i = 0; i < this->size; ++i) {
			check_x = 0;
			for (int j = 0; j < this->size; ++j) {
				check_x += x[j] * A[i][j];
			}
			if (fabs(b[i] - check_x) > 0.0000000001) {
				cout << "Oh, no! The solution is incorrect" << endl;
				check = false;
				break;
			}
		}

		if (check) {
			cout << "Congratulations!!! The solution is correct!!!" << endl;
		}
	}

public:
	SLAU(int SLAU_size = 1) : my_matrix<T>(SLAU_size) {

	}

	void resolve(my_vector<T>& b) {
		for (int i = 0; i < this->size; ++i) {
			if (this->xy[i][i] == 0) {
				cout << "SLAU has not  one solutions" << endl;
				return;
			}
		}

		int max_row;
		my_matrix<T> A_tmp_copy(this->size);
		create_tmp_copy(A_tmp_copy);
		my_vector<T> b_tmp_copy(b);
		my_vector<T> x(this->size);

		for (int column = 0; column < this->size; ++column) {
			max_row = column;
			for (int row = column + 1; row < this->size; ++row) {
				if (fabs(this->xy[max_row][column]) < fabs(this->xy[row][column])) {
					max_row = row;
				}
			}

			if (column != max_row) {
				T tmp;
				my_vector<T> tmp_vector;

				tmp = b[column];
				b[column] = b[max_row];
				b[max_row] = tmp;

				tmp_vector = this->xy[column];
				this->xy[column] = this->xy[max_row];
				this->xy[max_row] = tmp_vector;
			}

			for (int row = column; row < this->size; row++) {
				for (int column_tmp = this->size; column_tmp > column - 1; --column_tmp) {

					if (this->xy[row][column] == 0) {
						throw "\nError! Null column or null row";
					}
					else {
						if (column_tmp == this->size) {
							b[row] /= this->xy[row][column];
						}
						else {
							this->xy[row][column_tmp] /= this->xy[row][column];
						}
					}

				}
			}

			if (column < this->size - 1) {     // row subtraction
				for (int row = column + 1; row < this->size; ++row) {
					for (int column_tmp = column; column_tmp < this->size + 1; ++column_tmp) {
						if (column_tmp == this->size) {
							b[row] -= b[column];
						}
						else {
							this->xy[row][column_tmp] -= this->xy[column][column_tmp];
						}
					}
				}
			}
		}

		int zero_counter;
		bool one_solution = true;
		cout << "\nAnswer:\n" << endl;

		for (int row = 0; row < this->size; ++row) {   // check for the number of solutions
			zero_counter = 0;
			for (int column = 0; column < this->size; ++column) {
				if (this->xy[row][column] == 0) {
					++zero_counter;
				}
			}

			if (zero_counter == this->size && b[row] != 0) {
				cout << "\nNo solutions" << endl;
				return;
			}
			else if (zero_counter == this->size && b[row] == 0) {
				one_solution = false;
			}
		}

		if (one_solution) {
			x[this->size - 1] = b[this->size - 1];

			for (int x_row = (this->size - 2); x_row > -1; --x_row) {
				for (int x_column = x_row + 1; x_column < this->size; ++x_column) {
					b[x_row] -= (this->xy[x_row][x_column] * x[x_column]);
				}
				x[x_row] = b[x_row];
			}

			for (int i = 0; i < this->size; ++i) {
				cout << "x" << i + 1 << " = " << x[i] << endl;
			}

			check_function(A_tmp_copy, b_tmp_copy, x);
		}
		else {
			cout << "\nInfinitely many solutions" << endl;
		}
	}
};
