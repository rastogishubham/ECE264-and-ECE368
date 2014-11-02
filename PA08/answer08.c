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
	while(list != NULL)
	{
		List * p = list->next;
		free(list->str);
		free(list);
		list = p;
	}
}
int List_length(List * list)
{
	int len = 0;
	while(list != NULL)
	{
		len++;
		list = list->next;
	}
	return len;
}
List * List_merge(List * lhs, List * rhs, int(*compar)(const char * , const char*))
{
	int cmp = 0;
	if(lhs == NULL){ return rhs;}
	else if(rhs == NULL){ return lhs;}
	List * new = NULL;
	cmp = compar(lhs->str, rhs->str);
	if(cmp <= 0)
	{
		new = lhs;
		lhs = lhs->next;
	}
	else
	{
		new = rhs;
		rhs = rhs->next;
	}
	List * new2 = new;
	while(lhs != NULL && rhs != NULL)
	{
		//printf("S");
		cmp = compar(lhs->str, rhs->str);
		if(cmp <= 0)
		{
			new2->next = lhs;
			new2 = new2->next;
			lhs = lhs->next;
		}
		else
		{
			new2->next = rhs;
			new2 = new2->next;
			rhs = rhs->next;
		}
	}
	if(lhs != NULL)
	{
		while(lhs != NULL)
		{
		//	printf("A");
			new2->next = lhs;
			new2 = new2->next;
			lhs = lhs->next;
		}
	}
	if(rhs != NULL)
	{
		while(rhs != NULL)
		{
		//	printf("B");
			new2->next = rhs;
			new2 = new2->next;
			rhs = rhs->next;
		}
	}
/*	if(cmp <= 0)
	{
		lhs->next = List_merge(lhs->next, rhs, compar);
		return lhs;
	}
	else
	{
		rhs->next = List_merge(rhs->next, lhs, compar);
		return rhs;
	}*/
	return new;
}
List *  List_sort(List * list, int (*compar)(const char *, const char *))
{
	int len = List_length(list);
	if(len <= 1)
	{
		return list;
	}
	int lhs_len = len / 2;
	int lhs_ind = 0;
	List * lhs = malloc(sizeof(List));
	List * rhs = malloc(sizeof(List));
	while(lhs_ind < lhs_len)
	{
		if(lhs_ind == lhs_len - 1)
		{
			rhs->next = list->next;
			list->next = NULL;
		}
		List * p = lhs->next;
		lhs_ind++;
		list = p;
	}
	lhs->next= list;
	lhs = List_sort(lhs, compar);
	rhs = List_sort(rhs, compar);
	list = List_merge(lhs, rhs, compar);
	return list;
}

