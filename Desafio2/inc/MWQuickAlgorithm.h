#ifndef MWQUICKALGORITHM_H
#define MWQUICKALGORITHM_H

#include "MWCommon.h"

typedef struct {
    int32_t Mean;
    uint16_t numSamples;
} Mean;

void AddSampleToMean(Mean *mean, int32_t sample) {
    mean->Mean += sample;
    ++(mean->numSamples);
}

int32_t GetMean(Mean *mean) {
    if (mean->numSamples == 0) return 0;

    int32_t finalMean = mean->Mean/mean->numSamples;
    mean->Mean = 0; mean->numSamples = 0;
    return finalMean;
}

int32_t QuickPoly(int32_t x) {
    //1 + (x^2/720)*(-360 + (x^2)*(30 - x^2))
    int32_t x2 = x*x;

    return 1.0 + ((x2*2913)>>21)*(-360.0 + x2*(30.0 - x2));
}

clock_t RunQuickAlgorithm(int32_t *x) {
    clock_t start_time = 0, end_time = 0;
    int32_t mean = 0;
    int32_t qpoly = 0;
    Mean qpolyMean;

    start_time = clock();
    for (int j = 0; j < MAX_POLY_ITERATIONS; j++) {
        //calc poly
        qpoly = QuickPoly(x[j]);
        //add qpoly to mean
        AddSampleToMean(&qpolyMean, qpoly);
        //when j is divisible by 32, calc mean
        if ((j & 63) == 0) {
            mean += GetMean(&qpolyMean);
        }
    }
    end_time = clock();

    return end_time - start_time;
}

#endif
