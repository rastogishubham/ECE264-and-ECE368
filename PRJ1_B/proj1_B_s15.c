#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

// Name: Shubham Sandeep Rastogi 	PUID: 0026340022 	email: rastogis@purdue.edu
// Name: Aditya Giridhar         	PUID: 0026492087	email: agiridh@purdue.edu

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
void simulator(Queue * FEL1, Queue * FEL2, int total_tasks0, int total_tasks1, int tot_sub_tasks, double lbf_avg);
void mode1(double lambda_0, double lambda_1, double mu, int total_tasks0, int total_tasks1);
double * create_subtasks_servicetimes(double mu, int num_sub_tasks);
void mode2(char * filename);
void calculate_max_min(double * max, double * min, double * sub_tasks_time, int num_sub_tasks);
int queue_len(Queue * queue);
void write_mode_output(double avg_wait_0, double avg_wait_1, double avg_queue_len, double avg_CPU_util, double lbf_avg);
void find_max_min(double * sub_tasks_time, int num_sub_tasks, double * max, double * min);
void find_mu(double * sub_tasks_time, int num_sub_tasks, double * mu);
 
// This is the main function. Functions mode1 and mode2 have been called in this function
int main(int argc, char * * argv)
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
        Node -> sub_tasks_time = malloc(sizeof(double) * num_sub_tasks);
	Node -> sub_tasks_time = memcpy(Node -> sub_tasks_time, sub_tasks_time, (sizeof(double) * num_sub_tasks));
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
double * create_subtasks_servicetimes(double mu, int num_sub_tasks)
{
	double * sub_tasks_time = malloc(sizeof(double) * num_sub_tasks);
	int lcv = 0;
        double service_time = 0;
	double r = 0;
	for(lcv = 0; lcv < num_sub_tasks; lcv++)
	{
		r = calculate_r(mu);
		service_time = mu * exp(-mu * r);
       		service_time = ceil(service_time);
		sub_tasks_time[lcv] = service_time;
	}
        return sub_tasks_time;
}

//This function is used to calculate the number of sub tasks of a particular task
int calculate_num_sub_tasks()
{
	int num_sub_tasks = rand()  % 32 + 1;
	return num_sub_tasks;
}

// This function creates the queue by calling the Queue_Node_Create function
Queue * create_FEL(int priority, double arrival_time, int num_sub_tasks, Queue * FEL, double * sub_tasks_time)
{
        if(FEL == NULL)
        {
                return Queue_Node_Create(priority, arrival_time, num_sub_tasks, sub_tasks_time);// base case
        }
        FEL -> next = create_FEL(priority, arrival_time, num_sub_tasks, FEL -> next, sub_tasks_time); // recursive case
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
	int num_sub_tasks = 0; // number of sub tasks
	int tot_sub_tasks = 0; // total number of sub tasks
        double inter_arr_time = 0; // setting inter arrival time to 0
        double * sub_tasks_time = NULL; // setting service arrival time to 0
        double r = 0; // setting the variable r to 0
        double tot_time_0 = 0; // setting total time for tasks with priority 0 to 0
        double tot_time_1 = 0; // setting total time for tasks with priority 1 to 0
	double lbf = 0; // load balance factor
	double lbf_tot = 0; // total load balance factor
	double lbf_avg = 0; // average load balance factor
	double max = 0; //Maximum sub tasks service time of a particular task 
	double min = 0; //Minimum sub tasks service time of a particular task
        Queue * FEL1 = NULL; //future event list for task 0 with priority
        Queue * FEL2 = NULL; // future event list for task 1 with priority
        srand(time(NULL));
        for(lcv = 0; lcv < total_tasks0; lcv++) // creates the future event list for task with 0 priority by calling the create_FEL function
        {
		num_sub_tasks = calculate_num_sub_tasks();
                r = calculate_r(lambda_0);
                inter_arr_time = calculate_inter_arrival_time(lambda_0, r);
                sub_tasks_time = create_subtasks_servicetimes(mu, num_sub_tasks);
                tot_time_0 += inter_arr_time;
		tot_sub_tasks += num_sub_tasks;
                FEL1 = create_FEL(0, tot_time_0, num_sub_tasks, FEL1, sub_tasks_time);
		find_max_min(sub_tasks_time, num_sub_tasks, &max, & min);
		lbf = (max - min) * mu;
		lbf_tot += lbf;
		free(sub_tasks_time);
        }
        for(lcv = 0; lcv < total_tasks1; lcv++) // creates the future event list for task with 1 priority by calling the create_FEL function
        {
		num_sub_tasks = calculate_num_sub_tasks();
                r = calculate_r(lambda_1);
                inter_arr_time = calculate_inter_arrival_time(lambda_1, r);
                r = calculate_r(mu);
                sub_tasks_time = create_subtasks_servicetimes(mu, num_sub_tasks);
                tot_time_1 += inter_arr_time;
		tot_sub_tasks += num_sub_tasks;
                FEL2 = create_FEL(1, tot_time_1, num_sub_tasks, FEL2, sub_tasks_time);
		find_max_min(sub_tasks_time, num_sub_tasks, &max, &min);
		lbf = (max - min) * mu;
		lbf_tot += lbf;
		free(sub_tasks_time);
        }
	lbf_avg = lbf_tot / (double) (total_tasks0 + total_tasks1); // calculating load balance factor
        simulator(FEL1, FEL2, total_tasks0, total_tasks1, tot_sub_tasks, lbf_avg); // Calling the simulator function with created future event lists
        Queue_destroy(FEL1); // destroy the future event list of task with priority 0
        Queue_destroy(FEL2); // destroy the future event list of task with priority 1
        return;
}

