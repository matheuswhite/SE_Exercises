#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/MWQuickAlgorithm.h"
#include "inc/MWSlowAlgorithm.h"

#define TIMES 1000

int main(int argc, char const *argv[]) {
    clock_t non_optimized_code_time[TIMES], optimized_code_time[TIMES];
    double quickCosMean = 0, slowCosMean = 0, quickCosOld = 0, slowCosOld = 0;
    int32_t x[MAX_COS_ITERATIONS];

    for (int i = 0; i < TIMES; i++) {
        //srand(time(NULL));

        for (int j = 0; j < MAX_COS_ITERATIONS; j++) {
            x[j] = j+1;
        }

        non_optimized_code_time[i] = RunSlowAlgorithm(x);
        optimized_code_time[i] = RunQuickAlgorithm(x);
    }

    for (int i = 1; i <= TIMES; i++) {
        quickCosMean += optimized_code_time[i-1]/(double)i - quickCosOld/(double)i;
        slowCosMean  += non_optimized_code_time[i-1]/(double)i - slowCosOld/(double)i;

        quickCosOld = optimized_code_time[i-1];
        slowCosOld  = non_optimized_code_time[i-1];
    }

    printf("non_optimized_code_time: %f\noptimized_code_time: %f\nPercentage: %f%%", slowCosMean, quickCosMean, 100*(slowCosMean-quickCosMean)/slowCosMean);

    return 0;
}
