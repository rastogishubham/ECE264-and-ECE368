#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"answer08.h"
List * List_createNode(const char * name)
{
	List * Node = malloc(sizeof(List));
	Node->next = NULL;
	Node->str = strdup(name);
	return(Node);
}
void List_destroy(List * list)
{
	if(list == NULL)
	{
		return;
	}
	while(list != NULL)
	{
		list  = list->next;
		free(list->str);
		free(list);
	}
	return;
}
int List_length(List * list)
{
	int len = 0;
	while(list->next != NULL)
	{
		len++;
		list = list->next;
	}
	return len;
}
List * List_merge(List * lhs, List * rhs, int(*compar)(const char * , const char*))
{
	List new = NULL;
	if(lhs->str == NULL && rhs->str == NULL)
	{
		return NULL;
	}
	if(lhs->str == NULL)
	{
		return rhs;
	}
	if(rhs->str == NULL)
	{
		return lhs;
	}
	while(lhs != NULL && rhs != NULL)
	{
		
	}
	return lhs;
}
List *  List_sort(List * list, int (*compar)(const char *, const char *))
{
	return list;
}