// This function calculates the number of free processors
int calc_free_processors(int * processors)
{
	int lcv = 0;
	int free_processors = 0;
	for(lcv = 0; lcv < 64; lcv++)
	{
		if(processors[lcv] == 0)
		{
			free_processors++;
		}
	}
	return free_processors;
}

// This function is used to pop the node from the queue
Queue * pop_node(Queue * node, int queue_node_pos)
{
	
	if(queue_node_pos == 0)
	{
		Queue * temp = node;
		node = node -> next;
		free(temp -> sub_tasks_time);
		free(temp);
		return node;
	}
	Queue * prev = NULL;
	prev = node;
	Queue * temp = node;
	queue_node_pos--;
	temp  = temp -> next;
	while(queue_node_pos != 0)
	{
		temp = temp -> next;
		queue_node_pos--;
		prev = prev -> next;
	}
	prev -> next = temp -> next;
	free(temp -> sub_tasks_time);
	free(temp);
	return node;
}

//This function reduces the service time of the processors sub tasks and calculates the number of total sub tasks that have to be processed
int * reduce_service_time(int * processor, int * sub_tasks)
{
	int lcv = 0;
	for(lcv = 0; lcv < 64; lcv++)
	{
		if(processor[lcv] > 0)
		{
			processor[lcv]--;
			if(processor[lcv] == 0)
			{
				* sub_tasks = * sub_tasks - 1;
			}
		}
	}
	return processor;
}

