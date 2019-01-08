//todo destructor
//todo comments

#ifndef CPP_03_MATRIX_H
#define CPP_03_MATRIX_H

#define ARITHMETIC_DIMENSIONS_ERROR_MESSAGE "Cannot perform arithmetic on matrices of different dimensions."
#define TRANSPOSE_ON_NON_SQUARE_MATRIX_ERROR "Cannot perform transpose on non square matrix"

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

    P operator()(unsigned int rows, unsigned int cols) const
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

    Matrix &operator=(const Matrix &other)
    {
        _data = other._data;
        return *this;
    }

    int rows()
    {
        return rows;
    }

    int cols()
    {
        return cols;
    }

    void trans()
    {
        if (!isSquareMatrix())
        {
            throw std::invalid_argument(TRANSPOSE_ON_NON_SQUARE_MATRIX_ERROR);
        }

        Matrix<P> copyMatrix = *this;
        for (unsigned int i = 0; i < rows(); ++i)
        {
            for (unsigned int j = 0; j < cols(); ++j)
            {
                (*this)(i, j) = copyMatrix(j, i);
            }
        }
    }

    typename vector<P>::iterator begin()
    {
        return _data.begin();
    }

    typename vector<P>::iterator end()
    {
        return _data.end();
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
