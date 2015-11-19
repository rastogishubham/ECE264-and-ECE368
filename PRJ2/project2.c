
//Name: Shubham Sandeep Rastogi
//PUID: 0026340022
//Email: rastogis@purdue.edu
//Assignment: ECE 368 Project 2


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
void max_min(int *, int, int *, int *, int *);
void c_sort(int *, int, int);
void RadixSort(int *, int);
void sort(int [], int);

void sort(int arr[], int n)
{
	int flag = 0;
	int max = 0;
	int min = 0;
	max_min(arr, n, &max, &min, &flag);
	if(flag == 1 && max/n < 5 && min >= 0 && max < 1200000)
	{
		c_sort(arr, n, max);
	}
	else if(flag == 1)
	{
		RadixSort(arr, n);
	}
}
	
void max_min(int arr[], int n, int * max, int * min, int * flag)
{
	int i = 0;
	* max = arr[0];
	* min = arr[0];
	for(i = 0; i < n; i++)
	{
		if(arr[i] > * max)
		{
			* max = arr[i];
		}
		else if(arr[i] < * min)
		{
			* min = arr[i];
		}
		if(i < n - 1 && arr[i] > arr[i + 1])
		{
			* flag = 1;
		}
	}
}
void c_sort(int arr[], int n, int max)
{
	int current = 0;
	int * count = calloc(max + 1, sizeof(int));
	for(current = 0; current < n; current++)
	{
		count[arr[current]]++;
	}
	int num = 0;
	current = 0;
	for(current = 0; current <= max; current++)
	{
		while(count[current] > 0)
		{
			arr[num] = current;
			num++;
			count[current]--;
		}
	}		
	free(count);
}


/*
int main()
{
        int * arr = malloc(sizeof(int) * NUM);
        int lcv = 0;
        srand(time(NULL));
        printf("Orignal Array");
        for(lcv = 0; lcv < NUM; lcv++)
        {
                arr[lcv] = rand() % 1000000;
                if(arr[lcv] % 5  == 0)
                {
                        arr[lcv] *= -1;
                }
        printf("ARR[%d] = %d\n",lcv, arr[lcv]);
        }
        TIME(sort(arr, NUM));
        sorted(arr, NUM);
        free(arr);
        return EXIT_SUCCESS;
}
*/

//code was adaptd from the textbook and the internet for this function
void RadixSort(int * pData, int count)
{
	int * pTemp = malloc(sizeof(int) * (count + 1));	
	int mIndex[4][256] = {{0}};            
	unsigned int * pDst, * pTmp, * pSrc;
	int i,j,m,n;
	unsigned int u;
	for(i = 0; i < count; i++)
	{         
		u = pData[i];
		for(j = 0; j < 4; j++)
		{
			if(j != 3)
			{                 
				mIndex[j][(int)(u & 0xff)]++;
			}
			else
			{
				mIndex[j][(int)((u^0x80) & 0xff)]++;
			}
			u >>= 8;
		}       
	}
	for(j = 0; j < 4; j++)
	{            
		n = 0;
		for(i = 0; i < 256; i++)
		{
			m = mIndex[j][i];
			mIndex[j][i] = n;
			n += m;
		}       
	}
	pDst = (unsigned int *)pTemp;              
	pSrc = (unsigned int *)pData;
	for(j = 0; j < 4; j++)
	{
		for(i = 0; i < count; i++)
		{
			u = pSrc[i];
			if(j != 3)
			{                  
				m = (int)(u >> (j<<3)) & 0xff;
			}
			else
			{
				m = (int)((u >> (j<<3))^0x80) & 0xff;
			}
			pDst[mIndex[j][m]++] = u;
		}
		pTmp = pSrc;
		pSrc = pDst;
		pDst = pTmp;
	}
	free(pTemp);
}