//This function simulates the whole scenario
void simulator(Queue * FEL1, Queue * FEL2, int total_tasks0, int total_tasks1, int tot_sub_tasks, double lbf_avg)
{
	int * processors = malloc(sizeof(int) * 64);//Store's the service times of the sub tasks being processed
	long int tot_service_time = 0;//stores the total time the processors are busy 
	int lcv = 0;//variable to control for loops
	int total_time = 0;//stores the total time of the simulation
	int free_processors = 0;//stores the number of the free processors left at any time of the simulation
	int queue_len_0 = 0;//stores the length of the temporary queue of jobs with priority 0 at any time
	int queue_len_1 = 0;//stores the length of the temporary queue of jobs with priority 0 at any time
	int tot_queue_len = 0;//stores the total length of both temporary queue's at any time
	int tot_wait_0 = 0;//the total wait time for jobs with priority 0
	int tot_wait_1 = 0;//the total wait time for jobs with priority 1
	Queue * temp_queue_0 = NULL;//temporary queue for jobs with priority 0
	Queue * temp_queue_1 = NULL;//temporary queue for jobs with priority 1
	Queue * head_0 = NULL;//pointer to temporary queue 0
	Queue * head_1 = NULL;//pointer to temporary queue 1
	int sub_task_pos = 0;//stores the position of the sub tasks in the array of sub tasks
	int queue_node_pos_0 = 0;//stores the position of the temporary queue 0's node 
	int queue_node_pos_1 = 0;//stores the position of the temporary queue 1's node
	int num_sub_tasks_cpy = 0;//copy of the number of sub tasks
	double avg_queue_len = 0;//stores the average queue length of the simulation
	double avg_wait_0 = 0;//stores the average wait time of the jobs with priority 0
	double avg_wait_1 = 0;//stores the average wait time of the jobs with priority 0
	long double global_avg_CPU_util = 0;//stores the global average CPU utilization
	
	for(lcv = 0; lcv < 64; lcv++)
	{
		processors[lcv] = 0;
	}
	while(tot_sub_tasks > 0)
	{
		if(FEL1 != NULL && total_time == FEL1 -> arr_time)
		{
			temp_queue_0 = create_FEL(0, FEL1 -> arr_time, FEL1 -> num_sub_tasks, temp_queue_0, FEL1 -> sub_tasks_time);
			FEL1 = FEL1 -> next;
			queue_len_0 = queue_len(temp_queue_0);
			tot_queue_len += queue_len_0;
		}
		if(FEL2 != NULL && total_time == FEL2 -> arr_time)
		{
			temp_queue_1 = create_FEL(1, FEL2 -> arr_time, FEL2 -> num_sub_tasks, temp_queue_1, FEL2 -> sub_tasks_time);
			FEL2 = FEL2 -> next;
			queue_len_1 = queue_len(temp_queue_1);
			tot_queue_len += queue_len_1;
		}
		free_processors = calc_free_processors(processors);
		head_0 = temp_queue_0;
		head_1 = temp_queue_1;
		queue_node_pos_0 = 0;
		queue_node_pos_1 = 0;
		while(free_processors > 0 && head_0 != NULL)
		{
			free_processors = calc_free_processors(processors);
			if(head_0 != NULL && head_0 -> num_sub_tasks <= free_processors)
			{
				num_sub_tasks_cpy = head_0 -> num_sub_tasks;
				for(lcv = 0; (lcv < 64 && num_sub_tasks_cpy > 0); lcv++)
				{
					if(processors[lcv] == 0)
					{
						processors[lcv] = head_0 -> sub_tasks_time[sub_task_pos];
						tot_service_time += processors[lcv];
						sub_task_pos++;
						num_sub_tasks_cpy--;
					}
				}
				tot_wait_0 += (total_time - head_0 -> arr_time);
				head_0 = head_0 -> next;
				temp_queue_0 = pop_node(temp_queue_0, queue_node_pos_0);
				sub_task_pos = 0;
			}
			else if(head_0 != NULL && head_0 -> num_sub_tasks > free_processors)
			{
				head_0 = head_0 -> next;
				queue_node_pos_0++;
			}
		}
		sub_task_pos = 0;
		while(temp_queue_0 == NULL && free_processors > 0 && head_1 != NULL)
		{
			free_processors = calc_free_processors(processors);
			if(temp_queue_0 == NULL && head_1 != NULL && head_1 -> num_sub_tasks <= free_processors)
			{
				num_sub_tasks_cpy = head_1 -> num_sub_tasks;
				for(lcv = 0; (lcv < 64 && num_sub_tasks_cpy > 0); lcv++)
				{
					if(processors[lcv] == 0)
					{
						processors[lcv] = head_1 -> sub_tasks_time[sub_task_pos];
						tot_service_time += processors[lcv];
						sub_task_pos++;
						num_sub_tasks_cpy--;
					}
				}
				tot_wait_1 += (total_time - head_1 -> arr_time);
				head_1 = head_1 -> next;
				temp_queue_1 = pop_node(temp_queue_1, queue_node_pos_1);
				sub_task_pos = 0;
			}
			else if(head_0 == NULL && head_1 != NULL && head_1 -> num_sub_tasks > free_processors)
			{
				head_1 = head_1 -> next;
				queue_node_pos_1++;
			}
			sub_task_pos = 0;
		}
		total_time++;
		free_processors = calc_free_processors(processors);
		if(free_processors < 64)
		{
			processors = reduce_service_time(processors, &tot_sub_tasks);
		}
	}
	free(processors);
	avg_queue_len = (double) tot_queue_len / (double) (total_tasks0 + total_tasks1);
	avg_wait_0 = (double) tot_wait_0 / (double) (total_tasks0);
	avg_wait_1 = (double) tot_wait_1 / (double) (total_tasks1);
	global_avg_CPU_util = (double) tot_service_time  / (double) (total_time * 64);
	write_mode_output(avg_wait_0, avg_wait_1, avg_queue_len, global_avg_CPU_util, lbf_avg);
}

