//
// Created by avichay t on 1/7/19.
//

#ifndef CPP_03_MATRIX_H
#define CPP_03_MATRIX_H

#define ARITHMETIC_DIMENSIONS_ERROR_MESSAGE "Cannot perform arithmetic on matrices of different dimensions."

#include <vector>
#include <exception>
#include <iostream>

using std::vector;


template<class P>
class Matrix
{
    Matrix() : Matrix(1, 1)
    {

    }

    Matrix(unsigned int rows, unsigned int cols) : data(rows * cols), rows(rows), cols(cols)
    {

    }

    Matrix(unsigned int rows, unsigned int cols, const vector<P> &cells) : data(rows * cols, cells), rows(rows),
                                                                           cols(cols)
    {

    }

    ~Matrix()
    {

    }

    bool operator==(const Matrix &other)
    {
        return data == other.data;
    }

    bool operator!=(const Matrix &other)
    {
        return !(*this == other);
    }


    Matrix operator+(const Matrix &other)
    {
        if (!sameDimensions(other))
        {
            throw std::invalid_argument(ARITHMETIC_DIMENSIONS_ERROR_MESSAGE);
        }
        Matrix result(data + other.data);
        return result;
    }

    Matrix operator-(const Matrix &other)
    {
        if (!sameDimensions(other))
        {
            throw std::invalid_argument(ARITHMETIC_DIMENSIONS_ERROR_MESSAGE);
        }
        Matrix result(data - other.data);
        return result;
    }

    P &operator()(unsigned int rows, unsigned int cols)
    {
        return data[(rows + 1) * cols];
    }

    bool isSquareMatrix()
    {
        return cols == rows;
    }


    friend std::ostream &operator<<(std::ostream &output, Matrix &matrix)
    {
        for (unsigned int i = 0; i < matrix.rows; ++i)
        {
            for (unsigned int j = 0; j < matrix.cols; ++j)
            {
                output << matrix(i, j) << '\t';
            }
            output << std::endl;
        }
        return output;
    }

private:
    vector<P> data;
    int rows, cols;

    bool sameDimensions(const Matrix &other)
    {
        return cols == other.cols && rows == other.rows;
    }
};


#endif //CPP_03_MATRIX_H
