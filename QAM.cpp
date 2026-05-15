#include "QAM.h"
#include <math.h>
#include <stdexcept>
#include <iostream>

QAM::QAM(int M): M(M) {
    if (M != 4 && M != 16 && M !=64) {
        throw std::invalid_argument("Incorrect value");
    }
    bpc = static_cast<int>(std::sqrt(M));

    generateConstellation();
    normalize();
}

void QAM::generateConstellation() {
    
    constellation.clear();

    for (int Rs = 0; Rs <  2 * bpc; Rs+=2) {
        for (int Ims = 0; Ims < 2 * bpc; Ims +=2) {
            double Re = (bpc - 1) - Rs;
            double Im = (bpc-1) - Ims;
            constellation.push_back(std::complex<double>(Re, Im));
        }
    }
}

void QAM::normalize() {
    double Power = 0.0;
    for (const auto& p: constellation) {
        Power += std::norm(p);
    }
    Power /= constellation.size();
    for (auto& p: constellation) {
        p /= std::sqrt(Power);
    }
}

std::vector<std::complex<double>> QAM::modulate(const std::vector<int>& inputBits) {
    std::vector<std::complex<double>> Signal;
    size_t bps = static_cast<size_t>(std::log2(M));

    for (size_t i = 0; i < inputBits.size(); i += bps) {
        size_t sIndx = 0;
    
        for (int b = 0; b < bps; b++) {
            sIndx |= (inputBits[i + b] << (bps - 1 - b));
        }
        Signal.push_back(constellation[sIndx]) ;
    }   
    return Signal;
}

std::vector<int> QAM::demodulate(const std::vector<std::complex<double>>& inputSignal) {
    std::vector<int> bits;
    size_t bps = static_cast<size_t>(std::log2(M));

    for (const auto& s: inputSignal) {
            int indx = 0;
            double min = std::norm(s - constellation[0]);

            for (int i = 1; i < M; i ++) {
                double distance = std::norm(s - constellation[i]);
                if (distance < min) {
                    min = distance;
                    indx = i;
                }
            }
        for (int b = bps - 1; b >= 0; b--) {
            bits.push_back((indx >> b) & 1);
        }
    }

    return bits;
}