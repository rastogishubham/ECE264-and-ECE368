#include"answer03.h"
#include<string.h>

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
		//new_dest = '\0';
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
	int ind = 0;
	int count_delims= 0;
	int str_len = strlen(str);
	for(ind = 0; ind < str_len; ind++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{
			count_delims++;
		}
	}
	char * * strArr = malloc((count_delims + 1) * sizeof(char *));
	ind = 0;
	int last = 0;
	int arrInd = 0;
	for(ind = 0; ind < str_len; ind++)
	{
		if(strchr(delims, str[ind]) != NULL)
		{
			char * new_str = malloc(sizeof(char *) * (ind - last));
			memcpy(new_str, &str[last], last - ind + 1);
			strcpy(strArr[arrInd], new_str);
			last = ind + 1;
			arrInd++;
		}
	}
	char * new_str = malloc(sizeof(char *) * (str_len - last));
	memcpy(new_str, &str[last], last - str_len - 1);
	strcpy(strArr[arrInd], new_str);
	*arrLen = arrInd + 1;
	return(strArr);	
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

