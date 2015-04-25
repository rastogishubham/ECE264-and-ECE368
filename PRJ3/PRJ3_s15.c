#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void destroy_arr(int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void print_arr(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income);
void create_arr(int size, char * file, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income, FILE * fp);
double * * create_u_lab(long int size, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income, double * lab_max);
void destroy_matrix(double * * matrix, int size);
double * * create_lab_matrix(double * * ulab_matrix, int size, double l_max, double delta);
void query1(double * * lab_matrix, int size, int source);
void query3(double * * lab_matrix, int size, int source);
void get_input(int * size, double * delta_1, double * delta_2, int * source, double * alpha, FILE * fp);
void query5(double * * lab_matrix, int size);
void query4(double * * lab_matrix, int size, int source);
int not_in_array(int * arr, int size, int val);
int cmp(const void * a, const void * b);
void query6(double * * lab_matrix, int size);
int query6_helper(double * * lab_matrix, int size, int source);
double min_dist(double * dist, int * sptSet, int size);
void query2(double * * lab_matrix, int size, int source, double alpha);
double cmp2(const void * a, const void * b);
int main(int argc, char * * argv)
{
	double * * ulab_matrix = NULL;
	double * * dense_graph = NULL;
	double * * sparse_graph = NULL;
	double l_max = 0.0;
	double delta_1 = 0.0;
	double delta_2 = 0.0;
	int size = 0;
	double alpha = 0.0;
	int source = 0;
	FILE * fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("Error in opening file");
	}
	get_input(&size, &delta_1, &delta_2, &source, &alpha, fp);
	int * age = malloc(sizeof(int) * size);
	int * gender = malloc(sizeof(int) * size);
	int * m_status = malloc(sizeof(int) * size);
	int * race = malloc(sizeof(int) * size);
	int * birth = malloc(sizeof(int) * size);
	int * lang = malloc(sizeof(int) * size);
	int * occupation = malloc(sizeof(int) * size);
	int * income = malloc(sizeof(int) * size);
	create_arr(size, argv[1], age, gender, m_status, race, birth, lang, occupation, income, fp);
	ulab_matrix = create_u_lab(size, age, gender, m_status, race, birth, lang, occupation, income, &l_max);
	dense_graph = create_lab_matrix(ulab_matrix, size, l_max, delta_1);
	printf("\n\n");
	sparse_graph = create_lab_matrix(ulab_matrix, size, l_max, delta_2);
	query1(dense_graph, size, source);
	query3(dense_graph, size, source);
	query5(dense_graph, size);
	query4(dense_graph, size, source);
	query6(dense_graph, size);
	query2(dense_graph, size, source, alpha);
	destroy_arr(age, gender, m_status, race, birth, lang, occupation, income);
	destroy_matrix(ulab_matrix, size);
	destroy_matrix(dense_graph, size);
	destroy_matrix(sparse_graph, size);
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
void create_arr(int size, char * file, int * age, int * gender, int * m_status, int * race, int * birth, int * lang, int * occupation, int * income, FILE * fp)
{
	int user_id = 0;
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &user_id, &age[lcv], &gender[lcv], &m_status[lcv], &race[lcv], &birth[lcv], &lang[lcv], &occupation[lcv], &income[lcv]);
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
	free(query_1);
}
void query3(double * * lab_matrix, int size, int source)
{
	int * query_3 = malloc(sizeof(int) * size);
	int ctr = 0;
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		if(lab_matrix[source - 1][lcv] != 0)
		{
			query_3[ctr] = lcv + 1;
			ctr++;
		}
	}
	printf("The number of immdiate neigbours for %d are: %d\n", source, ctr);
	for(lcv = 0; lcv < ctr; lcv++)
		printf("The node ID's are %d\n", query_3[lcv]);
	free(query_3);
}
void get_input(int * size, double * delta_1, double * delta_2, int * source, double * alpha, FILE * fp)
{
	int size_tmp = 0;
	double delta1_tmp = 0.0;
	double delta2_tmp = 0.0;
	int source_tmp = 0;
	double alpha_tmp = 0.0;
	fscanf(fp, "%d,%lf,%lf,%d,%lf", &size_tmp, &delta1_tmp, &delta2_tmp, &source_tmp, &alpha_tmp);
	* size = size_tmp;
	* delta_1 = delta1_tmp;
	* delta_2 = delta2_tmp;
	* source = source_tmp;
	* alpha = alpha_tmp;
}
void query5(double * * lab_matrix, int size)
{
	double query_5 = 0.0;
	int ctr = 0;
	int lcv = 0;
	int lcv2 = 0;
	for(lcv2 = 0; lcv2 < size; lcv2++)
	{
		for(lcv = 0; lcv < size; lcv++)
		{
			if(lab_matrix[lcv2][lcv] != 0)
			{
				ctr++;
			}
		}
	}
	query_5 = ctr / size;
	printf("The average of 1 hops is: %0.2lf\n", query_5);
}
void query4(double * * lab_matrix, int size, int source)
{
	int lcv = 0;
	int lcv2 = 0;
	int * query_4 = calloc(size, sizeof(int));
	int ctr = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		if(lab_matrix[source - 1][lcv] != 0)
		{
			for(lcv2 = 0; lcv2 < size; lcv2++)
			{
				if(lab_matrix[lcv][lcv2] != 0 && (lcv2 + 1) != source && not_in_array(query_4, ctr, lcv2 + 1))
				{
					query_4[ctr] = lcv2 + 1;
					ctr++;
				}
			}
		}
	}
	qsort(query_4, ctr, sizeof(int), cmp);
	printf("The number of 2nd hop number are: %d\n", ctr);
	for(lcv = 0; lcv < ctr; lcv++)
		printf("The nodes are %d\n", query_4[lcv]);
	free(query_4);
}
int not_in_array(int * arr, int size, int val)
{
	int lcv = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		if(arr[lcv] == val)
			return 0;
	}
	return 1;
}
int cmp(const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}
void query6(double * * lab_matrix, int size)
{
	int lcv = 0;
	int ctr = 0;
	double query_6 = 0.0;
	for(lcv = 0; lcv < size; lcv++)
	{
		ctr += query6_helper(lab_matrix, size, lcv + 1);
	}
	query_6 = (double) ctr / size;	
	printf("The average for 2 hops is: %0.2lf", query_6);
}
int query6_helper(double * * lab_matrix, int size, int source)
{
	int lcv = 0;
	int lcv2 = 0;
	int * query_4 = calloc(size, sizeof(int));
	int ctr = 0;
	for(lcv = 0; lcv < size; lcv++)
	{
		if(lab_matrix[source - 1][lcv] != 0)
		{
			for(lcv2 = 0; lcv2 < size; lcv2++)
			{
				if(lab_matrix[lcv][lcv2] != 0 && (lcv2 + 1) != source && not_in_array(query_4, ctr, lcv2 + 1))
				{
					query_4[ctr] = lcv2 + 1;
					ctr++;
				}
			}
		}
	}
	free(query_4);
	return ctr;
}
void query2(double * * lab_matrix, int size, int source, double alpha)
{
	int ctr = 0;
	int i = 0;
	int count = 0;
	int v = 0;
	double * dist = malloc(sizeof(double) * size);
	int * sptSet = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
	{
		dist[i] = 1;
		sptSet[i] = 0;
	}
	dist[source] = 0;
	for (count = 0; count < size - 1; count++)
	{
		int u = min_dist(dist, sptSet, size);
		sptSet[u] = 1;
		for (v = 0; v < size; v++)
		{
			if (!sptSet[v] && lab_matrix[u][v] && dist[u] != 1 && dist[u] + lab_matrix[u][v] < dist[v])
			{
            			dist[v] = dist[u] + lab_matrix[u][v];
			}
		}
	}
	qsort(dist, size, sizeof(double), cmp);
	for(i = 0; i < size; i++)
	{
		if(dist[i] < alpha)
			ctr++;
	}
	printf("number of nodes with shortest distance less than alpha is: %d", ctr - 1);
}
double min_dist(double * dist, int * sptSet, int size)
{
	int min = 1, min_index;
	int v = 0;
	for (v = 0; v < size; v++)
	{
		if (sptSet[v] == 0 && dist[v] <= min)
		{
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}
double cmp2(const void * a, const void * b)
{
   return (*(double*)a - *(double*)b);
}
