#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/MWQuickAlgorithm.h"
#include "inc/MWSlowAlgorithm.h"

int main(int argc, char const *argv[]) {
    clock_t non_optimized_code_time[1000], optimized_code_time[1000];
    int16_t quickCosMean = 0, slowCosMean = 0, quickCosAcc = 0, slowCosAcc = 0;
    double angles[MAX_COS_ITERATIONS];

    srand(time(NULL));

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < MAX_COS_ITERATIONS; j++) {
            angles[j] = 359;//rand() % 360;
            angles[j] = (angles[j]*0.017) - 3.14;
            printf("Angle %d: %f\n", j, angles[j]);
        }

        non_optimized_code_time[i] = RunSlowAlgorithm(angles);
        optimized_code_time[i] = RunQuickAlgorithm(angles);
    }

    for (int i = 1; i <= 1000; i++) {
        quickCosAcc += optimized_code_time[i-1];
        slowCosAcc  += non_optimized_code_time[i-1];

        if ((i % 10) == 0) {
            quickCosMean = quickCosAcc/10;
            slowCosMean  = slowCosAcc/10;

            quickCosAcc = 0;
            slowCosAcc  = 0;
        }
    }

    printf("non_optimized_code_time: %d\noptimized_code_time: %d\nPercentage: %f%%", slowCosMean, quickCosMean, (float)(slowCosMean-quickCosMean)/slowCosMean);

    return 0;
}
