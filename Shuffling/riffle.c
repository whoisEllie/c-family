#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define DEBUG true 

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
            memcpy(W + i * size, B, (len/2 - bCounter) * size);
            break;
        }
        else if (bCounter >= len/2)
        {
            memcpy(W + i * size, A, (len/2 - aCounter) * size);
            break;
        }
        // Choose whether to take the next element from A or B
        if ((rand()%2)) 
        {
            memcpy(W + i * size, A, size); // Copy the next element from A to work 
            aCounter++; A += size; // Step forward in the L array 
        } else {
            memcpy(W + i * size, B, size); // Copy the next element from B to work 
            bCounter++; B += size; // Step forward in the L array 
        }
    }

    // Updating the original L pointer with the riffled one in work 
    memcpy(L, W, len * size);
}

void riffle(void *L, int len, int size, int N) {
    void *work = malloc(len * size); // Allocate workspace
    srand(time(NULL)); // Seeding the random number generator with current time

    // Loop to riffle the deck N times
    for (int i = 0; i < N; i++) {
        riffle_once(L, len, size, work);
    }
    free(work);
}

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

float quality(int *numbers, int len) {
    int c= 0;
    for (int i = 0; i < len - 1; i++)
    {
        if (numbers[i+1] > numbers[i])
        {
            c++;
        }
    }
    return (float) c / len;
}

float average_quality(int N, int shuffles, int trials) {
    float sum = 0;
    int *cards = malloc(N * sizeof(int));
    for (int i = 0; i < trials; i++) 
    {
        // Initialize the cards array with integers 0, 1, ..., N-1
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
