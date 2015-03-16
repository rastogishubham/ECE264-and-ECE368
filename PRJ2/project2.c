#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#define NUM 10000000
#define TIME(fun) do {\
                    struct timeval start, end, diff;\
                    gettimeofday(&start, NULL);\
                    fun;\
                    gettimeofday(&end, NULL);\
                    timersub(&end, &start, &diff);\
                    printf("Time taken: %ld.%06ld sec.\n",(long int)diff.tv_sec, (long int)diff.tv_usec);\
                } while(0)

int maximum(int arr[], int n)
{
	int i = 0;
	int max = arr[0];
	for(i = 0; i < n; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
void sort(int arr[], int n)
{
	int current = 0;
	int max = maximum(arr, n);
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
void printArray(int * arr, int n)
{
	int lcv = 0;
	for(lcv = 0; lcv < n; lcv++)
	{
		printf("%d\n", arr[lcv]);
	}
	printf("\n lcv %d\n", lcv);
}
int cmp(const void * a, const void * b)
{
	return *(int *)a - *(int*)b;
}

void RadixSort(int * pData, int count)
{
	int * pTemp = malloc(sizeof(int) * (count + 1));	
	int mIndex[4][256] = {{0}};            // index matrix
	unsigned int * pDst, * pSrc, * pTmp;
	int i,j,m,n;
	unsigned int u;
	for(i = 0; i < count; i++)
	{         // generate histograms
		u = pData[i];
		for(j = 0; j < 4; j++)
		{
			if(j != 3)
			{                 //  signed integer handling
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
	{             // convert to indices
		n = 0;
		for(i = 0; i < 256; i++)
		{
			m = mIndex[j][i];
			mIndex[j][i] = n;
			n += m;
		}       
	}
	pDst = (unsigned int *)pTemp;               // radix sort
	pSrc = (unsigned int *)pData;
	for(j = 0; j < 4; j++)
	{
		for(i = 0; i < count; i++)
		{
			u = pSrc[i];
			if(j != 3)
			{                  //  signed integer handling
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
	memcpy(pData, (int *) pSrc, count);
}

int main()
{
	int * arr = malloc(sizeof(int) * NUM);
	int * arr_cpy = malloc(sizeof(int) * NUM);
	int * arr_cpy_2 = malloc(sizeof(int) * NUM);
	int lcv = 0;
	int flag = 0;
	srand(time(NULL));
	printf("Orignal Array");
	for(lcv = 0; lcv < NUM; lcv++)
	{
		arr[lcv] = (int) rand()% 80000000;
	//	if(arr[lcv] % 5 == 0)
	//	{
	//		arr[lcv] *= -1;
	//	}
		arr_cpy[lcv] = arr[lcv];
		arr_cpy_2[lcv] = arr[lcv];
		//printf("%d\n", arr[lcv]);
	}
	TIME(sort(arr, NUM));
	TIME(qsort(arr, NUM, sizeof(int), cmp));
	TIME(RadixSort(arr, NUM));
//	printArray(arr, NUM);
	for(lcv = 0; lcv < NUM - 1; lcv++)
	{
		if(arr[lcv] > arr[lcv + 1])
		{
			flag = 1;
			break;
		}
	}
	if(flag == 1)
	{
		printf("Not sorted\n");
	}
	else
	{
		printf("Sorted\n");
	}
	free(arr);
	free(arr_cpy);
	free(arr_cpy_2);
	return EXIT_SUCCESS;
}
