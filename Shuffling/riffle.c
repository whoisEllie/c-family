#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void riffle_once(void *L, int len, int size, void *work)
{
	// Making sure our work array is clear and ready to accept the riffled array
	free(work);
	work = malloc(sizeof(L));

	// Obtaining pointers to the head of our input arrays, B will be incremented after a midway point is calculated
	void *A = L;
	void *B = L;
	void *out = work;

	int midPoint = ceil((double)len/2);	
	B = B + midPoint * size;

}

int main(int argv, char* argc[])
{
	void* work = malloc(sizeof(void));
	int testint[6] = {1, 2, 3, 4, 5, 6};
	char testchar[6] = {'a', 'b', 'c', 'd', 'e', 'f'};

	printf("Running int riffle\n");
	riffle_once(testint, 6, sizeof(int), work);
}
