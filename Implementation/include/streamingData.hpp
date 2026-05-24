#ifndef STREAMINGDATA_HPP
#define STREAMINGDATA_HPP

#include <fstream>
#include <iostream>

class streamData
{
  private:
    std::ifstream Stream;

  public:
    streamData(const std::string& filePath) : Stream(filePath)
    {
        std::string header;
        std::getline(Stream, header);
    };

    //~streamData()
    //{
    //  Stream.close();
    //};

    bool next(std::string& line)
    {
        return static_cast<bool>(std::getline(Stream, line));
    };

    void readData();
};

#endif