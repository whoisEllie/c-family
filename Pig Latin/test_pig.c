#include "pig.c"

char* words[7] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};

int main()
{
	for (int i = 0; i < 7; i++) {
		printf("%s => %s\n", words[i], pig(words[i]));
	}
	return 0;
}
