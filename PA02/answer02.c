#include"answer02.h"

size_t my_strlen(const char * str)
{
	int length_of_string = 0;
	int index = 0;
	if(str[0] == '\0')
	{
		return(length_of_string);
	}
	else 
	{
		while(str[index] != '\0')
		{
			length_of_string++;
			index++;
		}
		return(length_of_string);
	}
}
int my_countchar(const char * str, char ch)
{
	int count = 0;
	int index = 0;
	while(str[index] != '\0')
	{	
		if(str[index] == ch)
		{
			count++;
		}
		index++;
	}
	return(count);
}
char * my_strchr(const char * str, int ch)
{
	int index = 0;
	int str_len = 0;
	str_len = my_strlen(str);
	for(index = 0; index <= str_len; index++)
	{
		if(str[index] == ch)
		{	
			return((char *) &str[index]);
		}
	}
	return(NULL);
}
char * my_strrchr(const char * str, int ch)
{
	int index = 0;
	int str_len = 0;
	str_len = my_strlen(str);
	for(index = str_len; index >= 0; index--)
	{
		if(str[index] == ch)
		{
			return((char *) &str[index]);
		}
	}
	return(NULL);
}
char * my_strstr(const char * haystack, const char * needle)
{	
	int ind1 = 0;
	int ind2 = 0;
	int haystack_len = 0;
	int needle_len = 0;
	int count = 0;
	if(needle[0] == '\0')
	{
		return((char *)haystack);
	}
	haystack_len = my_strlen(haystack);
	needle_len = my_strlen(needle);
	for(ind1 = 0; ind1 < haystack_len; ind1++)
	{
		for(ind2 = 0; ind2 < needle_len; ind2++)
		{
			if(needle[ind2] == haystack[ind2 + ind1])
			{
				count++;
			}
		}
		if(count == needle_len )
		{
			return((char *) &haystack[ind1]);
		}
		count = 0;
	}
	return(NULL);
}
char * my_strcpy(char * dest, const char * src)
{
	int ind = 0;
	int src_len = 0;
	src_len = my_strlen(src);
	for(ind = 0; ind <= src_len; ind++)
	{
		dest[ind] = src[ind];
	}
	return(dest);
}
char * my_strcat(char * dest, const char * src)
{
	int ind = 0;
	int dest_len = 0;
	int src_len = 0;
	dest_len = my_strlen(dest);
	src_len = my_strlen(src);
	for(ind = 0; ind < src_len; ind++)
	{
		dest[ind + dest_len] = src[ind];
	}
	
	return(dest);
}
int my_isspace(int ch)
{
	if((char) ch == ' ' || (char) ch == '\f' || (char) ch == '\n' || (char) ch == '\r' || (char) ch == '\t' || (char) ch == '\v')
	{
		return(1);
	}
	return(0);
}
int my_atoi(const char * str)
{
	
	return(0);
}

