#ifndef MWSLOWALGORITHM_H
#define MWSLOWALGORITHM_H

#include "MWCommon.h"

clock_t RunSlowAlgorithm(double *angles) {
    clock_t start_time = 0, end_time = 0;
    double scos = 0;
    int16_t mean = 0, oldestCos = 0, temp = 0;
    uint16_t numSamples = 0;

    start_time = clock();
    for (int j = 0; j < MAX_COS_ITERATIONS; j++) {
        //calc cos
        scos = cos(angles[j]);
        printf("Scos: %f\n", scos);
        //calc mean
        ++numSamples;
        mean += scos/numSamples - oldestCos/numSamples;
        //when j is divisible by 32, do something
        if ((j % 32) == 0) {
            temp += mean;
        }
        oldestCos = scos;
    }
    end_time = clock();

    return end_time - start_time;
}

#endif
