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

