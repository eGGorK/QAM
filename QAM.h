#pragma once

#include <vector>
#include <complex>

class QAM {
    public:
        QAM(int M);

        std::vector<std::complex<double>> modulate(const std::vector<int>& inputBits);

        std::vector<int> demodulate(const std::vector<std::complex<double>>& inputSignal);
        private:
        int M;
        int bpc;
        std::vector<std::complex<double>> constellation;
        void generateConstellation();
        void normalize();
};