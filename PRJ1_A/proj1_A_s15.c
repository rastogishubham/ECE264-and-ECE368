#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//
typedef struct Queue_Node
{
	double arr_time;
	int priority;
	double service_time;
	struct Queue_Node * next;
}Queue;

//fuction declarations
Queue * mode1(double lamda_0, double lambda_1, double mu, int total_tasks);
Queue * Queue_Node_Create(int priority, double arr_time, double service_time);
double calculate_inter_arrival_time(double lambda, double r);

Queue * Queue_Node_Create(int priority, double arr_time, double service_time)
{
	Queue * Node = malloc(sizeof(Queue));
//	printf("Just malloced %p\n", Node); 
	Node -> next = NULL;
	Node -> priority = priority;
	Node -> arr_time = arr_time;
	Node -> service_time = service_time;
	return Node;
}

void Queue_destroy(Queue * queue)
{
	while(queue != NULL)
	{
		Queue * p = queue -> next;
//		printf("Just Freed %p\n", queue);
		free(queue);
		queue = p;
	}
}

double calculate_r(double mu)
{
	double x = (double) rand() / RAND_MAX;
	//printf("\n x = %f\n", x);
	double r = (-1 / mu) * log(1 - x);
	//printf("\n Random R = %f\n", r);
	return r;
}

double calculate_inter_arrival_time(double lambda, double r)
{
	double inter_arr_time = lambda * exp(-lambda * r);
	inter_arr_time = ceil(inter_arr_time);
	return inter_arr_time;
}

double calculate_service_time(double mu, double r)
{
	double service_time = mu * exp(-mu * r);
	service_time = ceil(service_time);
	return service_time;
}

/*void list_print(Queue * FEL)
{
	while(FEL != NULL)
	{
		printf("\n\n");
		printf("Arrival Time = %f\n", FEL -> arr_time);
		printf("Service Time = %f\n", FEL -> service_time);
		printf("Priority = %d\n", FEL -> priority);
		printf("\n\n");
		FEL = FEL -> next;
	}
}*/
 
int main(int argc, char * * argv)
{
	printf("argc = %d\n", argc);
	if(argc == 5)
	{
		double lambda_0 = atof(argv[1]);
		double lambda_1 = atof(argv[2]);
		double mu = atof(argv[3]);
		int total_tasks = atoi(argv[4]) * 2;
		Queue * FEL1 = mode1(lambda_0, lambda_1, mu, total_tasks);
//		list_print(FEL1);
		Queue_destroy(FEL1);
	}
	else
	{
		printf("Wrong input");
	}
	return EXIT_SUCCESS;
}



Queue * create_FEL(int priority, double arrival_time, double service_time, Queue * FEL)
{
	if(FEL == NULL)
	{
		return Queue_Node_Create(priority, arrival_time, service_time);
	}
	FEL -> next = create_FEL(priority, arrival_time, service_time, FEL -> next);
	return FEL;
}

Queue * mode1(double lambda_0, double lambda_1, double mu, int total_tasks)
{
	if(lambda_0 + lambda_1 > mu)
	{
		printf("Enter values so that lambda_1 + lambda_0 is less than mu\n");
		return NULL;
	}
	int lcv = 0;
	double inter_arr_time = 0;
	double service_time = 0;
	double r = 0;
	double tot_time_0 = 0;
	double tot_time_1 = 0;
	Queue * FEL1 = NULL;
	Queue * FEL2 = NULL;
	for(lcv = 0; lcv < total_tasks / 2; lcv++)
	{
		r = calculate_r(lambda_0);
		inter_arr_time = calculate_inter_arrival_time(lambda_0, r);
		r = calculate_r(mu);
		service_time = calculate_service_time(mu, r);
		tot_time_0 += inter_arr_time;
		FEL1 = create_FEL(0, tot_time, service_time, FEL1);
	}
	for(lcv = 0; lcv < total_tasks / 2; lcv++)
	{
		r = calculate_r(lambda_1);
		inter_arr_time = calculate_inter_arrival_time(lambda_1, r);
		r = calculate_r(mu);
		service_time = calculate_service_time(mu, r);
		tot_time_1 += inter_arr_time;
		FEL2 = create_FEL(1, tot_time, service_time, FEL2);
	}
	Queue_destroy(FEL2);
	return FEL1;
}

void simulator(Queue * FEL1, Queue * FEL2, int total_tasks)
{
	int server_time = 0;
	int total_time = 0;
	Queue * temp_queue_0 = 0;
	Queue * temp_queue_1 = 0;
	int flag = 1;
	int tot_service_time = 0;
	double avg_CPU_util = 0;
	double avg_queue_len = 0;
	int queue_0_len = 0;
	int queue_1_len = 0;
	int tot_queue_len = 0;
	int tot_wait_0 = 0;
	int tot_wait_1 = 0;
	double avg_wait_0 = 0;
	double avg_wait_1 = 0;
	while(total_tasks > 0)
	{
		queue_0_len = queue_len(temp_queue_0);
		queue_1_len = queue_len(temp_queue_1);
		tot_queue_len += queue_0_len + queue_1_len;
		if(total_time == FEL1 -> arr_time)
		{
			temp_queue_0 = create_list(0, FEL1 -> arr_time, FEL1 -> service_time, temp_queue_0);
			if(flag == 1)
			{
				server_time = temp_queue_0 -> service_time;
				tot_service_time += server_time;
				flag = 0;
				tot_wait_0 += (total_time - temp_queue_0 -> arr_time);
				Queue * p = temp_queue_0 -> next;
				free(temp_queue_0);
				temp_queue_0 = p;
			}
			FEL1 = FEL1 -> next;
		}
		if(total_time == FEL2 -> arr_time)
		{
			temp_queue_1 = create_list(0, FEL2 -> arr_time, FEL2 -> service_time, temp_queue_1);
			if(flag == 1 && temp_queue_0 == NULL)
			{
				server_time = temp_queue_1 -> service_time;
				tot_service_time += server_time;
				flag = 0;
				tot_wait_1 += (total_time - temp_queue_0 -> arr_time);
				Queue * p = temp_queue_1 -> next;
				free(temp_queue_1);
				temp_queue_1 = p;
			}
			FEL2 = FEL2 -> next;
		}
		total_time++;
		if(flag == 0)
		{
			server_time--;
			if(server_time == 0)
			{
				total_tasks--;
				flag = 1;
			}
		}
	}
	avg_CPU_util = tot_service_time / total_time;
	avg_queue_len = tot_queue_len / (total_time + 1);
	avg_wait_0 = tot_wait_0 / (total_tasks / 2);
	avg_wait_1 = tot_wait_1 / (total_tasks / 2);
}

int queue_len(Queue * queue)
{
	int len = 0;
	while(queue != NULL)
	{
		len++;
		queue = queue -> next;
	}
	return len;
}
void mode2(char * filename)
{
	return;
}
