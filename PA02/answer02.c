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

