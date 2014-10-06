#include"answer05.h"
#include<stdio.h>
#include<stdlib.h>
void partitionAllHelper(int*, int, int);
void printPartition(int*, int);
void printPartition(int *buffer, int length)
{
	int ind;
	for(ind = 0; ind < length - 1; ind++)
	{
		printf("%d +", buffer[ind]);
	}
	printf("%d\n", buffer[length - 1]);
}
void partitionAllHelper(int *buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
	}
	for(val = 0; val <= left; val++)
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
/*
void partitionIncresing(int value);
{

}

void partitionDecresing(int value);
{

}

void partitionOdd(int value)
{

}
void partitionEven(int value)
{

}

void partitionOddandEven(int value)
{

}
void partitionPrime(int value)
{

}*/
