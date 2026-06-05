#include "../include/tde.h"
#include <stdio.h>

void tdeInit(TDE* tde, int dimension, int tau)
{
    tde->dimension_ = dimension;
    tde->tau_ = tau;
}

void embedding(TDE* tde, Vector* output, float slidingWindow[], int windowSize)
{
    int m = output->vectorSize_;
    int w = windowSize - 1;
    for (int i = 0; i < m; i++)
    {
        int xt = w - i * tde->tau_;
        setVectorIndex(output, i, slidingWindow[xt]);
    }
}
