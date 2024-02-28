#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "array.hpp"

template <typename T>
class Matrix {
public:
    // Constructors
    Matrix() : rows(0), cols(0), data() {}
    Matrix(int rows, int columns) : rows(rows), cols(columns), data(rows) {
        for(int i = 0; i < rows; ++i) {
            data[i] = Array<T>(columns);
        }
    }
    // Operator overloading to access rows
    Array<T>& operator[](int row) {
        return data[row];
    }

    const Array<T>& operator[](int row) const {
        return data[row];
    }

    // Get number of rows and columns
    int num_rows() const {
        return rows;
    }

    int num_cols() const {
        return cols;
    }

    // Fill every entry of the matrix with given value 'val'
    void fill(const T& val) {
        for (int i = 0; i < rows; ++i) {
            data[i].fill(val);
        }
    }

    // Fill matrix, set entry in row 'i' and column 'j' to 'fn(i, j)'
    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }

private:
    int rows;
    int cols;
    Array<Array<T>> data;
};

// Stream insertion operator
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        out << matrix[i] << std::endl;
    }
    return out;
}

// Stream extraction operator
template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        in >> matrix[i];
    }
    return in;
}

#endif // MATRIX_HPP
