#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "beggar.h"
#include "shuffle/shuffle.h"

/**
 * Whether the current distribution of cards constitutes a finished game
 *
 * @param players The current players of the game, both playing and disqualified
 * @param Nplayers The amount of players in the game
 *
 * @return True of the game is finished, false otherwise
 */
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

/**
 * Checks to see if a card is a penalty card
 *
 * @param cardNo The value of the card to check
 *
 * @return True of the card is a penalty card, false if otherwise
 */
int is_penalty_card(int cardNo)
{
	if (cardNo > 10) {
		return 1;	
	}
	else {
		return 0;
	}
}

/**
 * Pops the top-most card from the player's hand
 *
 * @param player The player who's hand to pop from
 *
 * @return The value of the popped card
 */
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

/**
 * Runs the logic for a single turn
 *
 * @param player The player who is playing this turn
 * @param deck The deck of cards in play
 *
 * @return The reward for the previous player, NULL if there is none
 */
struct pile_struct* take_turn(Player* player, Pile* deck)
{
	// Check for 0!
	int topCard = -10;
	if (deck->pileSize > 0) {
		topCard = deck->pile[deck->pileSize-1];
	}
	if (is_penalty_card(topCard)) {
		for (int i = 0; i < (topCard - 10); i++) {
			if (player->handSize > 0) {
				int nextCard = pop(player);
				if (nextCard == 0) {
					return deck;
				}
				deck->pile[deck->pileSize] = nextCard;
				deck->pileSize += 1;
				if (nextCard > 10) {
					return NULL;
				}
			}
			else {
			 return deck;
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

/**
 * Gets the index of the next player in the array
 *
 * @param currentPlayer The index of the current player in the array
 * @param Nplayers The number of players present in the game
 *
 * @return The index of the next player in the array
 */
int get_next_player(int currentPlayer, int Nplayers)
{
	if (currentPlayer < Nplayers-1) {
		return currentPlayer + 1;	
	}
	else {
		return 0;
	}
}

/**
 * Gets the index of the previous player in the array
 *
 * @param currentPlayer The index of the current player in the array
 * @param Nplayers The number of players present in the game
 *
 * @return The index of the previous player in the array
 */
int get_previous_player(int currentPlayer, int Nplayers)
{
	if (currentPlayer == 0) {
		return Nplayers-1;
	}
	else {
		return currentPlayer-1;
	}
}

/**
 * Splits 52 cards amongst the given number of players
 *
 * @param Nplayers The number of players between whom to split the cards
 *
 * @return An array of cards where the index corresponds to the player's index
 */
int* divideCards(int Nplayers)
{
	int remainder = 52 % Nplayers;
	int initial = (52-remainder)/Nplayers;
	int* final = malloc(sizeof(int) * Nplayers); 

	for (int i = 0; i < Nplayers; i++) {
		final[i] = initial;
	}

	final[Nplayers-1] += remainder;

	return final;
}

/**
 * Plays a single game of Beggary your Neighbour
 *
 * @param Nplayers The number of players taking part
 * @param deck The shuffled deck of cards used to play the game
 * @param talkative Whether to display verbose game information
 *
 * @return The number of turns it took for the game to finish
 */
int beggar(int Nplayers, int* deck, int talkative)
{

	// Creating the deck struct
	Pile* outPile = malloc(sizeof(Pile));
	outPile->pile = malloc(52 * sizeof(int));
	// ALlocate the pile to the shuffled deck and update it's size
	for (int i = 0; i < 52; i++) {
	 outPile->pile[i] = deck[i];
	}
	outPile->pileSize = 52;

	int playerIndex = 0;
	Player* players = malloc(sizeof(Player) * Nplayers);
	for (int i = 0; i < Nplayers; i++) {
		players[i].hand = malloc(52 * sizeof(int));
		players[i].id = i;
	}

	int* cardSplit = divideCards(Nplayers);	
	int* deckPtr = outPile->pile;

	// Setting the hands of each player
	for (int i = 0; i < Nplayers; i++) {
		players[i].handSize = cardSplit[i];
		for (int j = 0; j < cardSplit[i]; j++) {
			players[i].hand[j] = *deckPtr++;	
		}	
	}

	free(cardSplit);

	// Clearing the deck 
	//memset(deck->pile, 0, 52 * sizeof(int));
	outPile->pileSize = 0;

	int turnNo = 0;
	struct pile_struct *reward; 

	int finishLoop = false;

	while (!finishLoop) {

		if (players[playerIndex].handSize > 0) {

			if (talkative) {
				printf("Turn %d\n", turnNo);

				// Debug printing the pile
				printf("Pile: ");
				for (int i = 0; i < outPile->pileSize; i++) {
					printf("%d, ", outPile->pile[i]);	
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
			}
		
			reward = take_turn(&players[playerIndex], outPile);

			int amount0 = 0;

			for (int i = 0; i < Nplayers; i++) {
				if (players[i].handSize == 0) {
					amount0 += 1;
				}
			}

			if (amount0 == Nplayers) // If we run into a situation where two players discard cards at the same time, the last player gets all the cards 
			{
				for (int i = 0; i < reward->pileSize; i++) {
					players[playerIndex].hand[players[playerIndex].handSize] = reward->pile[i];	
					players[playerIndex].handSize += 1;
				}
				memset(reward->pile, 0, sizeof(int) * 52);
				reward->pileSize = 0;
			}
			else
			{
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

	if (talkative) {
		// Printing the final state of the pile and hands

		printf("\nFinal result:\n\n");

		// Debug printing the pile
		printf("Final pile: ");
		for (int i = 0; i < outPile->pileSize; i++) {
			printf("%d, ", outPile->pile[i]);	
		}
		printf("\n");

		// Debug printing the hands of each player
		for (int k = 0; k < Nplayers; k++) {
			if (k == playerIndex) {
				printf("   %d: ", k);
			}
			else {
				printf("   %d: ", k);
			}
			for (int n = 0; n < players[k].handSize; n++) {
				printf("%d ", players[k].hand[n]);	
			}
			printf("\n");
		}
	}


	for (int i = 0; i < Nplayers; i++) {
		free(players[i].hand);
	}
	free(outPile->pile);
	free(outPile);
	free(players);
	return turnNo;
}

/**
 * Calculates statistics about games with a certain number of players
 *
 * @param Nplayers The amount of players to simulate
 * @param games The amount of games to play
 *
 * @return A struct of statistics including the shortest game, the longest game, and the average number of turns in a game
 */
struct gameStatistics* statistics(int Nplayers, int games)
{
	int sum = 0;

	struct gameStatistics* returnStatistics = malloc(sizeof(struct gameStatistics));
	returnStatistics->shortest = 100000;
	returnStatistics->longest = 0;

	for (int i = 0; i < games; i++) {

		// Create the deck
		int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

		// Shuffle deck
		shuffle(deck, 52, time(NULL));	

		int result = beggar(Nplayers, deck, 0);

		if (result < returnStatistics->shortest) {
			returnStatistics->shortest = result;	
		}
		if (result > returnStatistics->longest) {
			returnStatistics->longest = result;
		}
		sum += result;
	}

	returnStatistics->average = sum / games;

	return returnStatistics;
}
