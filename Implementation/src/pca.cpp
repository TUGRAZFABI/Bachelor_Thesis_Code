#include "../include/pca.hpp"
#include <iostream>
#include <numeric>

void PCA ::learn(std::vector<std::vector<double>>& windows)
{
    int num_windows = windows.size();
    int embedding_dim = windows[0].size();
    global_mean.resize(embedding_dim, 0.0);

    // calculate global means for each n-th position of the vectors then center each
    // entry
    for (int pos_in_single_window = 0; pos_in_single_window < embedding_dim; pos_in_single_window++)
    {
        // mean calculation
        double sum = 0;
        for (int winPos = 0; winPos < num_windows; winPos++)
        {
            sum += windows[winPos][pos_in_single_window];
        }
        global_mean[pos_in_single_window] = sum / num_windows; // Store average

        // 2.0 center the data by substracting the mean (around 0,0)
        for (int win = 0; win < num_windows; win++)
        {
            windows[win][pos_in_single_window] -= global_mean[pos_in_single_window];
        }
    }

    // 3.0 compute the covariance matrix
    std::vector<std::vector<double>> cov(embedding_dim, std::vector<double>(embedding_dim, 0.0));
    for (int k = 0; k < embedding_dim; k++)
    {
        for (int pos = 0; pos < embedding_dim; pos++)
        {
            double sum = 0;
            for (int win = 0; win < num_windows; win++)
            {
                sum += windows[win][k] * windows[win][pos];
            }
            cov[k][pos] = sum / (num_windows - 1);
        }
    }

    // calculate eigenvalues and eigenmatrix

    for (int i = 0; i < embedding_dim; i++)
    {
        for (int j = 0; j < embedding_dim; j++)
        {
            // removed eigen
        }
    }

    // Compute eigenvectors and eigenvalues without library

    // Store eigenvalues and eigenvectors without library
}

std::vector<std::vector<double>> PCA::toPcaSpace(std::vector<std::vector<double>>& windows)
{
    int num_windows = windows.size();
    int d = windows[0].size(); // Original dimension (100)

    std::vector<std::vector<double>> result(num_windows, std::vector<double>(n_dimensions));

    for (int i = 0; i < num_windows; i++)
    {
        // for the n-compontents PC1,Pc2....
        for (int comp = 0; comp < n_dimensions; comp++)
        {
            double score = 0;

            // Dot product of centered windows and eigenvectors
            for (int j = 0; j < d; j++)
            {
                double centered = windows[i][j] - global_mean[j];
                // score += centered * eigenvectors(j, eigenvectors.cols() - 1 - comp);
                //  largest eigenvectors at the end.
            }

            result[i][comp] = score;
        }
    }

    return result;
}
