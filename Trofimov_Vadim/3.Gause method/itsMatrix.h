#pragma once
#include "itsVector.h"
template <typename T>
class Matrix :
    public Vector<Vector<T>>
{
public:
    Matrix(int dim = 1) : Vector<Vector<T>>(dim) {
        if (dim > 0) {
            for (int i = 0; i < dim; ++i) {
                this->arr_[i].setArr(dim);
            }
        }
        else {throw std::exception("dimension shoud be greater than zero"); }
    }
    Matrix(Matrix& a) : Vector<Vector<T>>(a.getLength()) {
        for (int i = 0; i < a.getLength(); ++i) {
            this->arr_[i] = a[i];
        }
    }
    Vector<T>& operator[](int i){
        return this->arr_[i];
    }
    int getDim() { return this->len_; }
};  
template <typename T> Vector<T> operator *(Matrix<T>& m, Vector<T>& v) {
    int lenF = m.getDim();
    int lenS = v.getLength();
    if (lenF == lenS) {
        Vector<T> res(lenF);
        for (int i = 0; i < lenF; ++i) {
            res[i] = m[i] * v;
        }
        return res;
    }
    else{ throw std::exception("matrix and vector shoud be the same length"); }
};
template <typename T> bool operator ==(Matrix<T>& X, Matrix<T>& Y){
    int dimF = X.getDim(), dimS = Y.getDim();
    if (dimF != dimS) { throw std::exception("matrix shoud be the same dimentions");}
    else {
        for (int i = 0; i < dimF; ++i) {
            if (X[i] != Y[i]) { return false; }
            else { return true; }
        }
    }
};

template <typename T> std::ostream& operator <<(std::ostream& os, Matrix<T>& a) {
    for (int i = 0; i < a.getDim(); ++i) {
        std::cout << "{";
        std::cout << a[i][0];
        for (int j = 1; j < a.getDim(); ++j) {
            std::cout << ";" << a[i][j];
        }
        std::cout << "}" << std::endl;
    }
    return os;
};
template <typename T> std::istream& operator >>(std::istream& is, Matrix<T>& a) {
    for (int i = 0; i < a.getDim(); ++i) {
        for (int j = 0; j < a.getDim(); ++j) {
            std::cout << "A(" << i + 1 << "," << j + 1 << ") =" ;
            std::cin >> a[i][j];
        }
    }
    return is;
};