#include"answer03.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char** argv)
{
	char * dest = "Shubham";
	int n = strlen(dest);
	char * src = " Rastogi";
	dest = malloc(1 + 2 *(strlen(dest) + strlen(src)));
	strcpy(dest, "Shubham");
	printf("The Concatenated String is %s\n\n",strcat_ex(&dest, &n, src));
	free(dest);
	return(EXIT_SUCCESS);
}
