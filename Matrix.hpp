//
// Created by avichay t on 1/7/19.
//


//todo destructor
//todo comments

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

    Matrix(unsigned int rows, unsigned int cols) : _data(rows * cols), _rows(rows), _cols(cols)
    {

    }

    Matrix(unsigned int rows, unsigned int cols, const vector<P> &cells) : _data(rows * cols, cells), _rows(rows),
                                                                           _cols(cols)
    {

    }

    ~Matrix()
    {

    }

    bool operator==(const Matrix &other)
    {
        return _data == other._data;
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
        Matrix result(_data + other._data);
        return result;
    }

    Matrix operator-(const Matrix &other)
    {
        if (!sameDimensions(other))
        {
            throw std::invalid_argument(ARITHMETIC_DIMENSIONS_ERROR_MESSAGE);
        }
        Matrix result(_data - other._data);
        return result;
    }

    P &operator()(unsigned int rows, unsigned int cols)
    {
        return _data[(rows + 1) * cols];
    }

    bool isSquareMatrix()
    {
        return _cols == _rows;
    }


    friend std::ostream &operator<<(std::ostream &output, Matrix &matrix)
    {
        for (unsigned int i = 0; i < matrix._rows; ++i)
        {
            for (unsigned int j = 0; j < matrix._cols; ++j)
            {
                output << matrix(i, j) << '\t';
            }
            output << std::endl;
        }
        return output;
    }

    int rows()
    {
        return rows;
    }

    int cols()
    {
        return cols;
    }


private:
    vector<P> _data;
    int _rows, _cols;

    bool sameDimensions(const Matrix &other)
    {
        return _cols == other._cols && _rows == other._rows;
    }
};


#endif //CPP_03_MATRIX_H
