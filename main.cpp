#include <iostream>
#include "QAM.h"
#include "AWGNgenerator.h"
#include <vector>
#include <fstream>


double BERcalculation(const std::vector<int>& startBits, const std::vector<int>& endBits) {
    int errors = 0;
    size_t size = startBits.size();

    for (size_t i = 0; i < size; i++) {
        if (startBits[i] != endBits[i]) {
            errors++;
        }
    }

    double ber = static_cast<double>(errors)/ static_cast<double>(size);
    return ber;
}

int main() {
    
    size_t numbits = 1e7;
    std::vector<int> inputbits(numbits);
    
    std::default_random_engine generator(static_cast<size_t>(time(0)));

    std::uniform_int_distribution<int> binary(0,1);

    for (size_t i = 0; i < numbits; i++) {
        inputbits[i] = binary(generator);
    }
    
    QAM qpsk(4);
    QAM qam_16(16);
    QAM qam_64(64);

    std::ofstream outputQSPK("QSPK.txt");
    std::ofstream outputQAM_16("QAM16.txt");
    std::ofstream outputQAM_64("QAM64.txt");

    //моделируем
    auto qpsksgn = qpsk.modulate(inputbits);
    auto qam_16_sgn = qam_16.modulate(inputbits);
    auto qam_64_sgn = qam_64.modulate(inputbits);

    for (int db = 1; db < 30; db++) {

        //создаём и добавляем шум
        AWGNGenerator noise_4(db, 4, 4);
        AWGNGenerator noise_16(db, 4, 16);
        AWGNGenerator noise_64(db, 4, 64);
        auto qpskn = noise_4.addNoise(qpsksgn);
        auto qam_16_n = noise_16.addNoise(qam_16_sgn);
        auto qam_64_n = noise_64.addNoise(qam_64_sgn);

        //демодулируем
        auto result_qspk = qpsk.demodulate(qpskn);
        auto result_qam_16 = qam_16.demodulate(qam_16_n);
        auto result_qam_64 = qam_64.demodulate(qam_64_n);

        //считаем BER
        auto ber_qspk = BERcalculation(inputbits, result_qspk);
        auto ber_qam_16 = BERcalculation(inputbits, result_qam_16);
        auto ber_qam_64 = BERcalculation(inputbits, result_qam_64);

        outputQSPK << db << " " << ber_qspk << std::endl;
        outputQAM_16 << db << " " << ber_qam_16 << std::endl;
        outputQAM_64 << db << " " << ber_qam_64 << std::endl;
        
    }

    outputQSPK.close();
    outputQAM_16.close();
    outputQAM_64.close();

}