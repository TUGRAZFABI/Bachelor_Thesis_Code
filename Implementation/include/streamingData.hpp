#ifndef STREAMINGDATA_HPP
#define STREAMINGDATA_HPP

#include <fstream>
#include <iostream>

class streamData
{
  private:
    double current;
    double next;
    bool has_next;

  public:
    streamData();
    void readData(std::string FilePath);
};

#endif