#include "../include/tde.hpp"
#include <vector>

TDE::TDE(int embedding_dimension, const std::vector<double>& data, int stride_val, int tau_val)
    : d(embedding_dimension), stride(stride_val), tau(tau_val), values(data)
{
}

TDE::TDE() : d(1), stride(1), tau(1) {}

std::vector<std::vector<double>> TDE::time_delay_embedding(const std::vector<double>& values)
{
    std::vector<std::vector<double>> windows;

    signed int index = 0;
    signed int length = values.size();
    while (index <= length - d)
    {
        std::vector<double> window;
        for (signed int i = index; i <= index + d * tau; i += tau)
        {
            if (i > length)
            {
                return windows;
            }
            window.push_back(values[i]);
        }
        windows.push_back(window);
        index += stride;
    }

    return windows;
}
