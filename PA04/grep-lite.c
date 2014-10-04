#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char * * argv)
{
	int ind = 0;
	for(ind = 1; ind < argc; ind++)
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
	int flag_invert = 0;
	int flag_line = 0;
	int flag_quiet = 0;
	int line_num = 1;
	char str[2001];
	int return_val = 0;
	for(ind = 1; ind < argc - 1; ind++)
	{
		if(strcmp(argv[ind], "-v") != 0 && strcmp(argv[ind], "-n") != 0 && strcmp(argv[ind], "-q") != 0 && strcmp(argv[ind], "--invert-match") != 0 && strcmp(argv[ind], "--line-number") != 0 && strcmp(argv[ind], "--quiet") != 0)
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
	for(ind = 0; ind < argc; ind++)
	{
		if(strcmp(argv[ind], "-v") == 0 || strcmp(argv[ind], "--invert-match") == 0)
		{
			flag_invert = 1;
		}
		if(strcmp(argv[ind], "-n") == 0 || strcmp(argv[ind], "--line-number") == 0)
		{
		//	printf("Line number found");
			flag_line = 1;
		}
		if(strcmp(argv[ind], "-q") == 0 || strcmp(argv[ind], "--quiet") == 0)
		{
//			printf ("Quiet found!\n");			

			flag_quiet = 1;
		}
	}
	while(fgets(str, 2001, fp) != NULL)
	{
		//printf("fgets not null \n");
		if(strstr(str, argv[argc - 1]) != NULL && flag_quiet == 1)
		{
	//		printf ("Found match and quiet!\n");
			return_val =  0;
		}
		if(strstr(str, argv[argc - 1]) == NULL && flag_quiet == 1)
		{

			//printf ("did not Find match and quiet!\n");
			return_val = 0;
		}
		if(flag_invert == 1 && strstr(str, argv[argc - 1]) == NULL && flag_line == 1 && flag_quiet == 0)
		{
			//printf("a");
			printf("%d: ", line_num);
			printf("%s", str);
			return_val = 0;
		}
		if(flag_invert == 1 && strstr(str, argv[argc - 1]) == NULL && flag_line == 0 && flag_quiet == 0)
		{	
			//printf("b");
			printf("%s", str);
			return_val = 0;
		}
		if(flag_invert == 0 && flag_line == 0 && flag_quiet == 0  && strstr(str, argv[argc - 1]) != NULL)
		{	
			//printf("c");
			printf("%s", str);
			return_val = 0;
		}
		if(flag_invert == 0 && flag_line == 1 && flag_quiet == 0 && strstr(str, argv[argc - 1]) != NULL)
		{
			//printf("d");
			printf("%d: ", line_num);
			printf("%s", str);
			return_val = 0;
		}
		line_num++;
		//fclose(fp);
	}
	fclose(fp);
	return return_val;
}
