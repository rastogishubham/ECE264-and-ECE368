#include"answer05.h"
#include<stdio.h>
#include<stdlib.h>
//function definitions
void partitionAllHelper(int*, int, int);
void printPartition(int*, int);
void partitionIncreasingHelper(int *, int, int);
void partitionDecreasingHelper(int *, int, int);
void partitionOddHelper(int * , int , int);
void partitionEvenHelper(int *, int, int);
void partitionOddAndEvenHelper(int*, int, int);
void partititonPrimeHelper(int *, int, int);
//code for function partitionPrimeHelper based on code from Prof. Lu's book.
void partitionPrimeHelper(int * buffer, int ind, int left)
{
	//variable declerations
	int val;
	int lcv = 0;
	int count = 0;
	//base case
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	//recursive case
	for(val = 1; val <= left; val ++)
	{
		count = 0;
		for(lcv = 1; lcv <= val; lcv++)
		{
			if(val % lcv == 0)
			{
				count ++;
			}
		}
		if(count == 2)
		{
			buffer[ind] = val;
			partitionPrimeHelper(buffer, ind + 1, left - val);
		}
	}
}
//code for function partitionOddAndEvenHelper based on code from Prof. Lu's book
void partitionOddAndEvenHelper(int * buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	for(val = 1; val <= left; val ++)
	{
		int valid = 0;
		if(ind == 0)
		{
			valid = 1;
		}
		else
		{
			valid = (buffer[ind - 1] % 2) != (val % 2);
		}
		if(valid == 1)
		{
			buffer[ind] = val;
			partitionOddAndEvenHelper(buffer, ind + 1, left - val);
		}
	}
}
//code for function partitionEvenHelper based on code from Prof. Lu's book
void partitionEvenHelper(int * buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	for(val = 2; val <= left; val += 2)
	{
		buffer[ind] = val;
		partitionEvenHelper(buffer, ind + 1, left - val);
	}
}
//code for function partitionOddHelper based on code from Prof. Lu's book
void partitionOddHelper(int * buffer, int ind, int left)
{
	int val;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	for(val = 1; val <= left; val += 2)
	{
		buffer[ind] = val;
		partitionOddHelper(buffer, ind + 1, left - val);
	}
}
//code for function partitionDecreasingHelper based on code from Prof. Lu's book
void partitionDecreasingHelper(int * buffer, int ind, int left)
{
	int val = 0;
	if(left == 0)
	{
		printPartition(buffer, ind);
		return;
	}
	int max = left;
	if(ind != 0)
	{
		max = buffer[ind - 1] - 1;
	}
	for(val = max; val >= 1; val --)
	{
		buffer[ind] = val;
		partitionDecreasingHelper(buffer, ind + 1,  left - val);
	}
}
//coe for function partitionIncreasingHelper based on code from Prof. Lu's book
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
//code for function printPartition based on code from Prof. Lu's book
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
//code for function partitionAllHelper based on code from Prof. Lu's book
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
//code for function partitionAll based on code from Prof. Lu's book
void partitionAll(int value)
{
	int *buffer;
	buffer = malloc(sizeof(int) * value);
 	partitionAllHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionIncreasing based on code from Prof. Lu's book
void partitionIncreasing(int value)
{
	int *buffer;
	buffer = malloc(sizeof(int) * value);
	partitionIncreasingHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionDecreasing base on code from Prof. Lu's book
void partitionDecreasing(int value)
{
	int *buffer = malloc(sizeof(int) * value);
	partitionDecreasingHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionOdd based on code from Prof. Lu's book
void partitionOdd(int value)
{
	int * buffer = malloc(sizeof(int) * value);
	partitionOddHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionEven based on code from Prof. Lu's book
void partitionEven(int value)
{
	int *buffer = malloc(sizeof(int) * value);
	partitionEvenHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionOddAndEven based on code from Prof. Lu's book
void partitionOddAndEven(int value)
{	
	int * buffer = malloc(sizeof(int) * value);
	partitionOddAndEvenHelper(buffer, 0, value);
	free(buffer);
	return;
}
//code for function partitionPrime based on code from Prof. Lu's book
void partitionPrime(int value)
{
	int * buffer = malloc(sizeof(int) * value);
	partitionPrimeHelper(buffer, 0, value);
	free(buffer);
	return;
}
