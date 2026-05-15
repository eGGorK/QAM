#include "AWGNgenerator.h"

AWGNGenerator::AWGNGenerator(double snr, size_t seed, double M): snr(snr), generator(seed), bps(std::log2(M)) {}

std::vector<std::complex<double>> AWGNGenerator::addNoise(const std::vector<std::complex<double>>& sgnl) {
    std::vector<std::complex<double>> noisySignal = sgnl;
    std::normal_distribution<double> distribution(0.0, std::sqrt(1/(2* std::pow(10, snr/10))));
    for (auto& p: noisySignal) {
        double nR = distribution(generator);
        double nIm = distribution(generator);
        p += std::complex<double>(nR, nIm);
    }
    
    return noisySignal;
}