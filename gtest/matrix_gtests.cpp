#include <gtest/gtest.h>

#include <string>

#include "matrix.hpp"

using namespace std;

TEST(MatrixTests, RowsAndCols) {
    Matrix<int> mat{3, 2};
    EXPECT_EQ(mat.num_rows(), 3);
    EXPECT_EQ(mat.num_cols(), 2);

    Matrix<double> mat2{5, 1};
    EXPECT_EQ(mat2.num_rows(), 5);
    EXPECT_EQ(mat2.num_cols(), 1);

    Matrix<string> mat3;
    EXPECT_EQ(mat3.num_rows(), 0);
    EXPECT_EQ(mat3.num_cols(), 0);
}

TEST(MatrixTests, FillWithValue) {
    Matrix<int> mat{2, 3};
    mat.fill(5);
    for (int i = 0; i < mat.num_rows(); ++i) {
        for (int j = 0; j < mat.num_cols(); ++j) {
            EXPECT_EQ(mat[i][j], 5);
        }
    }
}

TEST(MatrixTests, FillWithFunction) {
    Matrix<int> mat{2, 2};
    auto fn = [](int i, int j) { return i + j; };
    mat.fill_with_fn(fn);
    for (int i = 0; i < mat.num_rows(); ++i) {
        for (int j = 0; j < mat.num_cols(); ++j) {
            EXPECT_EQ(mat[i][j], i + j);
        }
    }
}