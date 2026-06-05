#include "../include/tde.h"

void tdeInit(TDE* tde, int dimension, int tau)
{
    tde->dimension_ = dimension;
    tde->tau_ = tau;
}
