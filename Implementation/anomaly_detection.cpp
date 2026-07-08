#include <fstream>
#include <iostream>
#include <vector>

#include "include/streamingData.hpp"
#include "include/AnomalyDetection.h"
#include "include/utils.h"

void writeData(std::string filePath, std::vector<float> fileToWrite, bool append = true)
{
    std::ofstream MyFile;
    if (append)
    {
        MyFile.open(filePath, std::ios_base::app);
    }
    else
    {
        MyFile.open(filePath);
    }

    if (!MyFile.is_open())
    {
        std::cerr << "Error: Could not open or create file at path: " << filePath << std::endl;
        return;
    }

    for (std::size_t i = 0; i < fileToWrite.size(); i += 2)
    {
        MyFile << fileToWrite.at(i) << "," << fileToWrite.at(i + 1) << std::endl;
    }
    MyFile.close();
}

int main()
{
    std::vector<float> writeToFile;
    std::cout << "Real time anomaly detection...." << std::endl;
    int i = 2;
    std::string fileInput = std::to_string(i);
    std::string absolutePath = "Data/" + fileInput + ".csv";
    streamData DataStream(absolutePath);

    // 1. Time Delay Embedding (TDE) Shape Settings
    int dimensions = 3;
    int tau = 200;
    int tdeSpan = (dimensions - 1) * tau; // 400 samples

    // 2. Sliding Window Analysis Capacity (k history elements)
    // Needs to be larger than tdeSpan to avoid division-by-zero!
    int windowSize = 1000;
    std::cout << "Sliding History Window Size (k): " << windowSize << std::endl;

    std::string line;

    // Allocate Data Containers
    std::vector<float> slidingWindow(windowSize, 0.0f);
    float tde[dimensions] = {0.0f};

    int tdeIndexes[dimensions];
    embeddingIndexes(tdeIndexes, windowSize, dimensions, tau);

    float runningMean = 0.0f;
    float runningCov[dimensions * dimensions] = {0.0f};

    float eigenvalues[dimensions] = {0.0f};
    float eigenvectors[dimensions * dimensions] = {0.0f};

    // Warm up and fill the initial window buffer completely
    for (int i = 0; i < windowSize; i++)
    {
        DataStream.next(line);
        if (line.empty())
        {
            break;
        }
        slidingWindow[i] = std::stof(line);
    }

    // Process the streaming timeline
    int sampleCounter = windowSize;
    while (DataStream.hasNext())
    {
        DataStream.next(line);
        if (line.empty())
        {
            break;
        }
        float value = std::stof(line);

        // 1. Update the incremental sliding properties
        PCA(&runningMean, runningCov, tde, slidingWindow.data(), dimensions, windowSize, value,
            tdeIndexes);
        sampleCounter++;

        // 2. Create a scaled matrix copy for the Jacobi solver
        float scaledCov[dimensions * dimensions];
        int numVectorsInWindow = windowSize - tdeSpan; // 1000 - 400 = 600 active vectors

        for (int m = 0; m < dimensions * dimensions; m++)
        {
            // Bounded division (Divides by 599, avoiding 0-division NaN)
            scaledCov[m] = runningCov[m] / (float)(numVectorsInWindow - 1);
        }

        // 3. Solve Eigenvalues/Eigenvectors using the stable matrix
        jacobiEigenvalue(scaledCov, dimensions, eigenvalues, eigenvectors);

        // 4. Locate dominant principal components
        int idx_pc1 = 0;
        int idx_pc2 = 0;
        findTopTwoComponents(eigenvalues, dimensions, &idx_pc1, &idx_pc2);

        // 5. Project current TDE state vector into the 2D plane
        float projected_X = 0.0f;
        float projected_Y = 0.0f;
        projectData(tde, eigenvectors, dimensions, idx_pc1, &projected_X);
        projectData(tde, eigenvectors, dimensions, idx_pc2, &projected_Y);

        // 6. Push coordinates sequentially into output vector
        writeToFile.push_back(projected_X);
        writeToFile.push_back(projected_Y);
    }

    // Write out the fresh data trajectory (False to overwrite cleanly)
    std::string outputPath = "Data/output.txt";
    writeData(outputPath, writeToFile, false);

    std::cout << "Done! Fingerprint data stored successfully." << std::endl;
    return 0;
}