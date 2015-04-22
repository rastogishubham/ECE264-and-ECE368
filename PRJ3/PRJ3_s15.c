#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void destroy_arr(int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void print_arr(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void create_arr(long int size, char * file, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
double * * create_u_lab(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income, double * lab_max);
void destroy_matrix(double * * matrix, int size);
double * * create_lab_matrix(double * * ulab_matrix, int size, double l_max, double delta);
void query1(double * * lab_matrix, int size, int source);
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
	double * * ulab_matrix = NULL;
	double * * lab_matrix = NULL;
	double l_max = 0.0;
	double delta = 0.3;
	fclose(fp);
	create_arr(size, argv[1], age, gender, m_status, race, birth, lang, occupation, income);
	print_arr(size, age, gender, m_status, race, birth, lang, occupation, income);
	ulab_matrix = create_u_lab(size, age, gender, m_status, race, birth, lang, occupation, income, &l_max);
	lab_matrix = create_lab_matrix(ulab_matrix, size, l_max, delta);
	query1(lab_matrix, size, 5);
	destroy_arr(age, gender, m_status, race, birth, lang, occupation, income);
	destroy_matrix(ulab_matrix, size);
	destroy_matrix(lab_matrix, size);
	free(str);
	return EXIT_SUCCESS;
}
void destroy_matrix(double * * matrix, int size)
{
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		free(matrix[lcv]);
	}
	free(matrix);
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
double * * create_u_lab(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income, double * l_max)
{
	double * * ulab_matrix = malloc(sizeof(double *) * size);
	int lcv = 0;
	int row = 0;
	int col = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		 ulab_matrix[lcv] =  malloc(sizeof(double) * size);
	}
	for(row = 0; row < size; row++)
	{
		for(col = 0; col < size; col++)
		{
			ulab_matrix[row][col] = pow((age[row] - age[col]), 2) + pow((gender[row] - gender[col]), 2) + pow((m_status[row] - m_status[col]), 2) + pow((race[row] - race[col]), 2) + pow((birth[row] - birth[col]), 2) + pow((lang[row] - lang[col]), 2) + pow((occupation[row] - occupation[col]), 2) + pow((income[row] - income[col]), 2);
			ulab_matrix[row][col] = sqrt(ulab_matrix[row][col]);
			ulab_matrix[row][col] = (int) (ulab_matrix[row][col] * 100);
			ulab_matrix[row][col] = ulab_matrix[row][col] / 100;
			if(row == 0 && col == 0)
				* l_max = ulab_matrix[row][col];
			if(ulab_matrix[row][col] > * l_max)
				* l_max = ulab_matrix[row][col];
		}
	}
	return ulab_matrix;
}
double * * create_lab_matrix(double * * ulab_matrix, int size, double l_max, double delta)
{
	int lcv = 0;
	int row = 0;
	int col = 0;
	double * * lab_matrix = malloc(sizeof(double *) * size);
	for(lcv = 0; lcv < size; lcv++)
	{
		lab_matrix[lcv] = malloc(sizeof(double) * size);
	}
	for(row = 0; row < size; row++)
	{
		for(col = 0; col < size; col++)
		{
			lab_matrix[row][col] = 1 - (ulab_matrix[row][col] / l_max);
			lab_matrix[row][col] = (int) (lab_matrix[row][col] * 100);
			lab_matrix[row][col] = lab_matrix [row][col] / 100;
			if(lab_matrix[row][col] < delta || row == col)
				lab_matrix[row][col] = 0;
			printf("lab value for row %d, col %d is: %lf\n",row + 1, col + 1,  lab_matrix[row][col]);
		}
	}
	return lab_matrix;
}
void query1(double * * lab_matrix, int size, int source)
{
	int * query_1 = malloc(sizeof(int) * size);
	int ctr = 0;
	double min = 1.0;
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{	
		if(min > lab_matrix[source - 1][lcv] && lab_matrix[source - 1][lcv] != 0)
			min = lab_matrix[source - 1][lcv];
	}
	for(lcv = 0; lcv < size; lcv++)
	{
		if(min == lab_matrix[source - 1][lcv] && lab_matrix[source -1 ][lcv] != 0)
		{
			query_1[ctr] = lcv + 1;
			ctr++;
		}
	}
	for(lcv = 0; lcv < ctr; lcv++)
		printf("The lowest LAB nodes are %d\n", query_1[lcv]);
	printf("The smallest LAB value is: %lf\n", min);
}

