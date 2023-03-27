#include <math.h>
#include <stdbool.h>
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
			return 0;
		}
	}
	
	if (fullCount == 1) {
		return 1;	
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
	// Check for 0!
	int topCard = 0;
	if (deck->pileSize > 0) {
		topCard = deck->pile[deck->pileSize-1];
	}
	if (is_penalty_card(topCard)) {
		for (int i = 0; i < (topCard - 10); i++) {
			int nextCard = pop(player);
			deck->pile[deck->pileSize] = nextCard;
			deck->pileSize += 1;
			if (nextCard > 10) {
				return NULL;	
			}
		}
		return deck;
	}
	else {
		// Play card
		int playerTopCard = pop(player); 
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

int get_previous_player(int currentPlayer, int Nplayers)
{
	if (currentPlayer == 0) {
		return Nplayers-1;
	}
	else {
		return currentPlayer-1;
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
		players[i].id = i;
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

	int turnNo = 0;
	struct pile_struct *reward; 

	int finishLoop = false;

	while (!finishLoop) {

		if (players[playerIndex].handSize > 0) {

			printf("Turn %d\n", turnNo);

			// Debug printing the pile
			printf("Pile: ");
			for (int i = 0; i < deck->pileSize; i++) {
				printf("%d, ", deck->pile[i]);	
			}
			printf("\n");

			// Debug printing the hands of each player
			for (int k = 0; k < Nplayers; k++) {
				if (k == playerIndex) {
					printf("*  %d: ", k);
				}
				else {
					printf("   %d: ", k);
				}
				for (int n = 0; n < players[k].handSize; n++) {
					printf("%d ", players[k].hand[n]);	
				}
				printf("\n");
			}

			reward = take_turn(&players[playerIndex], deck);

			if (reward != NULL) {
				// Obtain the previous player that's left with more than 0 cards 
				int previousPlayerID = get_previous_player(playerIndex, Nplayers);
				while (players[previousPlayerID].handSize == 0) {
					previousPlayerID = get_previous_player(previousPlayerID, Nplayers);
				}
				for (int i = 0; i < reward->pileSize; i++) {
					players[previousPlayerID].hand[players[previousPlayerID].handSize] = reward->pile[i];	
					players[previousPlayerID].handSize += 1;
				}	
				memset(reward->pile, 0, sizeof(int) * 52);
				reward->pileSize = 0;
			}

			// Actually increment playerindex
			playerIndex = get_next_player(playerIndex, Nplayers);

			// Increment turn
			turnNo++;
		}
		else {
			playerIndex = get_next_player(playerIndex, Nplayers);
		}

		finishLoop = finished(players, Nplayers); 
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

	beggar(4, cardPile, 1);
}
