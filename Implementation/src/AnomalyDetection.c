#include "../include/AnomalyDetection.h"

#define MAX_ITERATIONS 100
#define EPSILON 1e-6f

// Custom absolute value function for floats
float custom_abs(float x)
{
    return (x < 0.0f) ? -x : x;
}

// Custom square root via Newton-Raphson method
float custom_sqrt(float x)
{
    if (x <= 0.0f)
        return 0.0f;
    float guess = x;
    for (int i = 0; i < 8; i++)
    {
        guess = 0.5f * (guess + x / guess);
    }
    return guess;
}

void slideWindow(float* slidingWindow, int size, float value)
{
    for (int i = 0; i < size - 1; i++)
    {
        slidingWindow[i] = slidingWindow[i + 1];
    }
    slidingWindow[size - 1] = value;
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

// Pure C Algebraic Jacobi Solver (No math.h or memory allocation)
void jacobiEigenvalue(const float* runningCov, int dim, float* eigenvalues, float* eigenvectors)
{
    // 1. Initialize Eigenvectors as Identity Matrix
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            eigenvectors[indexAccessHelper(i, j, dim)] = (i == j) ? 1.0f : 0.0f;
        }
    }

    float A[dim * dim];
    for (int i = 0; i < dim * dim; i++)
    {
        A[i] = runningCov[i];
    }

    for (int iter = 0; iter < MAX_ITERATIONS; iter++)
    {
        // Find the largest off-diagonal element A[p][q]
        int p = 0, q = 1;
        float max_val = custom_abs(A[indexAccessHelper(0, 1, dim)]);

        for (int i = 0; i < dim; i++)
        {
            for (int j = i + 1; j < dim; j++)
            {
                float val = custom_abs(A[indexAccessHelper(i, j, dim)]);
                if (val > max_val)
                {
                    max_val = val;
                    p = i;
                    q = j;
                }
            }
        }

        // Check Convergence
        if (max_val < EPSILON)
        {
            break;
        }

        float app = A[indexAccessHelper(p, p, dim)];
        float aqq = A[indexAccessHelper(q, q, dim)];
        float apq = A[indexAccessHelper(p, q, dim)];

        float theta = (aqq - app) / (2.0f * apq);
        float abs_theta = custom_abs(theta);
        float t = 1.0f / (abs_theta + custom_sqrt(theta * theta + 1.0f));
        if (theta < 0.0f)
        {
            t = -t;
        }

        float c = 1.0f / custom_sqrt(t * t + 1.0f);
        float s = t * c;

        float app_new = c * c * app - 2.0f * s * c * apq + s * s * aqq;
        float aqq_new = s * s * app + 2.0f * s * c * apq + c * c * aqq;

        A[indexAccessHelper(p, p, dim)] = app_new;
        A[indexAccessHelper(q, q, dim)] = aqq_new;
        A[indexAccessHelper(p, q, dim)] = 0.0f;
        A[indexAccessHelper(q, p, dim)] = 0.0f;

        for (int i = 0; i < dim; i++)
        {
            if (i != p && i != q)
            {
                float aip = A[indexAccessHelper(i, p, dim)];
                float aiq = A[indexAccessHelper(i, q, dim)];
                A[indexAccessHelper(i, p, dim)] = c * aip - s * aiq;
                A[p * dim + i] = c * aip - s * aiq;
                A[indexAccessHelper(i, q, dim)] = s * aip + c * aiq;
                A[q * dim + i] = s * aip + c * aiq;
            }
        }

        for (int i = 0; i < dim; i++)
        {
            float vip = eigenvectors[indexAccessHelper(i, p, dim)];
            float viq = eigenvectors[indexAccessHelper(i, q, dim)];
            eigenvectors[indexAccessHelper(i, p, dim)] = c * vip - s * viq;
            eigenvectors[indexAccessHelper(i, q, dim)] = s * vip + c * viq;
        }
    }

    for (int i = 0; i < dim; i++)
    {
        eigenvalues[i] = A[indexAccessHelper(i, i, dim)];
    }
}

void findTopTwoComponents(const float* eigenvalues, int dim, int* idx_pc1, int* idx_pc2)
{
    int first = 0, second = -1;
    float max1 = eigenvalues[0];
    float max2 = -1e9f;

    for (int i = 1; i < dim; i++)
    {
        if (eigenvalues[i] > max1)
        {
            max2 = max1;
            second = first;
            max1 = eigenvalues[i];
            first = i;
        }
        else if (eigenvalues[i] > max2)
        {
            max2 = eigenvalues[i];
            second = i;
        }
    }
    *idx_pc1 = first;
    *idx_pc2 = second;
}

void projectData(float* tde, float* eigenvectors, int dimensions, int targetComponentIdx,
                 float* outputProjection)
{
    float sum = 0.0f;
    for (int i = 0; i < dimensions; i++)
    {
        int matrixIndex = i * dimensions + targetComponentIdx;
        sum += tde[i] * eigenvectors[matrixIndex];
    }
    *outputProjection = sum;
}

// Corrected Streaming Update Engine
void PCA(float* runningMean, float* runningCov, float* tde, float* slidingWindow, int dimensions,
         int windowSize, float newValue, int* indexes)
{
    // 1. EXTRACT THE CORRECT TIME-ORDERED TDE VECTOR DROPPING OUT OF THE FRONT
    float tdeOld[dimensions];
    int tau = indexes[0] - indexes[1]; // Deduce tau spacing dynamically

    for (int i = 0; i < dimensions; i++)
    {
        // Order must match original embedding: (dimensions - 1 - i) * tau
        tdeOld[i] = slidingWindow[(dimensions - 1 - i) * tau];
    }

    // Center the historical vector using the existing mean before modifying the buffer
    for (int i = 0; i < dimensions; i++)
    {
        tdeOld[i] -= *runningMean;
    }

    float oldestValue = slidingWindow[0];
    slideWindow(slidingWindow, windowSize, newValue);
    updateMean(runningMean, slidingWindow, windowSize, oldestValue);

    embedding(tde, slidingWindow, dimensions, indexes);
    centerData(runningMean, tde, dimensions);

    // Update unscaled scatter matrix sums
    updateCovariance(runningCov, tde, tdeOld, dimensions);
}

void updateMean(float* runningMean, float* slidingWindow, int windowSize, float oldestValue)
{
    if (*runningMean == 0)
    {
        for (int i = 0; i < windowSize - 1; i++)
        {
            *runningMean = *runningMean + slidingWindow[i];
        }
        *runningMean = (*runningMean + oldestValue) / (float)windowSize;
        return;
    }
    *runningMean = *runningMean + (slidingWindow[windowSize - 1] - oldestValue) / (float)windowSize;
}

void centerData(float* runningMean, float* tde, int dimensions)
{
    for (int i = 0; i < dimensions; i++)
    {
        tde[i] = tde[i] - *runningMean;
    }
}

void copyArray(float* array1, float* array2, int dimensions)
{
    for (int i = 0; i < dimensions; i++)
    {
        array1[i] = array2[i];
    }
}

int indexAccessHelper(int row, int column, int dimensions)
{
    return (row * dimensions) + column;
}

void updateCovariance(float* runningCov, float* tde, float* tdeOld, int dimensions)
{
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            int covIdx = indexAccessHelper(i, j, dimensions);
            float dotProductNew = tde[i] * tde[j];
            float dotProductOld = tdeOld[i] * tdeOld[j];

            runningCov[covIdx] = runningCov[covIdx] - dotProductOld + dotProductNew;
        }
    }
}