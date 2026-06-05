#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Vector
    {
        int vectorSize_;
        float* data_;
    } Vector;

    void vectorInit(Vector* vector, int size);

    void push_back(Vector* vector, float value);

    float at(Vector* vector, int index);

    int returnSizeVector(Vector* vector);

    void freeVector(Vector* vector);
#ifdef __cplusplus
}
#endif

#endif // VECTOR_H