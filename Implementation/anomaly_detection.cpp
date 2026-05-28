#include <fstream>
#include <iostream>
#include <vector>
#include "include/pca.hpp"
#include "include/slidingWindow.hpp"
#include "include/streamingData.hpp"
#include "include/tde.hpp"

std::vector<double> readFile(std::string filePath) // later this is the stream
{
    std::vector<double> data;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line))
    {
        double value = std::stod(line);
        data.push_back(value);
        // std::cout << "this is the value:" << value <<std::endl;
    }

    return data;
}

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

    while (DataStream.hasNext())
    {
        window.slideWindow(DataStream);
        printSlidingWindow(window, windowSize);
    }
    return 0;
}
