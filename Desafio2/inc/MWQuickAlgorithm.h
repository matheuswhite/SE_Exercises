#ifndef MWQUICKALGORITHM_H
#define MWQUICKALGORITHM_H

#include "MWCommon.h"

typedef struct {
    int32_t Mean;
    uint16_t numSamples;
} Mean;

void AddSampleToMean(Mean *mean, int16_t sample) {
    mean->Mean += sample;
    ++(mean->numSamples);
}

int16_t GetMean(Mean *mean) {
    if (mean->numSamples == 0) return 0;

    int16_t finalMean = mean->Mean/mean->numSamples;
    mean->Mean = 0; mean->numSamples = 0;
    return finalMean;
}

int32_t QuickCos(double rad) {
    //1 - (x^2/720)*(360 + (x^2)*(30 - x^2))
    int32_t rad2 = rad*rad;
    int32_t temp = 30 - rad2;
    temp = 360 + rad2*temp;
    temp = 1 - ((rad2*2913)>>21)*temp;

    return temp;
}

clock_t RunQuickAlgorithm(double *angles) {
    clock_t start_time = 0, end_time = 0;
    int16_t mean = 0;
    int32_t qcos = 0;
    Mean qcosMean;

    start_time = clock();
    for (int j = 0; j < MAX_COS_ITERATIONS; j++) {
        //calc cos and add to mean
        qcos = QuickCos(angles[j]);
        printf("Qcos %f:\n", qcos);
        AddSampleToMean(&qcosMean, qcos);
        //when j is divisible by 32, calc mean
        if ((j & 31) == 0) {
            mean += GetMean(&qcosMean);
        }
    }
    end_time = clock();

    return end_time - start_time;
}

#endif
