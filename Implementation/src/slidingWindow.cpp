#include "../include/slidingWindow.hpp"
#include "../include/streamingData.hpp"

float* slidingWindow::returnSlidingWindow(streamData& DataStream)
{
    std::string line;
    for (int i = 0; i < windowSize; i++)
    {
        DataStream.next(line);
        float value = std::stof(line);
        setValueIndex(i, value);
        // std::cout << "test at index" << i << "value" << value;
    }

    return SLIDING_WINDOW;
}