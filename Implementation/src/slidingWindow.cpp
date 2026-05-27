#include "../include/slidingWindow.hpp"
#include "../include/streamingData.hpp"

float* slidingWindow::returnSlidingWindow(streamData& DataStream)
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
        // std::cout << "test at index" << i << "value" << value;
    }

    return SLIDING_WINDOW;
}

void slidingWindow::slideWindow(streamData& DataStream)
{
    std::string line;
    for (int i = 0; i < windowSize + slideStep; i++)
    {
        int currentSlideIndex = i - slideStep;
        if (currentSlideIndex >= 0 && currentSlideIndex < windowSize - slideStep)
        {
            setValueIndex(currentSlideIndex, getValueIndex(currentSlideIndex));
        }
        else if (currentSlideIndex >= windowSize - slideStep)
        {
            DataStream.next(line);
            if (line.empty())
            {
                break;
            }
            float value = std::stof(line);
            setValueIndex(currentSlideIndex, value);
        }
        std::cout << "index" << i << "," << getValueIndex(currentSlideIndex) << ","
                  << currentSlideIndex << std::endl;
    }
}