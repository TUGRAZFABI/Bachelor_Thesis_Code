#include <fstream>
#include <iostream>
#include <vector>
#include "include/pca.hpp"
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

void displayVectorofVectors(std::vector<std::vector<double>> data)
{
    for (const auto& innerVector : data)
    {
        int i = 0;
        for (const auto& value : innerVector)
        {
            if (i == 2)
            {
                std::cout << value << " ";
            }

            i++;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "Welcome to the Vizualizer...." << std::endl;

    std::string input = "01 - m1_half_shaft_speed_no_mechanical_load";
    streamData DataStream;
    DataStream.readData(input);

    return 0;
}
