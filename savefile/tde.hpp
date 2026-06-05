#ifndef TDE_HPP
#define TDE_HPP

#include "../include/slidingWindow.hpp"
#include "../include/vector.h"
class TDE
{
  private:
    int dimension;
    int tau;

  public:
    // constructors
    TDE(int embedding_dimension, float delay) : dimension(embedding_dimension), tau(delay) {};

    void embedding(slidingWindow& SlidingWindow, Vector& output);
};

#endif // TDE_HPP