#ifndef TDE_HPP
#define TDE_HPP

#include "../include/matrix.hpp"
#include "../include/slidingWindow.hpp"

class TDE
{
  private:
    int dimension;
    int tau;

  public:
    // constructors
    TDE(int embedding_dimension, float delay) : dimension(embedding_dimension), tau(delay) {};

    void embedding(slidingWindow& SlidingWindow, Matrix& output);
};

#endif // TDE_HPP