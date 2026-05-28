#include "../include/slidingWindow.hpp"
#include "../include/streamingData.hpp"

void slidingWindow::returnSlidingWindow(streamData& DataStream)
{
    std::string line;
    for (int i = 0; i < windowSize; i++)
    {
        DataStream.next(line);
        if (line.empty()) // handling an case where the line is not an float.
        {
            break;
        }
        float value = std::stof(line);
        setValueIndex(i, value);
    }
}

void slidingWindow::slideWindow(streamData& DataStream)
{
    for (int i = 0; i < windowSize - slideStep; i++)
    {
        setValueIndex(i, getValueIndex(i + slideStep));
    }

    std::string line;
    for (int j = windowSize - slideStep; j < windowSize; j++)
    {
        DataStream.next(line);
        if (line.empty())
        {
            break;
        }
        float value = std::stof(line);
        setValueIndex(j, value);
    }
}