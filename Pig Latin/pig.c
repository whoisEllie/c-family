#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHARLIMIT 40 

// The pig function is a heavily modified version of an answer found at: https://stackoverflow.com/questions/37176442/translating-a-sentence-to-pig-latin-in-c

char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};

bool isConsonant(bool firstTime, char *value)
{
	for (int i = 0; i < (!firstTime? 6 : 5); i++) {
		if (vowels[i] == *value) {
			return false;
		}	
	}
	return true;
}

char *pig (char *word)
{
		// Declaring our output string	
    char *piglatin = calloc(CHARLIMIT, sizeof(char));
		// Declaring our suffix string (stores early ) 
		char *suffix = calloc(CHARLIMIT, sizeof(char));
    char *english = word, *pig = piglatin;
		bool addingToSuffix = true; bool startsWithConsonant = false; bool firstRound = true;

		int i = 0;

    // Iterate through every character in english
    for (; *english && english - word + 2 < CHARLIMIT; english++) {
				// If the current pointer location is a valid character 
        if (('A' <= *english && *english < 'Z') || ('a' <= *english && *english < 'z')) 
				{
					// If the current letter is a consonant and we are adding to our suffix (i.e., we have not yet hit a vowel)
					if (addingToSuffix && isConsonant(firstRound, english)) 
					{ 						
						startsWithConsonant = true;
						suffix[i] = *english;
						i++;
					}
					else {
						// Save the current character from english into pig
						*pig++ = *english, addingToSuffix = false; 
					}

					firstRound = false;
        }
    }   


		if (startsWithConsonant) {
			// adding our suffix on to our piglatin
			for (int j = 0; j < i; j++) {
				*pig++ = suffix[j];
			}
			// Appending "ay"
    	*pig++ = 'a', *pig++ = 'y', *pig = 0;
		}
		else {
			// Appending "way" 
		 	*pig++ = 'w', *pig++ = 'a', *pig++ = 'y', *pig = 0;
		}

		// Clean up
		free(suffix);

		return piglatin;
}
