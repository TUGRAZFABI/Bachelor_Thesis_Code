#include <fstream>
#include <iostream>
#include <vector>

#include "include/streamingData.hpp"
#include "include/AnomalyDetection.h"
#include "include/utils.h"

void writeData(std::string filePath, std::vector<double> fileToWrite, bool append = true)
{
    std::ofstream MyFile;

    if (append)
    {
        MyFile.open(filePath, std::ios_base::app); // append mode
    }
    else
    {
        MyFile.open(filePath); // overwrite mode (default)
    }

    for (std::size_t i = 0; i < fileToWrite.size(); i++)
    {
        MyFile << fileToWrite.at(i) << std::endl;
    }

    MyFile.close();
}

/*void printSlidingWindow(slidingWindow window, int windowSize)
{
    for (int i = 0; i < windowSize; i++)
    {
        std::cout << "[" << window.getValueIndex(i) << "]";
    }
    std::cout << std::endl;
}*/

int main()
{
    std::cout << "Real time anomaly detection...." << std::endl;
    float average = 0;
    for (int i = 1; i <= 30; i++)
    {
        if (i == 5 || i == 13 || i == 14 || i == 16)
        {
            i++;
            if (i == 14)
            {
                i++;
            }
        }
        std::string fileInput = std::to_string(i);
        // std::string fileInput = "01 - m1_half_shaft_speed_no_mechanical_load";
        std::string absolutePath = "Data/" + fileInput + ".csv";
        streamData DataStream(absolutePath);

        // init of the TDE
        int dimensions = 3;
        int tau = 2;
        int minObservations = 1 + (dimensions - 1) * tau;

        // calculate the indexes which are static doesnt need to recaltulate each iteration
        // calculateTDEIndexes(&tde, inputStep.getWindowSize());

        // next line to read:
        std::string line;

        // Init of all data containers
        float slidingWindow[minObservations];
        float tde[dimensions];
        float pca[minObservations];
        int tdeIndexes[dimensions];
        embeddingIndexes(tdeIndexes, minObservations, dimensions, tau);

        // running mean running cov
        float runningMean[dimensions];
        float runningCov[dimensions * dimensions]; // flat 1d matrix

        //
        for (int i = 0; i < minObservations; i++)
        {
            DataStream.next(line);
            if (line.empty())
            {
                break;
            }
            float value = std::stof(line);
            slideWindow(slidingWindow, minObservations, value);
        }

        float tmp = 0;
        float tmp2 = 0;
        float alpha = 0.05;
        //(0.5, 0.05, and 0.005 , 0.001, 0.0005)

        while (DataStream.hasNext())
        {
            embedding(tde, slidingWindow, dimensions, tdeIndexes);
            // printAnyArray(tde, dimensions);
            tmp = tmp + 1;
            tmp2 = tmp2 + tde[2];

            // updateCovariance(runningCov, tde, runningMean, dimensions);
            // printAnyArray(runningCov, dimensions * dimensions);
            updateMean(runningMean, tde, dimensions, alpha);
            // slide window
            DataStream.next(line);
            if (line.empty())
            {
                break;
            }
            float value = std::stof(line);
            slideWindow(slidingWindow, minObservations, value);
        }
        std::cout << "File input:" << fileInput << std ::endl;
        float correctMean = tmp2 / tmp;
        printf("Total evaluated values: %.1f\nResult with given n: %.2f \nalpha:%.4f "
               "\nResult with "
               "EWMA: %.3f \ndelta :%.3f \n",
               tmp, correctMean, alpha, runningMean[1], correctMean - runningMean[1]);
        average += correctMean - runningMean[1];
        std::cout << "Der average" << average / i - 4 << std::endl;
        std::cout << "Percentage" << ((correctMean - runningMean[1]) / correctMean) * 100 << "%"
                  << std::endl;
    }

    return 0;
}
