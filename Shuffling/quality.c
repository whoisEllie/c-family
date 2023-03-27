#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.c"

#define ITERATIONS 15

int main(int argc, char* argv[]) {

	int iterations = ITERATIONS;

	if (argc == 2)
	{
		if(atoi(argv[1]))
		{
			iterations = atoi(argv[1]);
		}
	}
	srand(time(NULL)); // Set the rand seed to the current unix time
	int N = 50;
	float avg = 0;
	for (int i = 1; i <= iterations; i++) {
		avg = average_quality(N, i, 30);
		printf("By shuffle %d the average quality is %f\n", i, avg);
	}
	printf("The final average quality after %d runs is %f.\n", iterations, avg);
	return 0;
}
