#include"answer03.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char** argv)
{
	char * dest = NULL;
	int n = 0;
	char * src = " Rastogi";
	dest = malloc(sizeof(char *) * (1 + 2 *(strlen(src))));
	strcpy(dest, "shubam");
	printf("The Concatenated String is %s\n\n",strcat_ex(&dest, &n, src));
	free(dest);
	
	//int i = 0;
	//int len = 0;
	//char * * strArr = explode("The\nTuring Test", " \t\v\r\f\n", &len);
	//printf("%s", strArr[1]);
	//for(i = 0; i < len; i++)
	//{
//		free(strArr[i]);
//	}
	return(EXIT_SUCCESS);
}
