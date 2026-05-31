#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>
class Matrix
{
  private:
    int rows;
    int columns;
    float* data;

  public:
    Matrix() : rows(0), columns(0), data(nullptr) {};

    Matrix(int r, int c) : rows(r), columns(c)
    {
        data = new float[r * c]();
    }

    ~Matrix()
    {
        delete[] data;
    }

    // avoid double free bugs
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    // avoid indexing issues
    inline float& at(int r, int c)
    {
        return data[r * columns + c];
    }

    int getAmountRows()
    {
        return rows;
    }

    int getAmountColumns()
    {
        return columns;
    }

    void DEBUG_PRINT()
    {
        for (int i = 0; i < rows; i++)
        {
            std::cout << "[";
            for (int j = 0; j < columns; j++)
            {
                std::cout << at(i, j) << ",";
            }
            std::cout << "]" << std::endl;
        }
    }
};

#endif