// This function creates the future event lists for both tasks. Each node of the list has the calculated arrival times, service times and the priority for each tasks for mode 2
void mode2(char * filename)
{
	FILE * fp = NULL;//File pointer
	Queue * FEL1 = NULL;//Future event list for jobs with priority 0
	Queue * FEL2 = NULL;//Future event list for jobs with priority 1
	double arrival_time = 0;//Arrival time of a particular task
	int priority = 0;//priority of a particular task
	int num_sub_tasks = 0;//number of sub tasks of a particular task
	double * sub_tasks_time;//arrya to store the service times of the sub tasks of a particular task
	int lcv = 0;//variable to control for loops
	int tot_sub_tasks = 0;//stores the total number of sub tasks for the simulation
	int total_tasks0 = 0;//stores the total number of tasks of priority 0
	int total_tasks1 = 0;//stores the totak number of tasks of priority 1
	double lbf = 0;//value of load balancing factor of a partcular task
	double lbf_tot = 0;//sum of all the load balancing factors of all tasks
	double lbf_avg = 0;//avearge load balancing factor of all tasks
	double max = 0;//maximum service time of a sub task for a given task
	double min = 0;//minimum service time of a sub tasks for a given task
	double mu = 0;//average rate of service time for a given sub task

	fp = fopen(filename, "r"); //open file to read
	if(fp == NULL)
	{
		printf("file not opened\n");
		return;
	}	

	while(!feof(fp))
	{
		fscanf(fp, "%lf %d %d", &arrival_time, &priority, &num_sub_tasks);
		if(feof(fp))
		{
			break;
		}	
		tot_sub_tasks += num_sub_tasks;
		sub_tasks_time = malloc(sizeof(double) * num_sub_tasks);

		for(lcv = 0; lcv < num_sub_tasks; lcv++)
		{
			fscanf(fp, " %lf", &sub_tasks_time[lcv]);
		}
		if(priority == 0)
		{
			FEL1 = create_FEL(priority, arrival_time, num_sub_tasks, FEL1, sub_tasks_time);
			total_tasks0++;
		}
		else
		{
			FEL2 = create_FEL(priority, arrival_time, num_sub_tasks, FEL2, sub_tasks_time);
			total_tasks1++;
		}
		find_max_min(sub_tasks_time, num_sub_tasks, &max, &min);
		find_mu(sub_tasks_time, num_sub_tasks, &mu);
		lbf = (max - min) * mu;
		lbf_tot += lbf;
	}

	fclose(fp);
	lbf_avg = lbf_tot / (double) (total_tasks1 + total_tasks0);
	simulator(FEL1, FEL2, total_tasks0, total_tasks1, tot_sub_tasks, lbf_avg);
	free(sub_tasks_time);
	Queue_destroy(FEL1); // destroying the future event list for task 0
	Queue_destroy(FEL2); // destroying future event list for task 1

	return;
}

//this function calculates the total length of a given queue
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

//this fucntion writes the output of the simulation to a file
void write_mode_output(double avg_wait_0, double avg_wait_1, double avg_queue_len, double global_avg_CPU_util, double lbf_avg)
{
        FILE * fp;

        fp = fopen("proj1_output", "w"); //open file to write

        fprintf(fp, "%lf\n", avg_wait_0);
        fprintf(fp, "%lf\n", avg_wait_1);
        fprintf(fp, "%lf\n", avg_queue_len);
        fprintf(fp, "%lf\n", global_avg_CPU_util);
	fprintf(fp, "%lf\n", lbf_avg);
        fclose(fp);
}

//this fucntion calculates the maximum and minimum service times of a sub task of a particular task
void find_max_min(double * sub_tasks_time, int num_sub_tasks, double * max, double * min)
{
	int lcv = 0;
	* min = sub_tasks_time[0];
	* max = sub_tasks_time[0];
	for(lcv = 0; lcv < num_sub_tasks; lcv++)
	{
		if(* min > sub_tasks_time[lcv])
		{
			* min = sub_tasks_time[lcv];
		}
		if(* max < sub_tasks_time[lcv])
		{
			* max = sub_tasks_time[lcv];
		}
	}
}

//this fucntion calculates the average rate of service time of sub tasks of a particular task
void find_mu(double * sub_tasks_time, int num_sub_tasks, double * mu)
{
	int lcv = 0;
	int total = 0;
	for(lcv = 0; lcv < num_sub_tasks; lcv++)
	{
		total += sub_tasks_time[lcv];
	}
	* mu = (double) num_sub_tasks / total;	
}
