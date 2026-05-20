#include "../include/streamingData.hpp"
#include "../include/slidingWindow.hpp"

streamData::streamData() {};

void streamData::readData(std::string FilePath)
{
    std::string absolutePath = "Data/" + FilePath + ".csv";
    std::cout << "Das ist der file path" << absolutePath;

    std::ifstream ReadFile(absolutePath);
    std::string text;

    while (getline(ReadFile, text))
    {
        std::cout << text << std::endl;
        _sleep(1);
    }

    ReadFile.close();
}