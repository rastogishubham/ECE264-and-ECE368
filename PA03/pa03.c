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
	int len = 0;
	//char * * strArr = explode("the\nturing test", " \t\v\n\r\f", &len);
	//char * * strArr = malloc(sizeof(char *));
	//strArr[0] = malloc(strlen("the\nturing test") + 1);
	//strcpy(strArr[0], "the\nturing test");
	//strArr = explode(strArr[0], " \t\v\n\r\f", &len);
	char * str = "The turing test";
	char * delims = " ";
	char * * strArr = explode(str, delims, &len);
	str = implode(strArr, len, " ");
	printf(" length is %d\n", len);
	int ind;
	for(ind = 0; ind < len; ++ind) {
		printf("strarr[%d] = %p = '%s'\n", ind, strArr[ind], strArr[ind]);
	}
	printf("(%s)\n", str);		
	for(ind = 0; ind < len; ++ind)
		free(strArr[ind]);
	printf("about to free %p\n", strArr);
	free(strArr);

	return 0;
}
