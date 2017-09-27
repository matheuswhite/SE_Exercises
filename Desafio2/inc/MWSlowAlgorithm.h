#ifndef MWSLOWALGORITHM_H
#define MWSLOWALGORITHM_H

#include "MWCommon.h"

int32_t SlowCos(int32_t x) {
    return cos(x);
}

clock_t RunSlowAlgorithm(int32_t *x) {
    clock_t start_time = 0, end_time = 0;
    int32_t scos = 0;
    int32_t mean = 0, oldestCos = 0, temp = 0;
    uint16_t numSamples = 0;

    start_time = clock();
    for (int j = 0; j < MAX_COS_ITERATIONS; j++) {
        //calc cos
        scos = SlowCos(x[j]);
        //calc mean
        ++numSamples;
        mean += scos/numSamples - oldestCos/numSamples;
        //when j is divisible by 32, do something
        if ((j % 64) == 0) {
            temp += mean;
        }
        oldestCos = scos;
    }
    end_time = clock();

    return end_time - start_time;
}

#endif
