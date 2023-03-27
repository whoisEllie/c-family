#include "beggar.c"
#include "shuffle/shuffle.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc == 2) {

		// Create the pile struct
		Pile* cardPile = malloc(sizeof(Pile));

		// Allocate memory for the pile
		cardPile->pile = malloc(52 * sizeof(int));

		// Create the deck
		int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

		// Shuffle deck
		shuffle(deck, 52, time(NULL));	

		// ALlocate the pile to the shuffled deck and update it's size
		cardPile->pile = deck;
		cardPile->pileSize = 52;

		if (atof(argv[1])) {
			int players = atoi(argv[1]);
			// Play the game
			beggar(players, cardPile, 1);
			//fscanf(stdin, "c"); // wait for user to enter input from keyboard
			return 0;
		}

		printf("Something went wrong, please try entering the correct arguments\n");
		return 1;
	}
}
