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
			new2->next = lhs;
			new2 = new2->next;
			lhs = lhs->next;
		}
	}
	if(rhs != NULL)
	{
		while(rhs != NULL)
		{
			new2->next = rhs;
			new2 = new2->next;
			rhs = rhs->next;
		}
	}
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
	List * lhs = list;
	List * rhs = NULL;
	List * tmp = list;
	while(tmp != NULL)
	{
		lhs_ind++;
		List * new = tmp->next;
		if(lhs_ind == lhs_len)
		{
			tmp->next = NULL;
			rhs = new;
		}
		tmp = new; 
	}
	List * first = List_sort(lhs, compar);
	List * second = List_sort(rhs, compar);
	List * merge = List_merge(first, second, compar);
	return merge;
}

