#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void destroy_arr(int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void print_arr(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void create_arr(long int size, char * file, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);

int main(int argc, char * * argv)
{
	long int size = 0;
	FILE * fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("Error in opening file");
		return EXIT_FAILURE;
	}
	char * str = malloc(sizeof(char) * 2048);
	while(fgets(str, 2048, fp))
	{
		size++;
	}
	int * age = malloc(sizeof(int) * size);
	int * gender = malloc(sizeof(int) * size);
	int * m_status = malloc(sizeof(int) * size);
	int * race = malloc(sizeof(int) * size);
	int * birth = malloc(sizeof(int) * size);
	int * lang = malloc(sizeof(int) * size);
	int * occupation = malloc(sizeof(int) * size);
	int * income = malloc(sizeof(int) * size);
	
	fclose(fp);
	create_arr(size, argv[1], age, gender, m_status, race, birth, lang, occupation, income);
	print_arr(size, age, gender, m_status, race, birth, lang, occupation, income);
	destroy_arr(age, gender, m_status, race, birth, lang, occupation, income);
	free(str);
	return EXIT_SUCCESS;
}
void destroy_arr(int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income)
{
	free(age);
	free(gender);
	free(m_status);
	free(race);
	free(birth);
	free(lang);
	free(occupation);
	free(income);
}
void print_arr(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income)
{
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		printf("%d, %d, %d, %d, %d, %d, %d, %d\n", age[lcv], gender[lcv], m_status[lcv], race[lcv], birth[lcv], lang[lcv], occupation[lcv], income[lcv]);
	}
}
void create_arr(long int size, char * file, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income)
{
	int user_id = 0;
	int lcv = 0;
	FILE * fp = fopen(file, "r");
	if(fp == NULL)
	{
		printf("Error in opening file");
		return;
	}
	for(lcv = 0; lcv < size; lcv++)
	{
		fscanf(fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d", &user_id, &age[lcv], &gender[lcv], &m_status[lcv], &race[lcv], &birth[lcv], &lang[lcv], &occupation[lcv], &income[lcv]);
	}
	fclose(fp);
}
