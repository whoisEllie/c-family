#include "pig.c"
#include <string.h>

#define BUFFERSIZE 200 
#define DRAWDETAILEDCONVERSIONS true 

int main()
{
	bool loop = true;

	char sentence[BUFFERSIZE];
	char pigLatinOutput[BUFFERSIZE + (BUFFERSIZE * 3)];
	const char delimiter[2] = " ";
	char *word;

	while (loop) {

		printf("\nInput the sentence you'd like to translate to pig latin, or hit enter to exit.\n\n");
		printf(">> ");
		fgets(sentence, BUFFERSIZE, stdin);
		printf("\n");

		// Clearing pigLatinOutput
		memset(pigLatinOutput, 0, BUFFERSIZE + (BUFFERSIZE * 3));

		if (sentence[0] == '\n') 
		{
			loop = false;
		}
		else 
		{
			// clearing input of \n
			sentence[strcspn(sentence, "\n")] = 0;

			word = strtok(sentence, delimiter);

			while (word != NULL) {
				
				if (DRAWDETAILEDCONVERSIONS) {
					printf("%s => %s\n", word, pig(word));
				}

				sprintf(pigLatinOutput + strlen(pigLatinOutput), "%s ", pig(word));

				word = strtok(NULL, delimiter);
			}

			printf("\nThe final sentence is:\n\n");
			printf("%s\n\n", pigLatinOutput);
		}	
	}
}
