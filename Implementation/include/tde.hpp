#ifndef TDE_HPP
#define TDE_HPP

#include <vector>

class TDE
{
  private:
    int d;
    int stride;
    int tau;
    std::vector<double> values;

  public:
    // constructors
    TDE(int embedding_dimension, const std::vector<double>& data, int stride_val = 1,
        int tau_val = 1);
    TDE();

    // main method
    std::vector<std::vector<double>> time_delay_embedding();
    // Overloaded method.
    std::vector<std::vector<double>> time_delay_embedding(const std::vector<double>& values);
};

#endif // TDE_HPP