#ifndef TDE_H
#define TDE_H

#include <stdlib.h>
#include "../include/vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct TDE
    {
        int dimension_;
        int tau_;
    } TDE;

    void tdeInit(TDE* tde, int dimension, int tau);

    // void embedding(slidingWindow& SlidingWindow, Vector& output);
#ifdef __cplusplus
}
#endif

#endif // VECTOR_H