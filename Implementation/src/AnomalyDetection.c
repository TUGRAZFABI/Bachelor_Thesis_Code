#include "../include/AnomalyDetection.h"

void slideWindow(float* buffer, int size, float value)
{
    for (int i = 0; i < size - 1; i++)
    {
        buffer[i] = buffer[i + 1];
    }
    buffer[size - 1] = value;
}

void embedding(float* buffer, float* slidingWindow, int size, int* indexes)
{
    for (int i = 0; i < size; i++)
    {
        int xt = indexes[i];
        buffer[i] = slidingWindow[xt];
    }
}

void embeddingIndexes(int* buffer, int windowSize, int dimensions, int tau)
{
    int w = windowSize - 1;
    for (int i = 0; i < dimensions; i++)
    {
        int xt = w - i * tau;
        buffer[i] = xt;
    }
}

void pca(float* runningMean, float* runningCov, float* buffer, float* slidingWindow, float* tde)
{
    for (int i = 0; i < sizeof(runningMean); i++)
    {
    }
}

void updateMean(float* runningMean, float* tde, int dimensions, float alpha)
{
    // float alpha = 0.05f; // learning rate

    for (int i = 0; i < dimensions; i++)
    {
        runningMean[i] = (1.0f - alpha) * runningMean[i] + (alpha * tde[i]);
    }
}

void copyArray(float* oldMean, float* runningMean, int dimensions)
{
    for (int i = 0; i < dimensions; i++)
    {
        oldMean[i] = runningMean[i];
    }
}

int indexAcsessHelper(int row, int column, int dimensions)
{
    return row * dimensions + column;
}

void updateCovariance(float* runningCov, float* tde, float* runningMean, int dimensions)
{
    float alpha = 0.05f;
    float oldMean[dimensions];
    copyArray(oldMean, runningMean, dimensions);
    updateMean(runningMean, tde, dimensions, 0.25);

    for (int row = 0; row < dimensions; row++)
    {
        float diff_old_row = tde[row] - oldMean[row];
        for (int column = 0; column < dimensions; column++)
        {
            int index = row * dimensions + column;
            runningCov[index] = (1 - alpha) * runningCov[index] +
                                alpha * diff_old_row * (tde[column] - runningMean[column]);
        }
    }
}

void jacobiEigenDecomposition(float* runningCov, float* eigenValues, float* eigenVector,
                              int dimensions)
{
    // create an idenity matrix
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            eigenVector[indexAcsessHelper(i, j, dimensions)] = (i == j) ? 1.0 : 0.0f;
        }
    }

    int maxIterations = 1000;
    for (int iteration = 0; iteration < maxIterations; iteration++)
    {
        // find largest element outside the diagonal
        float min = 0.0f;
        for (int i = 0; i < dimensions; i++)
        {
            for (int j = 0; j < dimensions; j++)
            {
                if (j != i)
                {
                    float currentElement = runningCov[indexAcsessHelper(i, j, dimensions)];

                    if (currentElement < min)
                    {
                        min = currentElement;
                    }
                }
            }
        }

        if (min < 0.000001f)
        {
            break;
        }
    }
}
