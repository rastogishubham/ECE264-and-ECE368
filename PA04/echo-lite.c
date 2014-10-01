#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char * * argv)
{
	int ind = 1;
	printf("\n");
	for(ind = 1; ind < argc; ind++)
	{
		printf("%s ", argv[ind]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
