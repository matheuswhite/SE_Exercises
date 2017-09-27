#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/MWQuickAlgorithm.h"
#include "inc/MWSlowAlgorithm.h"

#define TIMES 1000

int main(int argc, char const *argv[]) {
    clock_t non_optimized_code_time[TIMES], optimized_code_time[TIMES];
    double quickPolyMean = 0, slowPolyMean = 0, quickPolyOld = 0, slowPolyOld = 0;
    int32_t x[MAX_POLY_ITERATIONS];

    for (int i = 0; i < TIMES; i++) {
        //srand(time(NULL));

        for (int j = 0; j < MAX_POLY_ITERATIONS; j++) {
            x[j] = j+1;//rand() % 100 + 1;
        }

        non_optimized_code_time[i] = RunSlowAlgorithm(x);
        optimized_code_time[i] = RunQuickAlgorithm(x);
    }

    for (int i = 1; i <= TIMES; i++) {
        quickPolyMean += optimized_code_time[i-1]/(double)i - quickPolyOld/(double)i;
        slowPolyMean  += non_optimized_code_time[i-1]/(double)i - slowPolyOld/(double)i;

        quickPolyOld = optimized_code_time[i-1];
        slowPolyOld  = non_optimized_code_time[i-1];
    }

    printf("non_optimized_code_time: %f\noptimized_code_time: %f\nPercentage: %f%%", slowPolyMean, quickPolyMean, 100*(slowPolyMean-quickPolyMean)/slowPolyMean);

    return 0;
}
