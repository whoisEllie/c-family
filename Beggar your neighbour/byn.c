#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

int main(int argc, char* argv[])
{
	if (argc == 3) {
		int players = atoi(argv[1]);
		int games = atoi(argv[2]);

		for (int i = 2; i <= players; i++) {
			struct gameStatistics* outStatistics = statistics(i, games);
			printf("Statistics for %d players:   Average: %d, Min: %d, Max: %d\n", i, outStatistics->average, outStatistics->shortest, outStatistics->longest);
			free(outStatistics);
		}

		return 0;
	}

	printf("No or incorrect arguments provided!");
	return 1;
}
