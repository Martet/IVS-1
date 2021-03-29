//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Martin Zmitko <xzmitk01@stud.fit.vutbr.cz>
// $Date:       $2021-02-22
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Martin Zmitko
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixWrong : public ::testing::Test
{
protected:
    Matrix matrix;
};

class Matrix1x1 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix = Matrix();
        matrix.set(0, 0, 5);
    }

    Matrix matrix;
};

class Matrix2x2 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix = Matrix(2, 2);
        std::vector<std::vector<double>> values = {{1, 1}, {2, 3}};
        matrix.set(values);
    }

    bool compareMatrix(Matrix m, std::vector<std::vector<double>> v){
        Matrix compare = Matrix(v.size(), v[0].size());
        compare.set(v);
        return compare == m;
    }

    Matrix matrix;
};

class Matrix3x2 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix = Matrix(3, 2);
        matrix.set(std::vector<std::vector<double>>{{1, 2}, {1, 3}, {2, 3}});
    }

    bool compareMatrix(Matrix m, std::vector<std::vector<double>> v){
        Matrix compare = Matrix(v.size(), v[0].size());
        compare.set(v);
        return compare == m;
    }

    Matrix matrix;
};

class Matrix3x3 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix = Matrix(3, 3);
        matrix.set(std::vector<std::vector<double>>{{1, 2, 1}, {1, 2, 2}, {1, 1, 1}});
    }

    bool compareMatrix(Matrix m, std::vector<std::vector<double>> v){
        Matrix compare = Matrix(v.size(), v[0].size());
        compare.set(v);
        return compare == m;
    }

    Matrix matrix;
};

class Matrix4x4 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix = Matrix(4, 4);
        matrix.set(std::vector<std::vector<double>>{{2, 2, -3, 1}, {1, 2, 4, 2}, {-1, 1, -1, 1}, {1, -1, 2, -2}});
    }

    bool compareMatrix(Matrix m, std::vector<std::vector<double>> v){
        Matrix compare = Matrix(v.size(), v[0].size());
        compare.set(v);
        return compare == m;
    }

    Matrix matrix;
};



TEST_F(Matrix2x2, get)
{
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_THROW(matrix.get(-1, 0), std::runtime_error);
}

TEST_F(Matrix1x1, set)
{
    EXPECT_FALSE(matrix.set(5, 0, 2));
    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>>{1}));
    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>>{{2}, {2}, {3}}));
}

TEST_F(Matrix3x2, operations)
{
    Matrix mat2x3 = Matrix(2, 3);
    mat2x3.set(std::vector<std::vector<double>>{{2, 1, 3}, {1, 1, 2}});
    Matrix mat3x2 = matrix;
    mat3x2.set(0, 0, 5);

    EXPECT_THROW(matrix == mat2x3, std::runtime_error);
    EXPECT_FALSE(matrix == mat3x2);
    EXPECT_TRUE(matrix == matrix);
    EXPECT_TRUE(compareMatrix(matrix * mat2x3, {{4, 3, 7}, {5, 4, 9}, {7, 5, 12}}));
    EXPECT_THROW(matrix * matrix, std::runtime_error);
    EXPECT_TRUE(compareMatrix(matrix + matrix, {{2, 4}, {2, 6}, {4, 6}}));
    EXPECT_THROW(matrix + mat2x3, std::runtime_error);
    EXPECT_TRUE(compareMatrix(matrix * 2, {{2, 4}, {2, 6}, {4, 6}}));
    EXPECT_TRUE(compareMatrix(matrix.transpose(), {{1, 1, 2}, {2, 3, 3}}));

    EXPECT_THROW(matrix.inverse(), std::runtime_error);
}

TEST_F(Matrix3x3, inverse)
{
    EXPECT_TRUE(compareMatrix(matrix.inverse(), {{0, -1, 2}, {1, 0, -1}, {-1, 1, 0}}));
}

TEST_F(Matrix2x2, inverse)
{
    EXPECT_TRUE(compareMatrix(matrix.inverse(), {{3, -1}, {-2, 1}}));
    matrix.set({{1, 1}, {1, 1}});
    EXPECT_THROW(matrix.inverse(), std::runtime_error);
}

TEST_F(Matrix1x1, inverse)
{
    EXPECT_THROW(matrix.inverse(), std::runtime_error);
}

TEST_F(Matrix1x1, equation)
{
    EXPECT_EQ(matrix.solveEquation({5}), std::vector<double>{1});
}

TEST_F(Matrix3x2, equation){
    EXPECT_THROW(matrix.solveEquation({1, 2, 3}), std::runtime_error);
    EXPECT_THROW(matrix.solveEquation({2, 3}), std::runtime_error);
}

TEST_F(Matrix4x4, equation)
{
    EXPECT_TRUE(matrix.solveEquation({3, 5, 1, -4}) == std::vector<double>({1, -1, 0, 3}));
    matrix = Matrix(2, 2);
    EXPECT_THROW(matrix.solveEquation({1, 2}), std::runtime_error);
}

TEST_F(MatrixWrong, constructor)
{
    EXPECT_THROW(Matrix(0, 1), std::runtime_error);
}



/*** Konec souboru white_box_tests.cpp ***/
