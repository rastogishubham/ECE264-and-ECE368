//#include"answer05.c"
#include"answer05.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv)
{
	partitionAll(5);
	printf("\n");
	partitionIncreasing(4);
	printf("\n");
	partitionDecreasing(5);
	printf("\n");
	partitionOdd(5);
	printf("\n");
	partitionEven(6);
	printf("\n");
	partitionOddAndEven(5);
	printf("\n");
	partitionPrime(5);
	return EXIT_SUCCESS;
}
