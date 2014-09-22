#include"answer03.h"
#include<string.h>
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
	return(NULL);
}
char * implode(char * * strArr, int len, const char * glue)
{
	return(NULL);
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
	const cahr * ptr2 = (char *) arg2;
	const char ch1 = * ptr1;
	const char ch2 = * ptr2;
	if(ch1 < ch2)
	{
		return(-1);
	}
	else
	{
		return(0);
	}
}
