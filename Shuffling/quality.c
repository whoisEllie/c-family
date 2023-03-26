#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.c"

int main() {
    srand(time(NULL)); // seed the random number generator
    int N = 50;
    for (int shuffles = 1; shuffles <= 15; shuffles++) {
        float avg_q = average_quality(N, shuffles, 30);
        printf("Shuffles: %d, Average Quality: %f\n", shuffles, avg_q);
    }
    return 0;
}
