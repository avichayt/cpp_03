//todo destructor
//todo comments on exceptions
//todo comments
// todo get n in main in time checker

#ifndef CPP_03_MATRIX_H
#define CPP_03_MATRIX_H

#define ARITHMETIC_DIMENSIONS_ERROR_MESSAGE "Cannot perform arithmetic on matrices of different dimensions."
#define TRANSPOSE_ON_NON_SQUARE_MATRIX_ERROR "Cannot perform transpose on non square matrix"

#define WRONG_DIMENSIONS_OF_MATRIX_MULT_MESSAGE "Cannot multiply matrices of wrong dimentions."

#define INDEX_OUT_OF_BOUNDS_MESSAGE "Index out of bounds"

#define VECTOR_SIZE_ERROR "Vector not in right size"

#include <vector>
#include <exception>
#include <iostream>
#include <algorithm>
#include "Complex.h"

using std::vector;


template<class P>
class Matrix
{
public:

    /**
     * constructor for the matrix class
     */
    Matrix() : Matrix(1, 1)
    {

    }

    /**
     * constructor for the matrix class
     * @param rows amount of rows
     * @param cols amout of cols
     */
    Matrix(unsigned int rows, unsigned int cols) : _data(rows * cols), _rows(rows), _cols(cols)
    {

    }

    /**
     * constructor for the matrix class
     * @param rows amount of rows
     * @param cols amount of cols
     * @param cells
     */
    Matrix(unsigned int rows, unsigned int cols, const vector<P> &cells) : Matrix(rows, cols)
    {
        if (rows * cols != cells.size())
        {
            throw std::invalid_argument(VECTOR_SIZE_ERROR);
        }
        _data = cells;
    }

    bool operator==(const Matrix &other) const
    {

        return _data == other._data && rows() == other.rows() && cols() == other.cols();
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    Matrix operator+(const Matrix &other) const
    {
        if (!sameDimensions(other))
        {
            throw std::invalid_argument(ARITHMETIC_DIMENSIONS_ERROR_MESSAGE);
        }
        Matrix result(rows(), cols());
        result._data = _data;
        for (int i = 0; i < rows() * cols(); ++i)
        {
            result._data[i] += other._data[i];
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        if (!sameDimensions(other))
        {
            throw std::invalid_argument(ARITHMETIC_DIMENSIONS_ERROR_MESSAGE);
        }
        Matrix result(rows(), cols());
        result._data = _data;
        for (int i = 0; i < rows() * cols(); ++i)
        {
            result._data[i] -= other._data[i];
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (cols() != other.rows())
        {
            throw std::invalid_argument(WRONG_DIMENSIONS_OF_MATRIX_MULT_MESSAGE);
        }
        Matrix result(rows(), other.cols());
        P currentValue;
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < other.cols(); ++j)
            {
                currentValue = 0;
                for (int k = 0; k < _cols; ++k)
                {
                    currentValue += (*this)(i, k) * other(k, j);
                }
                result(i, j) = currentValue;

            }
        }
        return result;
    }

    P &operator()(unsigned int rows, unsigned int cols)
    {
        if (rows < 0 || rows >= _rows || cols < 0 || cols >= _cols)
        {
            throw std::out_of_range(INDEX_OUT_OF_BOUNDS_MESSAGE);
        }
        return _data[(rows * _cols) + cols];
    }

    P operator()(unsigned int rows, unsigned int cols) const
    {
        if (rows < 0 || rows >= _rows || cols < 0 || cols >= _cols)
        {
            throw std::out_of_range(INDEX_OUT_OF_BOUNDS_MESSAGE);
        }
        return _data[(rows * _cols) + cols];
    }

    bool isSquareMatrix() const
    {
        return _cols == _rows;
    }


    friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix)
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
        _data.resize(other.cols() * other.rows());
        _data = other._data;
        _rows = other.rows();
        _cols = other.cols();
        return *this;
    }

    unsigned int rows() const
    {
        return _rows;
    }

    unsigned int cols() const
    {
        return _cols;
    }

    Matrix trans();

    typedef typename vector<P>::const_iterator const_iterator;

    const_iterator begin() const
    {
        return _data.cbegin();
    }

    const_iterator end() const
    {
        return _data.cend();
    }


private:
    vector<P> _data;
    unsigned int _rows, _cols;

    bool sameDimensions(const Matrix &other) const
    {
        return _cols == other._cols && _rows == other._rows;
    }
};

template<>
inline
Matrix<Complex> Matrix<Complex>::trans()
{
    if (!isSquareMatrix())
    {
        throw std::invalid_argument(TRANSPOSE_ON_NON_SQUARE_MATRIX_ERROR);
    }

    Matrix<Complex> copyMatrix = *this;
    for (unsigned int i = 0; i < rows(); ++i)
    {
        for (unsigned int j = 0; j < cols(); ++j)
        {
            copyMatrix(i, j) = (*this)(j, i).conj();
        }
    }

    return copyMatrix;
}

template<class P>
Matrix<P> Matrix<P>::trans()
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
            copyMatrix(i, j) = (*this)(j, i);
        }
    }

    return copyMatrix;
}


#endif //CPP_03_MATRIX_H
