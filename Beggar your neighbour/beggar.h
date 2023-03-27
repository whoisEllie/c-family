#if !defined(BEGGAR_H)
#define BEGGAR_H

typedef struct player_struct {
	int id;
	int handSize;
	int* hand;
} Player;

typedef struct pile_struct {
	int pileSize;
	int* pile;
} Pile;

struct gameStatistics {
	int shortest;
	int longest;
	int average;
};

int finished(Player*, int);
int pop(Player*);
struct pile_struct* take_turn(Player*, Pile*);
int get_next_player(int, int);
int get_previous_player(int, int);
int* divideCards(int);
int beggar(int, int*, int);
struct gameStatistics* statistics(int, int);

#endif
