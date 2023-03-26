#include <math.h>
#include <stdlib.h>

typedef struct player_struct {
	int handSize;
	int* hand;
} Player;


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
		return ;
		}
	}
}

int* take_turn(Player* player, int** pile)
{

}

int beggar(int Nplayers, int *deck, int talkative)
{
	int playerIndex = 0;
	Player* players = malloc(sizeof(Player) * Nplayers);

	while (1) {
		
	}

	return 0;
}

int main(int argv, char* argc[])
{
	int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	beggar(3, deck, 1);
}
