#include <fstream>
#include <iostream>
#include "include/pca.hpp"
#include "include/slidingWindow.hpp"
#include "include/streamingData.hpp"
#include "include/tde.h"
#include "include/vector.h"

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

void printSlidingWindow(slidingWindow window, int windowSize)
{
    for (int i = 0; i < windowSize; i++)
    {
        std::cout << "[" << window.getValueIndex(i) << "]";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Real time anomaly detection...." << std::endl;

    // std::string fileInput = "01 - m1_half_shaft_speed_no_mechanical_load";
    std::string fileInput = "test";
    std::string absolutePath = "Data/" + fileInput + ".csv";
    streamData DataStream(absolutePath);

    // init of the TDE
    int dimensions = 3;
    int tau = 2;

    TDE tde;
    tdeInit(&tde, dimensions, tau);

    int minObservations = 1 + (dimensions - 1) * tau;

    // init of the vector used for the tde
    Vector tdeResult;
    vectorInit(&tdeResult, minObservations);

    // init of the sliding window
    slidingWindow inputStep(minObservations, 1);
    inputStep.returnSlidingWindow(DataStream);

    while (DataStream.hasNext())
    {
        printSlidingWindow(inputStep, minObservations);
        embedding(&tde, &tdeResult, inputStep.returnWindowAsArray(), inputStep.getWindowSize());
        inputStep.slideWindow(DataStream);
    }
    return 0;
}
