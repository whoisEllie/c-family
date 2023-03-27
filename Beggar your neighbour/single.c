#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"
#include "shuffle/shuffle.h"

int main(int argc, char* argv[])
{
	if (argc == 2) {

		// Create the deck
		int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

		// Shuffle deck
		shuffle(deck, 52, time(NULL));	

		if (atoi(argv[1])) {
			int players = atoi(argv[1]);
			// Play the game
			beggar(players, deck, 1);
			return 0;
		}

		printf("Something went wrong, please try entering the correct arguments\n");
		return 1;
	}
}
