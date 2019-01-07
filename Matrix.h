//
// Created by avichay t on 1/7/19.
//

#ifndef CPP_03_MATRIX_H
#define CPP_03_MATRIX_H

#define ARITHMETIC_DIMENSIONS_ERROR_MESSAGE "Cannot perform arithmetic on matrices of different dimensions."

#include <vector>
#include <exception>

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

private:
    vector<P> data;
    int rows, cols;

    bool sameDimensions(const Matrix &other)
    {
        return cols == other.cols && rows == other.rows;
    }
};


#endif //CPP_03_MATRIX_H
