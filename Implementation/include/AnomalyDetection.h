#ifndef ANOMALYDETECTION_H
#define ANOMALYDETECTION_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif
    void slideWindow(float* buffer, int size, float value);
    void embedding(float* buffer, float* slidingWindow, int size, int* indexes);
    void embeddingIndexes(int* buffer, int windowSize, int dimensions, int tau);

    // tde stuff
    void pca(float* runningMean, float* runningCov, float* buffer, float* slidingWindow,
             float* tde);

    void updateMean(float* runningMean, float* tde, int dimensions, float alpha);
    void copyArray(float* oldMean, float* runningMean, int dimensions);
    int indexAcsessHelper(int row, int column, int dimensions);

    void updateCovariance(float* runningCov, float* tde, float* runningMean, int dimensions);

    void jacobiEigenDecomposition(float* runningCov, float* eigenValues, float* eigenVectors,
                                  int dimensions);

#ifdef __cplusplus
}
#endif

#endif // ANOMALYDETECTION_H