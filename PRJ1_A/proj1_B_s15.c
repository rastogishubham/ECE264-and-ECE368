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
	int num_sub_tasks;
        double * sub_tasks_time;
        struct Queue_Node * next;
}Queue;

//Function Declerations


//Function Definitions

// This is the main function. Functions mode1 and mode2 have been called in this function
int main(int argc, char * argv)
{
	if(argc == 5)
        {
		double lambda_0 = atof(argv[1]); // avg. arrival time of tasks with priority 0
                double lambda_1 = atof(argv[2]); // avg. arrival time of tasks with priority 1
                double mu = atof(argv[3]); // avg. service time of task
                int total_tasks0 = atoi(argv[4]); // total tasks with priority 0
                int total_tasks1 = total_tasks0; // total tasks with priority 1
                mode1(lambda_0, lambda_1, mu, total_tasks0, total_tasks1); // Calling function mode1
        }
        else if(argc == 2)
        {
                mode2(argv[1]); //Calling function mode2
        }

	return EXIT_SUCCESS;
}

// The function Queue_Node_Create creates a list node
Queue * Queue_Node_Create(int priority, double arr_time, int num_sub_tasks, double * sub_tasks_time)
{
        Queue * Node = malloc(sizeof(Queue));
        Node -> next = NULL;
        Node -> priority = priority;
        Node -> arr_time = arr_time;
	Node -> num_sub_tasks = num_sub_tasks;
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
double * create_subtasks_servicetimes(double mu, double r, int num_sub_tasks)
{
	double * sub_tasks_time = malloc(sizeof(double *) * num_sub_tasks);
	int lcv = 0;
        double service_time = 0;
	for(lcv = 0; lcv < num_sub_tasks; lcv++)
	{
		service_time = mu * exp(-mu * r);
       		service_time = ceil(service_time);
		sub_tasks_time[lcv] = service_time;
	}
        return sub_tasks_time;
}

//This function is used to calculate the number of sub tasks of a particular task
int calculate_num_sub_tasks()
{
	int num_sub_tasks = rand() / RAND_MAX % 32 + 1;
	return num_sub_tasks;
}

// This function creates the queue by calling the Queue_Node_Create function
Queue * create_FEL(int priority, double arrival_time, int num_sub_tasks, double * sub_tasks_time, Queue * FEL)
{
        if(FEL == NULL)
        {
                return Queue_Node_Create(priority, arrival_time, num_sub_tasks, sub_tasks_time);
        }
        FEL -> next = create_FEL(priority, arrival_time, num_sub_tasks, sub_tasks_time, FEL -> next);
        return FEL;
}

// This function creates the future event lists for both tasks. Each node of the list has the calculated arrival times, service times and the priority for each tasks
void mode1(double lambda_0, double lambda_1, double mu, int total_tasks0, int total_tasks1)
{
        if(lambda_0 + lambda_1 > mu)
        {
                printf("Enter values so that lambda_1 + lambda_0 is less than mu\n");
                return;
        }
        int lcv = 0; // loop counter variable
	int num_sub_tasks = 0;
	int tot_sub_tasks = 0;
        double inter_arr_time = 0; // setting inter arrival time to 0
        double * sub_tasks_time = NULL; // setting service arrival time to 0
        double r = 0; // setting the variable r to 0
        double tot_time_0 = 0; // setting total time for tasks with priority 0 to 0
        double tot_time_1 = 0; // setting total time for tasks with priority 1 to 0
        Queue * FEL1 = NULL; //future event list for task 0 with priority
        Queue * FEL2 = NULL; // future event list for task 1 with priority
        srand(time(NULL));
        for(lcv = 0; lcv < total_tasks0; lcv++) // creates the future event list for task with 0 priority by calling the create_FEL function
        {
		num_sub_tasks = calculate_num_sub_tasks();
                r = calculate_r(lambda_0);
                inter_arr_time = calculate_inter_arrival_time(lambda_0, r);
                r = calculate_r(mu);
                sub_tasks_time = create_subtasks_servicetimes(mu, r, num_sub_tasks);
                tot_time_0 += inter_arr_time;
		tot_sub_tasks += num_sub_tasks;
                FEL1 = create_FEL(0, tot_time_0, num_sub_tasks, sub_tasks_time, FEL1);
        }
        for(lcv = 0; lcv < total_tasks1; lcv++) // creates the future event list for task with 1 priority by calling the create_FEL function
        {
		num_sub_tasks = calculate_num_sub_tasks;
                r = calculate_r(lambda_1);
                inter_arr_time = calculate_inter_arrival_time(lambda_1, r);
                r = calculate_r(mu);
                sub_tasks_time = create_subtasks_servicetimes(mu, r, num_sub_tasks);
                tot_time_1 += inter_arr_time;
		tot_sub_tasks += num_sub_tasks;
                FEL2 = create_FEL(1, tot_time_1, num_sub_tasks, sub_tasks_time, FEL2);
        }
        simulator(FEL1, FEL2, total_tasks0, total_tasks1); // Calling the simulator function with created future event lists
        Queue_destroy(FEL1); // destroy the future event list of task with priority 0
        Queue_destroy(FEL2); // destroy the future event list of task with priority 1
        return;
}

int calc_free_processors(int * processors)
{
	int lcv = 0;
	int free_processors = 0;
	for(lcv = 0; lcv < 64; lcv++)
	{
		if(processors[i] != 0)
		{
			free_processors++;
		}
	}
	return free_processors;
}

Queue * pop_node(Queue * node, int queue_node_pos)
{
	if(queue_node_pos == 0)
	{
		Queue * temp = node;
		node = node -> next;
		free(temp);
		return node;
	}
	Queue * prev = NULL;
	while(queue_node_pos != 0)
	{
		prev = node;
		node = node -> next;
		queue_node_pos--;
	}
	prev -> next = node -> next;
	free(node);
	return prev;
}

int * reduce_service_time(int * processor, int * sub_tasks)
{
	int lcv = 0;
	for(lcv = 0; lcv < 64; lcv++)
	{
		if(processor[lcv] > 0)
		{
			processor[lcv]--;
		}
		else
		{
			* sub_tasks = * sub_tasks - 1;
		}
	}
	return processor;
}
	
void simulator(Queue * FEL1, Queue * FEL2, int total_tasks0, int total_tasks1, int tot_sub_tasks)
{
	int * processors = malloc(sizeof(int *) * 64);
	int total_time = 0;
	int free_processors = 0;
	Queue * temp_queue_0 = NULL;
	Queue * temp_queue_1 = NULL;
	Queue * head_0 = NULL;
	Queue * head_1 = NULL;
	int lcv = 0;
	int sub_task_pos = 0;
	int queue_node_pos_0 = 0;
	int queue_node_pos_1 = 0;
	while(tot_sub_tasks > 0)
	{
		if(FEL1 != NULL && total_time == FEl1 -> arr_time)
		{
			temp_queue_0 = create_FEL(0, FEL1 -> arr_time, FEL1 -> num_sub_tasks, FEL1 -> sub_tasks_time, temp_queue_0);
			FEL1 = FEL1 -> next;
		}
		if(FEL2 != NULL && total_time == FEL2 -> arr_time)
		{
			temp_queue_1 = create_FEL(1, FEL2 -> arr_time, FEL2 -> num_sub_tasks, FEL2 -> sub_tasks_time, temp_queue_1);
			FEL2 = FEL -> next;
		}
		free_processors = calc_free_processors(processors);
		head_0 = temp_queue_0;
		head_1 = temp_queue_1;
		while(free_processors > 0 && (head_0 != NULL || head_1 != NULL))
		{
			free_processors = calc_free_processors(processors);
			if(head_0 != NULL && head_0 -> num_sub_tasks <= free_processors)
			{
				for(lcv = 0; lcv < 64; lcv++)
				{
					if(processors[lcv] == 0)
					{
						processors[lcv] = head_0 -> sub_tasks_time[sub_task_pos];
						sub_task_pos++;
					}
				}
				head_0 = head_0 -> next;
				temp_queue_0 = pop_node(temp_queue_0, queue_node_pos_0);
			}
			else if(head_0 != NULL && head_0 -> num_sub_tasks > free_processors)
			{
				head_0 = head_0 -> next;
				queue_node_pos_0++;
			}
			sub_task_pos = 0;
			free_processors = calc_free_processors(processors);
			if(head_0 == NULL && head_1 != NULL && head_1 -> num_sub_tasks <= free_processors)
			{
				for(lcv = 0; lcv < 64; lcv++)
				{
					if(processors[lcv] == 0)
					{
						processors[lcv] = head_1 -> sub_tasks_time[sub_task_pos];
						sub_task_pos++;
					}
				}
				head_1 = head_1 -> next;
				temp_queue_1 = pop_node(temp_queue_1, queue_node_pos_1);
			}
			else if(head_0 == NULL && head_1 != NULL && head_1 -> num_sub_tasks > free_processors)
			{
				head_1 = head_1 -> next;
				queue_node_pos_1++;
			}
			sub_tasks_pos = 0;
		}
		total_time++
		processors = reduce_service_time(processors, &num_sub_tasks);
	}
}
