#pragma once

#include <vector>
#include <math.h>
#include <random>
#include <complex>

class AWGNGenerator {
    public:
        AWGNGenerator (double snr, size_t seed, double M);
        std::vector<std::complex<double>> addNoise(const std::vector<std::complex<double>>& sgnl);
    private:
        double snr;
        double bps;
        std::default_random_engine generator;
};