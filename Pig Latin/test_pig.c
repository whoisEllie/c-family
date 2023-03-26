#include "pig.c"
#include <stdbool.h>
#include <stdlib.h>

char* words[7] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};

int main()
{
	for (int i = 0; i < 7; i++) {
		char* outWord = pig(words[i]);
		printf("%s => %s\n", words[i], outWord);
		free(outWord);
	}
	return 0;
}
