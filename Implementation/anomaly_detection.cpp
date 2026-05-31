#include <fstream>
#include <iostream>
#include <vector>
#include "include/matrix.hpp"
#include "include/pca.hpp"
#include "include/slidingWindow.hpp"
#include "include/streamingData.hpp"
#include "include/tde.hpp"

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

    // init of the sliding window
    int slideStep = 2;
    int windowSize = 10;
    slidingWindow window(windowSize, slideStep);

    // Main routine:
    std::string next_;
    window.returnSlidingWindow(DataStream);

    // init of the TDE
    int m = 2;
    int tau = 1;

    TDE tde(m, tau);
    Matrix tdeResult(windowSize, m);

    while (DataStream.hasNext())
    {
        window.slideWindow(DataStream);
        // printSlidingWindow(window, windowSize);

        tde.embedding(window, tdeResult);
        tdeResult.DEBUG_PRINT();
        break;
    }
    return 0;
}
