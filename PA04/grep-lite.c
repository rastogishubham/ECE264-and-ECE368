#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char * * argv)
{
	int ind = 0;
	for(ind = 0; ind < argc; ind++)
	{
		if(strcmp(argv[ind], "--help") == 0)
		{
			printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match      print non-matching lines\n  -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then exit status is 2.\n");
			return EXIT_SUCCESS;
		}
	}
	if(argc < 2)
	{
		return 2;
	}
	FILE * fp = stdin;
	ind = 0;
	char str[2000];
	for(ind = 0; ind < argc - 1; ind++)
	{
		if(strcmp(argv[ind], "-v") != 0 || strcmp(argv[ind], "-n") != 0 || strcmp(argv[ind], "-q") != 0 || strcmp(argv[ind], "--invert-match") != 0 || strcmp(argv[ind], "--line-number") != 0 || strcmp(argv[ind], "--quiet") != 0)
		{
			fprintf(stderr, "grep error %s is bogus command-line argument", argv[ind]);
			return 2;
		}
	}
	if(argv[argc - 1] [0] == '-')
	{	
		fprintf(stderr, "grep error PATTERN begins with '-'\n");
		return 2;
	}
	while(!feof(fp))
	{
		fgets(str, 2000, fp);
		if(strstr(str, argv[argc - 1]) != NULL)
		{
		}
	}
	return EXIT_SUCCESS;
}
