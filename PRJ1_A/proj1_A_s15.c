#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

//Teammates: 
//1) Shubham Sandeep Rastogi, PUID: 0026340022, email: rastogis@purdue.edu
//2) Aditya Girdhar, PUID: 0026492087, email: agiridh@purdue.edu


// This struct Queue has atrributes: arrival time, priority of task, service time and a pointer to the next node
typedef struct Queue_Node
{
	double arr_time;
	int priority;
	double service_time;
	struct Queue_Node * next;
}Queue;

//fuction declarations
void mode1(double lambda_0, double lambda_1, double mu, int total_tasks0, int total_tasks1);
Queue * Queue_Node_Create(int priority, double arr_time, double service_time);
double calculate_inter_arrival_time(double lambda, double r);
int queue_len(Queue * queue);
void simulator(Queue * FEL1, Queue * FEL2, int total_tasks0, int total_tasks1);
void write_mode_output(double avg_wait_0, double avg_wait_1, double avg_queue_len, double avg_CPU_util);
void mode2(char * filename);

// The function Queue_Node_Create creates a list node
Queue * Queue_Node_Create(int priority, double arr_time, double service_time) 
{
	Queue * Node = malloc(sizeof(Queue));
	Node -> next = NULL;
	Node -> priority = priority;
	Node -> arr_time = arr_time;
	Node -> service_time = service_time;
	return Node;
}

