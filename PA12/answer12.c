#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "answer12.h"
#include <pthread.h>
typedef struct prime {
	uint128 start;
	uint128 end;
	uint128 value;
	int * prime;
} object;

void * isPrime(void * obj_void)
{
	object * obj = (object *) obj_void;
	long int i = 0;
	for(i = obj -> start; i <= obj -> end && *(obj -> prime) == 1; i++)
	{
		if((obj -> value % i) == 0)
		{
			*(obj -> prime) = FALSE;
			pthread_exit(0);
		}
	}
	return NULL;
}


int my_isspace(int ch)
{
        if((char) ch == ' ' || (char) ch == '\f' || (char) ch == '\n' || (char) ch == '\r' || (char) ch == '\t' || (char) ch == '\v')
        {
                return(TRUE);
        }
        return(FALSE);
}
uint128 alphaTou128(const char * str)
{
       // int neg = 0;
        int ind = 0;
        uint128 ret = 0;
        while((str[ind] >= '0' && str[ind] <= '9') || my_isspace((int) str[ind]) == 1)
        {
             /*   if(str[ind] == '-')
                {
                        neg = 1;
                        ind++;
                }*/
                if(my_isspace((int) str[ind]) == 1)
                {
                        ind ++;
                }
                else if(str[ind] >= '0' && str[ind] <= '9')
                {
                        ret *= 10;
                        ret += str[ind] - '0';
                        ind++;
                }
                else
                {
                        return(0);
                }
        }
    /*    if(neg == 1)
        {
                ret = ret * -1;
        }*/
        return(ret);
}
char * u128ToString(uint128 value)
{
/*	if(value == 0)
	{
		return "0";
	}*/
	uint128 copy = value;
	int rem = 0;
	char * ch = NULL;
	int len = 0;
	do
	{
		rem = copy % 10;
		len++;
		copy = copy / 10;
	}while(copy != 0);
	ch = malloc(sizeof(char) * (len + 1));
	ch[len] = '\0';
	int ind = len - 1;
	do
	{
		rem = value % 10;
		ch[ind] = rem + '0';
		ind--;
		value = value / 10;
	}while(value != 0);
//	ch[len] = '\0';
	return ch;
}

int primalityTestParallel(uint128 value, int n_threads)
{
	int lcv = 0;
	if(value == 2 || value == 3)
	{
		return TRUE;
	}
	else if(value % 2 == 0 || value == 1)
	{
		return FALSE;
	}
	pthread_t * thread = malloc(sizeof(pthread_t) * n_threads);
//	pthread_attr_t * att = maolloc(sizeof(pthread_attr_t)  * nthreads);
	int flag = 0;
	int prime = 1;
	uint128 max = floor(sqrt(value));
	uint128 buffer_size = max / n_threads;
	object * obj = malloc(sizeof(object) * n_threads);
	for(lcv = 0; lcv < n_threads; lcv++)
	{
		uint128 start = lcv * buffer_size;
		uint128 end = (lcv + 1) * buffer_size;
		if(buffer_size == 0)
		{
			buffer_size = 1;
		}
		if(start < 3)
		{
			start = 3;
		}
		if(end < start)
		{
			end = start + 1;
		}
		obj[lcv].start = start;
		obj[lcv].end = end;
		obj[lcv].value = value;
		obj[lcv].prime = &prime;
		flag = pthread_create(&thread[lcv], NULL, isPrime, (void *) &obj[lcv]);
		if(flag != 0)
		{
			printf("Error in creating thread\n");
			return FALSE;
		}
	}
	for(lcv = 0; lcv < n_threads; lcv++)
	{
		int ret = 0;
		ret = pthread_join(thread[lcv], NULL);
		if(ret != 0)
		{
			printf("Error in joining thread\n");
			return FALSE;
		}
	}
	free(obj);
	free(thread);
	return prime;
}

/*int main()
{
	char * ch = u128ToString(1);
	free(ch);
	return 0;
}*/
