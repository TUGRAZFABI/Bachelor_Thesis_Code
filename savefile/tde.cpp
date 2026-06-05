#include "../include/tde.hpp"

void TDE::embedding(slidingWindow& SlidingWindow, vector& output)
{

    int m = output.returnSize();
    int w = SlidingWindow.getWindowSize() - 1;
    for (int i = 0; i < m; i++)
    {
        int xt = w - i * tau;
        output.setAtIndex(i, SlidingWindow.getValueIndex(xt));
    }
}