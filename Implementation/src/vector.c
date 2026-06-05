#include "../include/vector.h"
#include <stdlib.h>

void vectorInit(Vector* vector, int size)
{
    vector->vectorSize_ = size;
    vector->data_ = (float*)malloc(size * sizeof(float));
}

void push_back(Vector* vector, float value)
{
    for (int i = 1; i < vector->vectorSize_; i++)
    {
        vector->data_[i - 1] = vector->data_[i];
    }
    vector->data_[vector->vectorSize_ - 1] = value;
}

float at(Vector* vector, int index)
{
    return vector->data_[index];
}

int returnSizeVector(Vector* vector)
{
    return vector->vectorSize_;
}

void freeVector(Vector* vector)
{
    free(vector);
}