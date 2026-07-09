#ifndef ANOMALYDETECTION_H
#define ANOMALYDETECTION_H

#include <math.h> //in c++ : <cmath> in java: java.lang.math
#include <stdio.h>
// for abs function in c++: <cmath> in java: java.lang
#include <stdlib.h>
#include "../include/utils.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // main api calls
    void processNewDataPoint(float newValue, float* tde, float* slidingWindow, float* runningMean,
                             float* runningCov, float* eigenvalues, float* eigenvectors,
                             int* indexes, int windowSize, int dimensions, float* outX,
                             float* outY);

    void slideWindow(float* slidingWindow, int size, float value);
    void embedding(float* buffer, float* slidingWindow, int size, int* indexes);
    void embeddingIndexes(int* buffer, int windowSize, int dimensions, int tau);

    // tde stuff
    void PCA(float* runningMean, float* runningCov, float* tde, float* slidingWindow,
             int dimensions, int windowSize, float newValue, int* indexes);
    void updateMean(float* runningMean, float* slidingWindow, int windowSize, float oldestValue);
    void centerData(float* runningMean, float* tde, int dimensions);

    void copyArray(float* array1, float* array2, int dimensions);
    int indexAccessHelper(int row, int column, int dimensions);

    void updateCovariance(float* runningCov, float* tde, float* tdeOld, int dimensions);

    void jacobiEigenvalue(const float* runningCov, int dim, float* eigenvalues,
                          float* eigenvectors);
    void findTopTwoComponents(const float* eigenvalues, int dim, int* idx_pc1, int* idx_pc2);
    void projectData(float* tde, float* eigenvectors, int dimensions, int targetComponentIdx,
                     float* outputProjection);

#ifdef __cplusplus
}
#endif

#endif // ANOMALYDETECTION_H