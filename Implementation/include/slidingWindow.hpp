#ifndef SLIDINGWINDOW_HPP
#define SLIDINGWINDOW_HPP

#include "../include/streamingData.hpp"

class slidingWindow
{
  private:
    int windowSize;
    int slideStep;
    float* SLIDING_WINDOW;

  public:
    slidingWindow(int sizeWindow, int step) : windowSize(sizeWindow), slideStep(step)
    {
        SLIDING_WINDOW = new float[windowSize];
    }

    // getter setter
    float getValueIndex(int index)
    {
        return SLIDING_WINDOW[index];
    }

    void setValueIndex(int index, float value)
    {
        SLIDING_WINDOW[index] = value;
    }

    int getWindowSize()
    {
        return windowSize;
    }

    void returnSlidingWindow(streamData& DataStream);
    void slideWindow(streamData& DataStream);
};

#endif