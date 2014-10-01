#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char * * argv)
{
	char ch;
	int ind = 0;
	for(ind = 0; ind < argc; ind++)
	{
		if(strcmp(argv[ind], "--help") == 0)
		{
			printf("Usage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\n  cat-lite README   Print the file README to standard output.\n  cat-lite f - g    Print f's contents, then standard input,\n                    then g's contents.\n  cat-lite          Copy standard input to standard output.\n");
			return EXIT_SUCCESS;
		}
	}
	FILE * fptr;
	ind = 0;
	if(argc == 1)
	{
		fptr = stdin;
		while(!feof(fptr))
		{
			ch = fgetc(fptr);
			if(ch != EOF)
			{
				printf("%c", ch);
			}
		}
		fclose(fptr);
		return EXIT_SUCCESS; 
	}
	for(ind = 1; ind < argc; ind++)
	{
		if(strcmp(argv[ind], "-") == 0)
		{
			fptr = stdin;
		}
		else
		{
			fptr = fopen(argv[ind], "r");
		}
		if(fptr == NULL)
		{
			fprintf(stderr, "cat cannot open %s\n", argv[ind]);
			return EXIT_FAILURE;
		}
		while(!feof(fptr))
		{
			ch = fgetc(fptr);
			if(ch != EOF)
			{
				printf("%c", ch);
			}
		}
		fclose(fptr);
	}
	return EXIT_SUCCESS;
}
