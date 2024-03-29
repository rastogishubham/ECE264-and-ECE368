#include"answer03.h"
#include<string.h>
#include<stdio.h>
int cmpfuncstring(const void *, const void *);
int cmpfuncchar(const void *, const void *);
char * strcat_ex(char * * dest, int * n, const char * src)
{
	int src_len = 0;
	char * new_dest;
	src_len = strlen(src);
	if(*dest == NULL)
	{
		new_dest = malloc(sizeof(char *) * (1 + 2 * (src_len)));
		new_dest[0] = '\0';
		free(*dest);
		*dest  = new_dest;
		*n = 1 + 2 * src_len;
		strcat(*dest, src);
	}
	else if(strlen(*dest) + src_len + 1 > *n)
	{
		int dest_len = strlen(*dest);
		new_dest = (char *)malloc(sizeof(char *) * (1 + 2 * (strlen(*dest) + src_len)));
		strcpy(new_dest, *dest);
		free(*dest);
		*dest = new_dest;
		*n = 1 + 2 * (src_len + dest_len);
		strcat(*dest, src);
	}
	else
	{
		strcat(*dest, src);
	}
	return(*dest);
}

char * * explode(const char * str, const char * delims, int * arrLen)
{
	int N = 0;
	int ind = 0;
	for(ind = 0; ind < strlen(str); ind++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{
			N++;	
		}
	}
	*arrLen = N+1;
	char * * strArr = malloc((N + 1) * sizeof(char *));
	//printf("strArr = %p\n", strArr);
	strArr[0] = '\0';
	int last = 0;
	ind = 0;
	int arrInd = 0;
	for(ind = 0; ind < strlen(str); ind ++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{	
			strArr[arrInd] = malloc(sizeof(char) * (ind  - last + 1));
			//printf("just malloced %p\n", strArr[arrInd]);
			//strArr[arrInd] = '\0';
			memcpy(strArr[arrInd], &str[last],  ind - last);
			strArr[arrInd][ind - last] = '\0';
			last = ind + 1;
			arrInd++;
		}
	}
	strArr[arrInd] = malloc(sizeof(char *) * (ind- last + 1));
	//strArr[arrInd] = '\0';
	memcpy(strArr[arrInd], &str[last], ind - last);
	strArr[arrInd][ind - last] = '\0';
	return(strArr);
}
char * implode(char * * strArr, int len, const char * glue)
{
	char * str = NULL;
//	*str = '\0';
	int ind = 0;
	int len_strArr = 0;
	for(ind = 0; ind < len; ind++)
	{
		len_strArr = strlen(strArr[ind]);
		//str = malloc(sizeof(char *) * (len_strArr + 1));
		strcat_ex(&str, &len_strArr, strArr[ind]);
		if(ind < len -1)
		{
			strcat(str, glue);
		}	
	}
	/*
	ind = 0;
	for(ind = 0; ind < len; ind++)
	{	
		len_strArr = strlen(strArr[ind]);
		//memcpy(str, strArr[ind], len_strArr - 1);
		strcat(str, strArr[ind]);
		if(ind < len -1)
		{
			strcat(str, glue);
		}
	}
//	int len_str = strlen(str);
//	str[len_str] = '\0';*/
	return(str);
}
void sortStringArray(char * * arrString, int len)
{	
	qsort(&arrString[0], len, sizeof(char *), cmpfuncstring);
}
void sortStringCharacters(char * str)
{
	qsort(&str[0], strlen(str), sizeof(char), cmpfuncchar);
}
void destroyStringArray(char * * strArr, int len)
{
	int ind = 0;
	for(ind = 0; ind < len; ind++)
	{
		free(strArr[ind]);
	}
	free(strArr);
}
int cmpfuncstring(const void * arg1, const void * arg2)
{
	const char * const * ptr1 = (const char * *) arg1;
	const char * const * ptr2 = (const char * *) arg2;
	const char * str1 = * ptr1;
	const char * str2 = * ptr2;
	return(strcmp(str1, str2));
}
int cmpfuncchar(const void * arg1, const void * arg2)
{
	const char * ptr1 = (char *) arg1;
	const char * ptr2 = (char *) arg2;
	const char ch1 = * ptr1;
	const char ch2 = * ptr2;
	return(ch1 - ch2);
}
