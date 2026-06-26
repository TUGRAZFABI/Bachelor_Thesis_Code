#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif
    void printAnyArray(float* buffer, int size)
    {
        for (int i = 0; i < size; i++)
        {
            printf("[%2.f],", buffer[i]);
        }
        printf("\n");
    }

#ifdef __cplusplus
}
#endif

#endif // UTILS_H