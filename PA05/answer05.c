#include"answer05.h"
#include<stdio.h>
#include<stdlib.h>
void partitionAllHelper(int*, int, int);
void printPartition(int*, int);
void partitionIncreasingHelper(int *, int, int);
void partitionDecreasingHelper(int *, int, int);
void partitionDecreasingHelper(int * buffer, int ind, int left)
{
	int val;
}
void partitionIncreasingHelper(int *buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	int min = 1;
	if(ind != 0)
	{
		min = buffer[ind - 1] + 1;
	}
	for(val = min; val <= left; val++)
	{
		buffer[ind] = val;
		partitionIncreasingHelper(buffer, ind + 1, left - val);
	}
}

void printPartition(int *buffer, int length)
{
	int ind;
	printf("=");
	for(ind = 0; ind < length - 1; ind++)
	{
		printf("%d + ", buffer[ind]);
	}
	printf("%d\n", buffer[length - 1]);
}
void partitionAllHelper(int *buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	for(val = 1; val <= left; val++)
	{
		buffer[ind] = val;
		partitionAllHelper(buffer, ind + 1, left - val);
	}
}
void partitionAll(int value)
{
	int *buffer;
	buffer = malloc(sizeof(int) * value);
 	partitionAllHelper(buffer, 0, value);
	free(buffer);
//	return EXIT_SUCCESS;
}

void partitionIncreasing(int value)
{
	int *buffer;
	buffer = malloc(sizeof(int) * value);
	partitionIncreasingHelper(buffer, 0, value);
	free(buffer);
	return;
}

void partitionDecreasing(int value)
{
	return;
}

void partitionOdd(int value)
{
	return;
}
void partitionEven(int value)
{
	return;
}

void partitionOddAndEven(int value)
{
	return;
}
void partitionPrime(int value)
{
	return;
}
