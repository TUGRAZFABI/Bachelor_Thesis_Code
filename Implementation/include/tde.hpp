#ifndef TDE_HPP
#define TDE_HPP

#include "../include/slidingWindow.hpp"

class TDE
{
  private:
    int dimension;
    int stride;
    int tau;

    int size_;

    float* TDE_EMBEDDING;

  public:
    // constructors
    TDE(int embedding_dimension, int stride_val, int tau_val, int size)
        : dimension(embedding_dimension), stride(stride_val), tau(tau_val), size_(size)
    {
        TDE_EMBEDDING = new float[size_];
    };

    float getValueIndex(int index)
    {
        return TDE_EMBEDDING[index];
    }

    void setValueIndex(int index, float value)
    {
        TDE_EMBEDDING[index] = value;
    }

    void embedding(slidingWindow& SlidingWindow) {}
};

#endif // TDE_HPP