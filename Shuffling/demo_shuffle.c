#include <stdio.h>
#include <stdlib.h>
#include "riffle.c"

int main() {
    
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int numLen = sizeof(numbers) / sizeof(int);

    printf("Initial integer array is [");
    for (int i = 0; i < numLen; i++) {
        printf("%d,", numbers[i]);
    }
    printf("]\n");

    riffle(numbers, numLen, sizeof(int), 100);
    int check = check_shuffle(numbers, numLen, sizeof(int), cmp_int);
    printf("Check %s\n", check?"Passed" : "Failed");

    printf("Shuffled array of integers is [");
    for (int i = 0; i < numLen; i++) {
        printf("%d,", numbers[i]);
    }
    printf("]\n");

    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta",
                     "eta", "theta", "iota", "kappa", "lambda", "mu"};
    int greekLen = sizeof(greek) / sizeof(char *);

    printf("Initial greek letter array is [");
    for (int i = 0; i < greekLen; i++) {
        printf("%s,", greek[i]);
    }
    printf("]\n");

    riffle(greek, greekLen, sizeof(char *), 5);
    check = check_shuffle(greek, greekLen, sizeof(char *), cmp_str);
    printf("Check %s\n", check?"Passed" : "Failed");

    printf("Shuffled array of Greek letters is [");
    for (int i = 0; i < greekLen; i++) {
        printf("%s,", greek[i]);
    }
    printf("]\n");

    return 0;
}
