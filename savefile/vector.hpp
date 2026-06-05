#ifndef MATRIX_HPP
#define MATRIX_HPP
struct Vector
{
    size_t vectorSize_;
    float* data_;
};

void vectorInit(Vector& vector, size_t size)
{
    vector.vectorSize_ = size;
    vector.data_ = new float[size];
}

void push_back(Vector& vector, float value)
{
    for (size_t i = 1; i < vector.vectorSize_; i++)
    {
        vector.data_[i - 1] = vector.data_[i];
    }
    vector.data_[vector.vectorSize_ - 1] = value;
}

float at(Vector& vector, int index)
{
    return vector.data_[index];
}

size_t returnSizeVector(Vector& vector)
{
    return vector.vectorSize_;
}

void freeVector(Vector& vector)
{
    delete[] vector.data_;
    vector.data_ = nullptr;
    vector.vectorSize_ = 0;
}

#endif