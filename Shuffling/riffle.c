#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define DEBUG true 


/**
 * Riffles the given array once in place
 *
 * @param L The input void* array to be shuffled
 * @param len The length of the array
 * @param size The size (in bytes) of an array element
 * @param work A void* array which helps us in the shuffle by giving us a workspace 
 */
void riffle_once(void *L, int len, int size, void *work) 
{
    // Calculating a midpoint in the array
    int midPoint = ceil((double)len/2);

    // Split the array based on the calculated midpoint 
    char* A = (char*) L;
    char* B = (char*) L + (midPoint * size);

    // Obtain a pointer to the start of the workspace 
    char* W = (char *) work;

    // Initialising the counter objects
    int aCounter = 0; int bCounter = 0;

    // Iterating through the input array 
    for (int i = 0; i < len; i++)
    {
        if (aCounter >= len/2)
        {
            // If there are no more values left in the first half of the array, we can join the work array with the remaining values in B
            memcpy(W + i * size, B, (len/2 - bCounter) * size);
            break;
        }
        else if (bCounter >= len/2)
        {
            // If there are no more values left in the second half of the array, we can join the work array with the remaining values in A
            memcpy(W + i * size, A, (len/2 - aCounter) * size);
            break;
        }
        if (rand()%2) 
        {
            memcpy(W + i * size, A, size); // Copy the next element from A to work 
            aCounter++; A += size; // Step forward in the L array 
        } else {
            memcpy(W + i * size, B, size); // Copy the next element from B to work 
            bCounter++; B += size; // Step forward in the L array 
        }
    }

    // Return our now riffled pointer from the workspace back into L
    memcpy(L, W, len * size);
}

/**
 * A wrapper function for riffle_once, riffle gives us the chance to allocate a workspace and decide how many subsequent riffles we'd like to perform on the input array
 *
 * @param L The input void* array to be shuffled
 * @param len The length of the array
 * @param size The size (in bytes) of an array element
 * @param N The amount of times to repeat the riffle on the given array
 */
void riffle(void *L, int len, int size, int N) {
    void *work = malloc(len * size); // Allocating workspace
    srand(time(NULL)); // Seeding the random number generator with current time

    // Loop to riffle the deck N times
    for (int i = 0; i < N; i++) {
        riffle_once(L, len, size, work);
    }

    // Now that we no longer need it, free the workspace
    free(work);
}

/**
 * A function that checks whether our riffle function works properly by ensuring that the array contains the same elements before and after being riffled
 *
 * @param L the input void* array to be riffled
 * @param len The length of the array
 * @param size The size (in bytes) of an array element
 * int (*cmp)(void*, void*) The comparison function to use, which must be equal to that of the input array's data type
 *
 * @return A true/false integer declaring whether after riffling our array still contains all it's original elements and no new ones 
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *))
{
    // Making a copy and shuffling it 
    void* riffleArr = malloc(len * size);
    memcpy(riffleArr, L, len * size);
    riffle(riffleArr, len, size, 1);

    // Initialising the head pointers
    void* A = L; 
    void* B = riffleArr;
    bool found;

    for (int i = 0; i < len; i++)
    {
        found = false;
        for (int j = 0; j < len; j++) 
        {
            if (!cmp(A, B)) {
                found = true; 
            }
            B += size;
        }
        if (!found) {
            free(riffleArr);
            return false; 
        }
        A += size;
        B = riffleArr; // Resetting B to the head of the riffled array
    }

    free(riffleArr);
    return true;
}

/**
 * A helper function for comparing integers for equivalence
 *
 * @param a The first integer
 * @param b The second integer
 *
 * @return An integer denoting the relative position of b to a. If a is less than b, we return -1. If it is greater, we return 1. If they are equal, we return 0
 */
int cmp_int(void *a, void *b) {
    int numA = *(int*)a;
    int numB = *(int*)b;

    //Making necessary comparisons
    if (numA > numB)
    {
        if (DEBUG)
        {
            printf("%d != %d\n", numA, numB);
        }
        return -1;
    } else if (numA < numB)
    {
        if (DEBUG)
        {
            printf("%d != %d\n", numA, numB);
        }
        return 1;
    } 
    else 
    {
        if (DEBUG)
        {
            printf("%d = %d\n", numA, numB);
        }
        return 0;
    }
}

/**
 * A helper function for comparing strings for equivalence
 *
 * @param a The first string
 * @param b The second string
 *
 * @return The strcmp of the two strings, i.e. 0 if they're equal, 1 if not 
 */
int cmp_str(void *a, void *b) {
    // Converting void* to string
    char* strA = *(char**)a;
    char* strB = *(char**)b;

    if (DEBUG) 
    {
        int equivalence = strcmp(strA, strB);

        if (equivalence) 
        {
            printf("%s != %s\n", strA, strB); 
        }
        else 
        {
            printf("%s = %s\n", strA, strB); 
        }
        return equivalence;
    }
    else 
    {
        return strcmp(strA, strB);
    }
}

/**
 * A simple function which measures the quality of our riffle by comparing adjacent elements for equivalence. If an element is greater than it's predecessor, it's counted into the n array. If it's the opposite, then it is not. Ideally, we'd like a quality value of 0.5
 *
 * @param numbers The array of integers to evaluate for quality
 * @param len The length of the given numbers array
 *
 * @return The quality of the input array
 */
float quality(int *numbers, int len) {
    int n= 0;
    for (int i = 0; i < len - 1; i++)
    {
        if (numbers[i+1] > numbers[i])
        {
            n++;
        }
    }
    return (float) n / len;
}

/**
 * Calculates the quality across multiple riffles of the same array
 *
 * @param N The upper bound of the array which to generate
 * @param shuffles The amount of times to riffle the array
 * @param trials The amount of times to repeat the riffle
 *
 * @return The average quality of the riffle function, evaluated over trials amount of shuffles where the array was riffled shuffles times
 */
float average_quality(int N, int shuffles, int trials) {
    float sum = 0;
    int *cards = malloc(N * sizeof(int));
    for (int i = 0; i < trials; i++) 
    {
        // Initialize the cards array with integers from 0 to n-1
        for (int j = 0; j < N; j++) 
        {
            cards[j] = j;
        }
        // Shuffle the cards {shuffles} times
        for (int j = 0; j < shuffles; j++) 
        {
            riffle(cards, N, sizeof(int), shuffles);
        }
        // Compute the quality of the shuffle and add it to sum
        sum += quality(cards, N);
    }
    free(cards);
    return sum / trials;
}
