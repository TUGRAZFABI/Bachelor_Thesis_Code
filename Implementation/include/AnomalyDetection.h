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
    // Returns 1 once outX/outY hold a valid projection, 0 if there is not yet enough
    // stream history for a single embedded vector or a covariance estimate (n < 2).
    int processNewDataPoint(float newValue, float* tde, float* slidingWindow, float* runningMean,
                            float* runningCov, float* eigenvalues, float* eigenvectors,
                            int* indexes, int windowSize, int dimensions, int* sampleCount,
                            float* outX, float* outY);

    void slideWindow(float* slidingWindow, int size, float value);
    void embedding(float* buffer, float* slidingWindow, int size, int* indexes);
    void embeddingIndexes(int* buffer, int windowSize, int dimensions, int tau);

    // tde stuff
    // sampleCount persists across calls (caller-owned, init to 0). validCountOut receives the
    // number of embedded vectors currently backing runningMean/runningCov (n), saturating at
    // (windowSize - (dimensions-1)*tau) once the window is full. Returns 0 while there is not
    // yet a single valid embedded vector (not enough raw history), 1 otherwise.
    int PCA(float* runningMean, float* runningCov, float* tde, float* slidingWindow,
            int dimensions, int windowSize, float newValue, int* indexes, int* sampleCount,
            int* validCountOut);
    // newEmbedded/oldEmbedded are raw (uncentered). Pass oldEmbedded = NULL while the window
    // is still filling up (no eviction yet); pass the aged-out vector once it is full.
    void updateMean(float* runningMean, int dimensions, int n, const float* newEmbedded,
                    const float* oldEmbedded);
    void centerData(float* runningMean, float* tde, int dimensions);

    void copyArray(float* inputArray, float* outputArray, int dimensions);
    int indexAccessHelper(int row, int column, int dimensions);

    // newCentered/oldCentered are already mean-centered. Pass oldCentered = NULL while the
    // window is still filling up (no eviction yet).
    void updateCovariance(float* runningCov, int dimensions, const float* newCentered,
                          const float* oldCentered);

    void jacobiEigenvalue(float* runningCov, int dim, float* eigenvalues, float* eigenvectors);
    void findTopTwoComponents(const float* eigenvalues, int dim, int* idx_pc1, int* idx_pc2);
    void projectData(float* tde, float* eigenvectors, int dimensions, int targetComponentIdx,
                     float* outputProjection);

#ifdef __cplusplus
}
#endif

#endif // ANOMALYDETECTION_H