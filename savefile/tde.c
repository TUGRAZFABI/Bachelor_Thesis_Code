#include "../include/tde.h"
#include <stdio.h>

void tdeInit(TDE* tde, int dimension, int tau)
{
    tde->dimension_ = dimension;
    tde->tau_ = tau;
    tde->indices_ = (int*)malloc(dimension * sizeof(int));
}

void calculateTDEIndexes(TDE* tde, int windowSize)
{
    int m = tde->dimension_;
    int w = windowSize - 1;
    for (int i = 0; i < m; i++)
    {
        int xt = w - i * tde->tau_;
        tde->indices_[i] = xt;
    }
}

void embedding(TDE* tde, Vector* output, float slidingWindow[])
{
    for (int i = 0; i < tde->dimension_; i++)
    {
        int xt = tde->indices_[i];
        setVectorIndex(output, i, slidingWindow[xt]);
    }
}
