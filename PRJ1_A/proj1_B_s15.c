#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//Structure Definition
typedef struct Queue_Node
{
        double arr_time;
        int priority;
        double * sub_tasks_time;
        struct Queue_Node * next;
}Queue;

//Function Declerations


//Function Definations
int main(int argc, char * argv)
{
	return EXIT_SUCCESS;
}

// The function Queue_Node_Create creates a list node
Queue * Queue_Node_Create(int priority, double arr_time, int num_sub_tasks, double * sub_tasks_time)
{
        Queue * Node = malloc(sizeof(Queue));
        Node -> next = NULL;
        Node -> priority = priority;
        Node -> arr_time = arr_time;
        Node -> sub_tasks_time = malloc(sizeof(double *) * num_sub_tasks);
	Node -> sub_tasks_time = sub_tasks_time;
        return Node;
}

// This function is used to destroy the Queue
void Queue_destroy(Queue * queue)
{
        while(queue != NULL)
        {
                Queue * p = queue -> next;
		free(queue -> sub_tasks_time);
                free(queue);
                queue = p;
        }
}

// This function is used to calculate the variable "r" using the rand() function
double calculate_r(double mu)
{
        double x;
        double r;
        x = (double) rand() / RAND_MAX;
        r = (-1 / mu) * log(1 - x);

        return r;
}

// This function is used to calculate the inter arrival time 
double calculate_inter_arrival_time(double lambda, double r)
{
        double inter_arr_time = lambda * exp(-lambda * r);
        inter_arr_time = ceil(inter_arr_time);
        return inter_arr_time;
}

// This function is used to calculate the service time - time it takes for the CPU to process a task
double calculate_service_time(double mu, double r)
{
        double service_time = mu * exp(-mu * r);
        service_time = ceil(service_time);
        return service_time;
}

//This function is used to calculate the number of sub tasks of a particular task
int calculate_num_sub_tasks()
{
	int num_sub_tasks = rand() / RAND_MAX % 32 + 1;
	return num_sub_tasks;
}

