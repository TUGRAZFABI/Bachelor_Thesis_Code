#ifndef PCA_HPP
#define PCA_HPP
#include <vector>

class PCA
{
  private:
    int n_dimensions;
    std::vector<double> global_mean;

  public:
    PCA(int dimensions) : n_dimensions(dimensions) {}

    void learn(std::vector<std::vector<double>>& windows);
    std::vector<std::vector<double>> toPcaSpace(std::vector<std::vector<double>>& windows);
};

#endif
