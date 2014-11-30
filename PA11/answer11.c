#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"answer11.h"

HuffNode * HuffNode_create(int value)
{
	HuffNode * tree = malloc(sizeof(HuffNode));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}
void HuffNode_destroy(HuffNode * tree)
{
	if(tree == NULL){ return; }
	HuffNode_destroy(tree->left);
	HuffNode_destroy(tree->right);
	free(tree);
}
Stack * Stack_create()
{
	Stack * st = malloc(sizeof(Stack));
	st -> head = NULL;
	return st;
}
void Stack_destroy(Stack * stack)
{
	if(stack == NULL){ return; }
	while(stack->head != NULL)
	{
		StackNode * sn = stack->head->next;
		HuffNode_destroy(stack->head->tree);
		free(stack->head);
		stack->head = sn;
	}
	free(stack);
}
int Stack_isEmpty(Stack * stack)
{
	if(stack == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
HuffNode * Stack_popFront(Stack * stack)
{
	if(stack == NULL){ return NULL; }
	HuffNode * hn = stack->head->tree;
	StackNode * sn = stack->head->next;
	free(stack->head);
	stack->head = sn;
	return hn;
}
void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	StackNode * sn = malloc(sizeof(StackNode));
	sn->tree = tree;
	stack->head->next = sn;
}
void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode * tree1 = Stack_popFront(stack);
	HuffNode * tree2 = Stack_popFront(stack);
	HuffNode * tree3 = HuffNode_create(0);
	tree3->left = tree1;
	tree3->right = tree2;
	Stack_pushFront(stack, tree3);
}
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	return NULL;
}
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	return NULL;
}	
