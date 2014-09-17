#include"answer03.h"
#include<string.h>

char * strcat_ex(char * * dest, int * n, const char * src)
{
	int dest_len = 0;
	int src_len = 0;
	char * new_dest;
	src_len = strlen(src);
	if(*dest != NULL)
	{
		dest_len = strlen(*dest);
	}
	if(*dest == NULL || dest_len + src_len + 1 > *n)
	{
		new_dest = (char *)malloc(sizeof(char *) * (1 + 2 * (dest_len + src_len)));
		strcpy(new_dest, *dest);
		free(*dest);
		*dest = new_dest;
		*n = strlen(new_dest);
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
	int ind = 0;
	int count_delim = 0;
	int str_len = strlen(str);
	for(ind = 0; ind < str_len; ind++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{
			count_delims++;
		}
	}
	char * * strArr = malloc((count_delim + 1) * sizeof(char *));
	ind = 0;
	int last = 0;
	int arrInd = 0;
	for(ind = 0; ind < str_len; ind++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{
			char * new_str 
	return(NULL);	
}
char * implode(char * * strArr, int len, const char * glue)
{
	return(NULL);
}
void sortStringArray(char * * arrString, int len)
{

}
void sortStringCharacters(char * str)
{

}
void destroyStringArray(char * * strArr, int len)
{

}

