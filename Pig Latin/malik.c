#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Checks to see if a letter is a vowel. Returns 1 if it is. Returns 0 otherwise.
 *
 * @param letter - Character being evaluated
 *
 * @return 1 - If the letter is a vowel
 *         0 - If the letter isn't a vowel
 */
int isVowel(char letter) {
	// Converts letter to lower case for simplicity
	char lowerCase = tolower(letter);

	switch(lowerCase) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
						return 1;
		default:
						return 0;
	}
}



char *pig(char *word) {

	char *newWord;
	if(!(newWord = (char *)malloc(sizeof(word) * 50))) {
		printf("Insufficient Memory\n");
		exit(1);
	}

	switch(isVowel(word[0])) {
		case 1:
			strcpy(newWord, word);
			strcat(newWord, "way");
			return newWord;
		default:
			if (word[0] != 'y') {
				int len = strlen(newWord);
				int i;
				char consonants[20] = "";
				char *temp = consonants;
				char *ptr = newWord;
				for(i = 0; i < len; i++) {
					if((isVowel(word[i]) || (word[i] == 'y'))) {
						*ptr++ = word[i];
					} else {
						*temp++ = word[i];
					}
				}

				strcat(consonants, "ay");
				strcat(newWord, consonants);
			} else {
				int len = strlen(newWord);
				int i;
				char consonants[20] = "";
				char *temp = consonants;
				char *ptr = newWord;
				int hitVowel = 0;
				for(i = 0; i < len; i++) {
					if((isVowel(word[i]) || (word[i] == 'y')) || (hitVowel)) {
						hitVowel = 1;
						*ptr++ = word[i];
					} else {
						*temp++ = word[i];
						hitVowel = 0;
					}
				}

				strcat(consonants, "ay");
				strcat(newWord, consonants);
		}
		break;
	}

	return newWord;
}
