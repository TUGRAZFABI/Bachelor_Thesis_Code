#include "../include/tde.hpp"

void TDE::embedding(slidingWindow& SlidingWindow, Matrix& output)
{
    int windowSize = SlidingWindow.getWindowSize();
    for (int row = 0; row < windowSize - (dimension - 1) * tau; row++)
    {
        for (int col = 0; col < dimension; col++)
        {
            int xt = row + col * tau;
            output.at(row, col) = SlidingWindow.getValueIndex(xt);
        }
    }
}