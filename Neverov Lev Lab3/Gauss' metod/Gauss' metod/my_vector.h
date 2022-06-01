#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

template<typename T>
class my_vector {
protected:
	T* xy;
	int size;

public:
	my_vector(int basic_size = 1) {
		if (basic_size < 0) {
			throw "Error! Negative size of array";
		}
		size = basic_size;
		xy = new T[size];
	}

	my_vector(const my_vector<T>& other) {
		this->size = other.size;
		this->xy = new T[other.size];
		for (int i = 0; i < other.size; ++i) {
			this->xy[i] = other.xy[i];
		}
	}

	void resize(int re_size) {
		size = re_size;

		delete[] xy;

		xy = new T[re_size];
	}
	void random_fill(int counter) {
		srand(static_cast<unsigned>(time(0)));

		for (int i = 0; i < size; ++i) {
			if (i != counter || counter == size) {
				xy[i] = 1 + rand() % 5;
			}
			else
			{
				xy[i] = 10 + (size * size - size) * 5 + rand() % (5 * size);
			}
		}
	}

	my_vector& operator =(const my_vector<T>& other) {
		resize(other.size);

		for (int i = 0; i < other.size; ++i) {
			this->xy[i] = other.xy[i];
		}
		return *this;
	}

	T& operator[](int counter) {
		if (counter >= size) {
			throw "Error! Array counter out of bounds";
		}
		return xy[counter];
	}



	~my_vector() {
		delete[] xy;
	}
};