// This function is used to destroy the Queue
void Queue_destroy(Queue * queue)
{
	while(queue != NULL)
	{
		Queue * p = queue -> next;
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

// This is the main function. Functions mode1 and mode2 have been called in this function
int main(int argc, char * * argv)
{
	// For mode 1, example execution: project1-A avg_arrival_time_of_task_0 avg_arrival_time_of_task_1 avg_service_time number_of_tasks__to_be_simulated_for_each_priority
	
	// For mode 2, example execution: project1-A input.txt	

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

// This function creates the queue by calling the Queue_Node_Create function
Queue * create_FEL(int priority, double arrival_time, double service_time, Queue * FEL)
{
	if(FEL == NULL)
	{
		return Queue_Node_Create(priority, arrival_time, service_time); 
	}
	FEL -> next = create_FEL(priority, arrival_time, service_time, FEL -> next);
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
	double inter_arr_time = 0; // setting inter arrival time to 0
	double service_time = 0; // setting service arrival time to 0
	double r = 0; // setting the variable r to 0
	double tot_time_0 = 0; // setting total time for tasks with priority 0 to 0
	double tot_time_1 = 0; // setting total time for tasks with priority 1 to 0
	Queue * FEL1 = NULL; //future event list for task 0 with priority
	Queue * FEL2 = NULL; // future event list for task 1 with priority
	srand(time(NULL)); 
	for(lcv = 0; lcv < total_tasks0; lcv++) // creates the future event list for task with 0 priority by calling the create_FEL function
	{
		r = calculate_r(lambda_0);
		inter_arr_time = calculate_inter_arrival_time(lambda_0, r);
		r = calculate_r(mu);
		service_time = calculate_service_time(mu, r);
		tot_time_0 += inter_arr_time;
		FEL1 = create_FEL(0, tot_time_0, service_time, FEL1);
	}
	for(lcv = 0; lcv < total_tasks1; lcv++) // creates the future event list for task with 1 priority by calling the create_FEL function
	{
		r = calculate_r(lambda_1);
		inter_arr_time = calculate_inter_arrival_time(lambda_1, r);
		r = calculate_r(mu);
		service_time = calculate_service_time(mu, r);
		tot_time_1 += inter_arr_time;
		FEL2 = create_FEL(1, tot_time_1, service_time, FEL2);
	}
	simulator(FEL1, FEL2, total_tasks0, total_tasks1); // Calling the simulator function with created future event lists
	Queue_destroy(FEL1); // destroy the future event list of task with priority 0
	Queue_destroy(FEL2); // destroy the future event list of task with priority 1
	return;
}

// This function calculates the average waiting time for tasks with priority 0 and 1, average queue length and the average CPU utilization by simulating the arrival and departure of the tasks of priority 0 and 1 from their respective queues called temp_queue_0 and temp_queue_1.  

void simulator(Queue * FEL1, Queue * FEL2, int total_tasks0, int total_tasks1)
{
	int server_time = 0; // variable that stores the time it takes for the CPU to process a task
	int total_time = 0; // variable that stores the total time of the simulation
	Queue * temp_queue_0 = 0; // the queue used to temporarily store the tasks with priority 0
	Queue * temp_queue_1 = 0; // the queue used to temporarily store the tasks with priority 0
	int flag = 1; // If flag = 0, the server is busy. If the server is not busy, flag = 1
	int tot_service_time = 0; // variable that stores the calculated total service time
	double avg_CPU_util = 0; // variable to calculate avg. CPU utilization
	double avg_queue_len = 0; // variable to calculate avg. queue length
	int queue_0_len = 0; // variable to calculate length of the queue for tasks with priority 0
	int queue_1_len = 0; // variable to calculate length of the queue for tasks with priority 0
	int tot_queue_len = 0; // variable to store the total length of the queue
	int tot_wait_0 = 0; // variable to store the value of total wait time of task with priority 0
	int tot_wait_1 = 0; // variable to store the value of total wait time of task with priority 1
	double avg_wait_0 = 0; // avg waiting time for tasks with priority 0 
	double avg_wait_1 = 0; // avg waiting time for tasks with priority 1
	int total_tasks = total_tasks0 + total_tasks1; // variable stores the sum of the total tasks for priority 0 and 1
	int total_tasks_cpy = total_tasks; // variable stores the value of the total number of tasks 

	while(total_tasks > 0)
	{
		if(FEL1 != NULL && total_time == FEL1 -> arr_time) // add a task with priority 0 to the temp_queue_0 when total time is equal to the arrival time 
		{
			temp_queue_0 = create_FEL(0, FEL1 -> arr_time, FEL1 -> service_time, temp_queue_0); 
			FEL1 = FEL1 -> next;
	                queue_0_len = queue_len(temp_queue_0);
			tot_queue_len += queue_0_len;
		}
		if(flag == 1 && temp_queue_0 != NULL) // if server is not busy and if temp_queue_0 is not empty, process tasks with priority 0 
		{
			server_time = temp_queue_0 -> service_time;
			tot_service_time += server_time; // calculate total service time
			flag = 0; // CPU is busy
			tot_wait_0 += (total_time - temp_queue_0 -> arr_time); // calculating total wait time for tasks with priority 0
			Queue * p = temp_queue_0 -> next; // deleting the node from the queue
			free(temp_queue_0);
			temp_queue_0 = p;
		}
		if(FEL2 != NULL && total_time == FEL2 -> arr_time) // add a task with priority 0 to the temp_queue_0 when total time is equal to the arrival time 
		{
			temp_queue_1 = create_FEL(0, FEL2 -> arr_time, FEL2 -> service_time, temp_queue_1);
			FEL2 = FEL2 -> next;
	                queue_1_len = queue_len(temp_queue_1);
			tot_queue_len += queue_1_len;
		}
		if(flag == 1 && temp_queue_0 == NULL && temp_queue_1 != NULL) // if server is not busy, if temp_queue_0 is empty and if temp_queue_1 is not empty, process tasks with priority 1
		{
			server_time = temp_queue_1 -> service_time;
			tot_service_time += server_time; // calculate total service time
			flag = 0; // CPU is busy
			tot_wait_1 += (total_time - temp_queue_1 -> arr_time); // calculating total wait time for tasks with priority 1
			Queue * p = temp_queue_1 -> next; // deleting the node from the queue
			free(temp_queue_1);
			temp_queue_1 = p;
		}
		total_time++; //incrementing the total time by 1

		if(flag == 0)
		{
			server_time--; // decrement the server time
			if(server_time == 0)
			{
				total_tasks--;
				flag = 1;
			}
		}
	}
	avg_CPU_util = (double) tot_service_time / (double) total_time; // calulating avg. CPU utilization
	avg_queue_len = (double) tot_queue_len / (double) (total_tasks_cpy); // calculating avg. queue length
	avg_wait_0 = (double) tot_wait_0 / (double) (total_tasks0); // calculating avg. waiting time for tasks with priority 0
	avg_wait_1 = (double) tot_wait_1 / (double) (total_tasks1); // calculating avg. waiting time for tasks with priority 1
	
	write_mode_output(avg_wait_0, avg_wait_1, avg_queue_len, avg_CPU_util); // calling the write_mode_output function

}

// This function writes the calculated the calculated avg. wait time for tasks with priority 0 and 1, avg. queue length and avg. CPU utilization to the file proj1-a_output  
void write_mode_output(double avg_wait_0, double avg_wait_1, double avg_queue_len, double avg_CPU_util)
{
	FILE * fp;
	
	fp = fopen("proj1-a_output", "w"); //open file to write
	
	fprintf(fp, "%lf\n", avg_wait_0);
	fprintf(fp, "%lf\n", avg_wait_1);
	fprintf(fp, "%lf\n", avg_queue_len);
	fprintf(fp, "%lf\n", avg_CPU_util);
	fclose(fp);
}

// This function calculates the total length of the queue
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

// This function is called when argc = 2. The arrival times, priority and service times are read from the file input.txt and the calculated values of avg. wait time for both the tasks, avg. queue length and avg. CPU utilization are written to the file proj1-a_output
void mode2(char * filename)
{
	int total_tasks0 = 0; // variable stores the value of the total tasks for tasks with priority 0
	int total_tasks1 = 0;// variable stores the value of the total tasks for tasks with priority 1
	FILE * fp = NULL;
	fp = fopen(filename, "r"); // opening file to read
	if(fp == NULL)
	{
		printf("Not opened file\n");
		return;
	}
	char * str = malloc(sizeof(char *) * 10);
	Queue * FEL1 = NULL; // future event list for tasks with prioriy 0
	Queue * FEL2 = NULL; // future event list for tasks with prioriy 1
	int priority = 0; // variable to store the priority of task
	double arrival_time = 0; // variable to store the arrival time
	double service_time = 0; // variable to store the service time
	while(!feof(fp))
	{
		fscanf(fp, "%lf %d %lf", &arrival_time, &priority, &service_time); // read the data from the given file
		if(feof(fp))
		{
			break;
		}
		if(priority == 0)
		{
			FEL1 = create_FEL(priority, arrival_time, service_time, FEL1); //create the future event list for tasks with priority 0
			total_tasks0++;
		}
		else
		{
			FEL2 = create_FEL(priority, arrival_time, service_time, FEL2); // create the future event list for tasks with priority 1
			total_tasks1++;
		}
	}

	fclose(fp);
	simulator(FEL1, FEL2, total_tasks0, total_tasks1); // calling the simulator function with the created future event lists
	free(str);
	Queue_destroy(FEL1); // destroying the future event list of tasks with priority 0
	Queue_destroy(FEL2); // destroying the future event list of tasks with priority 1

	return;
}
