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
    std::string line;

    // Settings of sliding window and tde vector.
    int dimensions = 3;
    int tau = 200;
    int windowSize = 1000;

    float slidingWindow[windowSize] = {0.0f};
    float tde[dimensions] = {0.0f};

    int tdeIndexes[dimensions];
    embeddingIndexes(tdeIndexes, windowSize, dimensions, tau);

    float runningMean = 0.0f;
    float runningCov[dimensions * dimensions] = {0.0f};

    float eigenvalues[dimensions] = {0.0f};
    float eigenvectors[dimensions * dimensions] = {0.0f};

    float outX = 0.0f;
    float outY = 0.0f;

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

    while (DataStream.hasNext())
    {
        DataStream.next(line);
        if (line.empty())
        {
            break;
        }
        float value = std::stof(line);

        processNewDataPoint(value, tde, slidingWindow, &runningMean, runningCov, eigenvalues,
                            eigenvectors, tdeIndexes, windowSize, dimensions, &outX, &outY);

        writeToFile.push_back(outX);
        writeToFile.push_back(outY);
    }

    std::string outputPath = "Data/output.txt";
    writeData(outputPath, writeToFile, false);
    return 0;
}