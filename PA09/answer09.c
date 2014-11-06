#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"answer09.h"

BusinessNode * create_node(char * stars, char * name, char * address)
{
	BusinessNode * root = malloc(sizeof(BusinessNode));
	return root;
}
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
	
	return NULL;
}
BusinessNode * load_tree_from_file(char * filename)
{
	return NULL;
}
BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	return NULL;
}
void print_node(BusinessNode * node)
{
	return;
}
void print_tree(BusinessNode * tree)
{
	return;
}
void destroy_tree(BusinessNode * root)
{
	if(root == NULL){return;}	
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root->name);
	free(root->stars);
	free(root->address);
	free(root);
	return;
}
