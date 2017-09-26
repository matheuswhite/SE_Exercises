#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    int32_t Mean;
    uint16_t numSamples;
} Mean;

void AddSampleToMean(Mean *mean, int16_t sample) {
    mean->Mean += sample;
    ++(mean->Mean);
}

int16_t GetMean(Mean *mean) {
    int16_t finalMean = mean->Mean/mean->numSamples;
    mean->Mean = 0; mean->numSamples = 0;
    return finalMean;
}

int16_t qcos(int16_t rad) {
    //1 - x^2/2 + x^4/24 + x^6/720
    int32_t rad2 = rad*rad;
    int32_t rad4 = rad2*rad2;
    int32_t rad6 = rad4*rad2;

    return 1 - (rad2 >> 1) + ((rad4*2731)>>16) + ((rad6*2913)>>21);
}

int16_t scos(int16_t rad) {
    return 0;//cos (rad/1000.0);
}

int main(int argc, char const *argv[]) {
    clock_t start_time = 0, end_time = 0;
    clock_t non_optimized_code_time[1000], optimized_code_time[1000];
    Mean qcosMean, scosMean, qcosTotal, scosTotal;
    int16_t cos_value = 0;
    int16_t oldestCos = 0;
    int16_t _qcosTotal = 0, _scosTotal = 0, _qcosMean = 0, _scosMean = 0;

    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        //initialization
        cos_value = (rand() % 6280) - 3140;

        //non-optimized code
        start_time = clock();
        for (int j = 0; j < 512; j++) {
            scosMean.Mean += (scos(cos_value)/scosMean.numSamples) - (oldestCos/scosMean.numSamples);
            ++(scosMean.numSamples);
            if ((i % 32) == 0) {
                _scosMean += scosMean.Mean;
            }
        }
        end_time = clock();
        non_optimized_code_time[i] = end_time - start_time;

        //optimized code
        start_time = clock();
        for (int j = 0; j < 512; j++) {
            AddSampleToMean(&qcosMean, qcos(cos_value));
            if ((i & 31) == 0) {
                _qcosMean += GetMean(&qcosMean);
            }
        }
        end_time = clock();
        optimized_code_time[i] = end_time - start_time;

        //total mean
        AddSampleToMean(&qcosTotal, optimized_code_time[i]);
        AddSampleToMean(&scosTotal, non_optimized_code_time[i]);

        if ((i & 31) == 0) {
            _qcosTotal += GetMean(&qcosTotal);
            _scosTotal += GetMean(&scosTotal);
        }
    }
    _qcosTotal += GetMean(&qcosTotal);
    _scosTotal += GetMean(&scosTotal);

    printf("non_optimized_code_time: %d\noptimized_code_time: %d\n Percentage: %d%%", _scosTotal, _qcosTotal, _scosTotal-(_qcosTotal/_scosTotal));

    return 0;
}
