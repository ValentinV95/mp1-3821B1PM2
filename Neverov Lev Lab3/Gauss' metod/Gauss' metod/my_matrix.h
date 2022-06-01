#include <iostream>
#include "my_vector.h"

using namespace std;


template<typename T>
class my_matrix : public my_vector<my_vector<T>> {
public:
	my_matrix(int my_matrix_size = 1) : my_vector<my_vector<T>>(my_matrix_size) {
		for (int i = 0; i < my_matrix_size; ++i) {
			this->xy[i].resize(my_matrix_size);
		}
	}

	my_vector<T>& operator[](int counter) {
		if (counter >= this->size) {
			throw "Error! Out of bounds of array";
		}
		return this->xy[counter];
	}
};
