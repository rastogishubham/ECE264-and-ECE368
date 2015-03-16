#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#define NUM 10
#define TIME(fun) do {\
                    struct timeval start, end, diff;\
                    gettimeofday(&start, NULL);\
                    fun;\
                    gettimeofday(&end, NULL);\
                    timersub(&end, &start, &diff);\
                    printf("Time taken: %ld.%06ld sec.\n",(long int)diff.tv_sec, (long int)diff.tv_usec);\
                } while(0)
void sorted(int *);
void max_min(int *, int, int *, int *, int *);
void c_sort(int *, int, int);
void RadixSort(int *, int);
void printArray(int *, int);
void sort(int arr[], int n)
{
	int flag = 0;
	int max = 0;
	int min = 0;
	max_min(arr, n, &max, &min, &flag);
	if(flag == 1 && max/n < 5 && min >= 0 && max < 1200000)
	{
		c_sort(arr, n, max);
		printf("Count sort");
	}
	else if(flag == 1)
	{
		printf("Radix sort");
		RadixSort(arr, n);
	}
//	printArray(arr, n);
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
		else
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
//	int max = maximum(arr, n);
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
	unsigned int * pDst, * pTmp, * pSrc;
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
//	printf("\n psrc %p, pdata %p, \n", pSrc, pData);
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
	free(pTemp);
}

int main()
{
	int * arr = malloc(sizeof(int) * NUM);
//	int * arr_cpy = malloc(sizeof(int) * NUM);
//	int * arr_cpy_2 = malloc(sizeof(int) * NUM);
	int lcv = 0;
	//int flag = 0;
	srand(time(NULL));
	printf("Orignal Array");
	for(lcv = 0; lcv < NUM; lcv++)
	{
		arr[lcv] = rand() % 10000;
		if(arr[lcv] % 5 == 0)
		{
			arr[lcv] *= -1;
		}
//		arr_cpy[lcv] = arr[lcv];
//		arr_cpy_2[lcv] = arr[lcv];
		//printf("%d\n", arr[lcv]);
	}
//	TIME(c_sort(arr, NUM));
//	printf("Count\n");
//	sorted(arr);
//	TIME(qsort(arr_cpy, NUM, sizeof(int), cmp));
//	sorted(arr_cpy);
//	printf("Qsort\n");
//	TIME(RadixSort(arr_cpy_2, NUM));
//	sorted(arr_cpy_2);
//	printf("Radix\n");
//	printArray(arr, NUM);
//	free(arr);
//	free(arr_cpy);
//	free(arr_cpy_2);
	TIME(sort(arr, NUM));
	sorted(arr);
	free(arr);
	return EXIT_SUCCESS;
}
void sorted(int * arr)
{
	int lcv = 0;
	int flag = 0;
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
//	free(arr);
//	free(arr_cpy);
//	free(arr_cpy_2);
}
