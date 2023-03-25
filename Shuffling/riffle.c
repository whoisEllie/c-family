#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void riffle_once(void *L, int len, int size, void *work)
{
	// Making sure our work array is clear and ready to accept the riffled array
	free(work);
	work = malloc(sizeof(L));

	// Obtaining pointers to the head of our input arrays, B will be incremented after a midway point is calculated
	char *A = L;
	char *B = L;
	int aCount = 0; 
	int bCount = 0;
	char *out = work;

	int midPoint = ceil((double)len/2);	
	B = B + midPoint * size;

	for (int i = 0; i < len; i++) {
		if((rand()%2 && bCount < (len - midPoint)) || aCount >= midPoint)
		{
			printf("Updating B to %d\n", *(int*)B);
			*out = *B; 
			out += size;
			B += size;
			bCount++;
		}
		else
		{
			printf("Updating A to %d\n", *(int*)A);
			*out = *A;
			out += size;
			A += size;
			aCount++;
		}
	}
	
	void* C = work;
	for (int j = 0; j < len; j++) {
		printf("%d ", *(int*)C);
		C += size;
	}
}

int main(int argv, char* argc[])
{
	void* work = malloc(sizeof(void));
	int testint[6] = {1, 2, 3, 4, 5, 6};
	char testchar[6] = {'a', 'b', 'c', 'd', 'e', 'f'};


	srand(time(NULL));
	printf("Running int riffle\n");
	riffle_once(testint, 6, sizeof(int), work);
}
