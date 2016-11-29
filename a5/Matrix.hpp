#ifndef A5_MATRIX_HPP
#define A5_MATRIX_HPP

#include <cassert>
#include <complex>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<T>> data;

public:
    Matrix() {
        rows = 1;
        cols = 1;
        data.resize(rows);
        data[0].resize(cols);
    }

    Matrix(int rows, int cols) {
        Matrix::rows = rows;
        Matrix::cols = cols;
        data.resize(rows);
        for (auto it = data.begin(); it != data.end(); ++it) {
            it->resize(cols);
        }
    }

    const int getRows() const {
        return rows;
    }

    const int getCols() const {
        return cols;
    }

    std::vector<T> &operator[](const int index) {
        return data.at(index);
    }

    const std::vector<T> &operator[](const int index) const {
        return data.at(index);
    }

    const Matrix<T> operator+(const Matrix<T> &rhs) const {
        Matrix result(rhs.getRows(), rhs.getCols());
        for (int row = 0; row < rhs.getRows(); ++row) {
            for (int col = 0; col < rhs.getCols(); ++col) {
                result[row][col] = (*this)[row][col] + rhs[row][col];
            }
        }
        return result;
    }

    Matrix<T> &operator+=(const Matrix<T> &rhs) {
        *this = (*this) + rhs;
        return *this;
    }

    const Matrix<T> operator-(const Matrix<T> &rhs) const {
        Matrix result(rhs.getRows(), rhs.getCols());
        for (int row = 0; row < rhs.getRows(); ++row) {
            for (int col = 0; col < rhs.getCols(); ++col) {
                result[row][col] = (*this)[row][col] - rhs[row][col];
            }
        }
        return result;
    }

    Matrix<T> &operator-=(const Matrix<T> &rhs) {
        *this = (*this) - rhs;
        return *this;
    }

    const Matrix<T> operator*(const Matrix<T> &rhs) const {
        // create a matrix of dimension leftRows x rightCols
        Matrix result(this->getCols(), rhs.getCols());
        for (int row = 0; row < this->getRows(); ++row) {
            for (int col = 0; col < rhs.getCols(); ++col) {
                for (int rc = 0; rc < this->getRows(); ++rc) {
                    result[row][col] += (*this)[row][rc] * rhs[rc][col];
                }
            }
        }
        return result;
    }

    Matrix<T> &operator*=(const Matrix<T> &rhs) {
        *this = (*this) * rhs;
        return *this;
    }

    bool operator==(const Matrix<T> &rhs) const {
        if (this->getRows() != rhs.getRows()) {
            return false;
        }
        if (this->getCols() != rhs.getCols()) {
            return false;
        }
        for (int row = 0; row < rhs.getRows(); ++row) {
            for (int col = 0; col < rhs.getCols(); ++col) {
                if ((*this)[row][col] != rhs[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix<T> &rhs) const {
        return !((*this) == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &obj) {
        for (auto rowIt = obj.data.begin(); rowIt != obj.data.end(); ++rowIt) {
            for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
                if (colIt != rowIt->end() - 1) {
                    os << *colIt << " ";
                } else {
                    os << *colIt;
                }
            }
            os << std::endl;
        }
        return os;
    }
};

template<typename T>
const Matrix<T> operator*(const T &scalar, const Matrix<T> &rhs) {
    Matrix<T> result(rhs.getRows(), rhs.getCols());
    for (int row = 0; row < rhs.getRows(); ++row) {
        for (int col = 0; col < rhs.getCols(); ++col) {
            result[row][col] = scalar * rhs[row][col];
        }
    }
    return result;
}

template<typename T>
const Matrix<T> operator*(const Matrix<T> &lhs, const T &scalar) {
    Matrix<T> result(lhs.getRows(), lhs.getCols());
    for (int row = 0; row < lhs.getRows(); ++row) {
        for (int col = 0; col < lhs.getCols(); ++col) {
            result[row][col] = lhs[row][col] * scalar;
        }
    }
    return result;
}

template<typename T>
Matrix<T> &operator*=(Matrix<T> &lhs, const T &scalar) {
    lhs = lhs * scalar;
    return lhs;
}

#endif //A5_MATRIX_HPP
