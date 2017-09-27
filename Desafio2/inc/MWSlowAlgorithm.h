#ifndef MWSLOWALGORITHM_H
#define MWSLOWALGORITHM_H

#include "MWCommon.h"

int32_t SlowPoly(int32_t x) {
    //1 - (x^2)/2 + (x^4)/24 - (x^6)/720

    return 1 - (int64_t)x*x/2 + (int64_t)x*x*x*x/24 - (int64_t)x*x*x*x*x*x/720;
}

clock_t RunSlowAlgorithm(int32_t *x) {
    clock_t start_time = 0, end_time = 0;
    int32_t spoly = 0;
    int32_t mean = 0, oldestPoly = 0, temp = 0;
    uint16_t numSamples = 0;

    start_time = clock();
    for (int j = 0; j < MAX_POLY_ITERATIONS; j++) {
        //calc poly
        spoly = SlowPoly(x[j]);
        //calc mean
        ++numSamples;
        mean += spoly/numSamples - oldestPoly/numSamples;
        //when j is divisible by 32, do something
        if ((j % 64) == 0) {
            temp += mean;
        }
        oldestPoly = spoly;
    }
    end_time = clock();

    return end_time - start_time;
}

#endif
