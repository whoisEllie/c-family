#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shuffle/shuffle.h"

typedef struct player_struct {
	int id;
	int handSize;
	int* hand;
} Player;

typedef struct pile_struct {
	int pileSize;
	int* pile;
} Pile;


int finished(Player* players, int Nplayers)
{
	int fullCount = 0;

	for (int i = 0; i < Nplayers; i++) {
		if (players[i].handSize == 52) {
			fullCount++;
		}
		else if (players[i].handSize == 0) {
			continue;	
		}
		else {
		}
	}
	return 0;
}

int is_penalty_card(int cardNo)
{
	if (cardNo > 10) {
		return 1;	
	}
	else {
		return 0;
	}
}

int pop(Player* player)
{
	int returnVal = player->hand[0];
	for (int i = 0; i < player->handSize; i++) 
	{
		if (i == player->handSize-1) {
			player->hand[i] = 0;	
		}
		else {
			player->hand[i] = player->hand[i+1];
		}
	}
	player->handSize -= 1;
	return returnVal;
}

struct pile_struct* take_turn(Player* player, Pile* deck)
{
	printf("Size: %d\n", deck->pileSize);
	// Check for 0!
	int topCard = 0;
	if (deck->pileSize > 0) {
		topCard = deck->pile[deck->pileSize-1];
	}
	printf("%d\n", topCard);
	if (is_penalty_card(topCard)) {
		for (int i = 0; i < (topCard - 10); i++) {
			//add stuff	
		}
		// If it is a penalty card, lay down the relevant number of cards
		// 		If we find a penalty card, lay it down and exit
		// 		If not, return the pile
		return deck;
	}
	else {
		// Insert the newly discarded card
		int playerTopCard = pop(player); 
		printf("Appending %d to deck.\n", playerTopCard);
		deck->pile[deck->pileSize] = playerTopCard;
		deck->pileSize += 1;
		return NULL;
	}
}

int get_next_player(int currentPlayer, int Nplayers)
{
	if (currentPlayer < Nplayers-1) {
		return currentPlayer + 1;	
	}
	else {
		return 0;
	}
}

int* divideCards(int Nplayers)
{
	int remainder = 52 % Nplayers;
	int initial = (52-remainder)/Nplayers;
	int* final = malloc(sizeof(int) * Nplayers); 

	for (int i = 0; i < Nplayers; i++) {
		final[i] = initial;
	}

	final[Nplayers-1] += remainder;

	for (int i = 0; i < Nplayers; i++) {
		printf("%d ", final[i]);
	}
	printf("\n");

	return final;
}

int beggar(int Nplayers, Pile *deck, int talkative)
{
	int playerIndex = 0;
	Player* players = malloc(sizeof(Player) * Nplayers);
	for (int i = 0; i < Nplayers; i++) {
		players[i].hand = malloc(52 * sizeof(int));
	}

	int* cardSplit = divideCards(Nplayers);	
	int* deckPtr = deck->pile;

	// Setting the hands of each player
	for (int i = 0; i < Nplayers; i++) {
		players[i].handSize = cardSplit[i];
		for (int j = 0; j < cardSplit[i]; j++) {
			players[i].hand[j] = *deckPtr++;	
		}	
	}

	// Debug printing the hands of each player
	for (int k = 0; k < Nplayers; k++) {
		for (int n = 0; n < players[k].handSize; n++) {
			printf("%d ", players[k].hand[n]);	
		}
		printf("\n");
	}

	// Clearing the deck 
	memset(deck->pile, 0, 52 * sizeof(int));
	deck->pileSize = 0;


	while (1) {
		struct pile_struct *reward = take_turn(&players[get_next_player(playerIndex, Nplayers)], deck);
		if (reward != NULL) {
			// Reward the current player
			for (int i = 0; i < reward->pileSize; i++) {
				players[playerIndex].hand[players[playerIndex].handSize] = reward->pile[i];	
			}	
			memset(reward->pile, 0, sizeof(int) * 52);
			reward->pileSize = 0;
		}

		// Actually increment playerindex
		playerIndex = get_next_player(playerIndex, Nplayers);
		printf("Current player index is: %d\n", playerIndex);

		printf("Current deck is: ");
		for (int i = 0; i < deck->pileSize; i++) {
			printf("%d, ", deck->pile[i]);	
		}
		printf("\n");
	}

	return 0;
}


int main(int argv, char* argc[])
{
	Pile* cardPile = malloc(sizeof(Pile));
	cardPile->pile = malloc(52 * sizeof(int));
	int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	// Shuffle deck
	shuffle(deck, 52, time(NULL));	

	cardPile->pile = deck;
	cardPile->pileSize = 52;

	beggar(3, cardPile, 1);
}
