#pragma once
#include <iostream>
template <typename T>
class Vector
{
protected:
	int len_;
	T* arr_ = nullptr;
public:
	Vector<T>(int len = 1) {
		if (len > 0) {
			len_ = len;
			arr_ = new T[len];
		}
		else {
			throw std::exception("length shoud be greater than zero!");
		}
	}
	Vector<T>(const Vector<T>& a) {
		len_ = a.len_;
		arr_ = new T[len_];
		for (int i = 0; i < len_; ++i) {
			arr_[i] = a.arr_[i];
		}
	}
	~Vector<T>() {
		delete[]arr_;
	}
	int getLength() { return len_; }
	void setArr(int len) {
		if (len > 0) {
			len_ = len;
			delete[] arr_;
			arr_ = new T[len];
		}
		else {throw std::exception("length shoud be greater than zero");}
	}
	void swap(int first, int second) {
		T tmp = arr_[first];
		arr_[first] = arr_[second];
		arr_[second] = tmp;
	}
	T& operator[](const int a) {
		return arr_[a];
	}
	const Vector<T>& operator =(const Vector<T>& a) {
		len_ = a.len_;
		delete arr_;
		arr_ = new T[len_];
		for (int i = 0; i < len_; ++i) {
			arr_[i] = a.arr_[i];
		}
		return *this;
	}
	};
template<typename T> const Vector<T>& operator -=(Vector<T>&x, Vector<T>& y) {
	int lenF = x.getLength(), lenS = y.getLength();
	if (lenF == lenS) {
		for (int i = 0; i < lenF; ++i) {
			x[i] -= y[i];
		}
		return x;
	}
	else {
		throw std::length_error("vectors shoud be the same length");
	};
};
template<typename T> Vector <T> operator *(const Vector<T>& x, const T a) {
	int lenF = x.getLength();
	Vector<T> res(lenF);
	for (int i = 0; i < lenF; ++i) {
		res[i] = x[i] * a;
	}
	return res;
};

template<typename T> T operator *( Vector<T>& x,Vector<T>& y) {
	if (x.getLength() == y.getLength()) {
		int lenF = x.getLength();
		T res = static_cast<T>(0);
		for (int i = 0; i < lenF; ++i) {
			res += x[i] * y[i];
		}
		return res;
	}
	else { throw std::exception("vectors shoud be the same length"); }
};

template<typename T> bool operator ==(const Vector<T>& x,const Vector<T>& y) {
	int lenF = x.getLength(), lenS = y.getLength();
	if (lenF != lenS) { throw std::exception("vectors shoud be the same length"); }
	else {
		for (int i = 0; i < lenF; ++i) {
			if (x[i] != y[i]) { return false; }
			else { return true; }
		}
	}
};

template<typename T> bool operator !=(Vector<T>& x, Vector<T>& y) {
	return !(x == y);
};

template<typename T> std::ostream& operator<<(std::ostream& os, Vector<T>& x) {
	std::cout << "{" << x[0];
	for (int i = 1; i < x.getLength(); ++i) {
		std::cout << ";" << x[i];
	}
	std::cout << "}" << std::endl;
	return os;
}
template <typename T> std::istream& operator>>(std::istream& is, Vector<T>& x) {
	for (int i = 0; i < x.getLength(); ++i) {
		std::cout <<"b(" << i + 1 << ") =" ;
		std::cin >> x[i];
	}
	return is;
}