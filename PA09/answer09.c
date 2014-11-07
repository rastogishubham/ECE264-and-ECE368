#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"answer09.h"

char * * explode(const char * str, const char * delims, int * arrLen)
{
        int N = 0;
        int ind = 0;
        for(ind = 0; ind < strlen(str); ind++)
        {
                if(strchr(delims, str[ind]) != NULL)
                {
                        N++;
                }
        }
        *arrLen = N+1;
        char * * strArr = malloc((N + 1) * sizeof(char *));
        strArr[0] = '\0';
        int last = 0;
        ind = 0;
        int arrInd = 0;
        for(ind = 0; ind < strlen(str); ind ++)
        {
                if(strchr(delims, str[ind]) != NULL)
                {
                        strArr[arrInd] = malloc(sizeof(char) * (ind  - last + 1));
                        memcpy(strArr[arrInd], &str[last],  ind - last);
                        strArr[arrInd][ind - last] = '\0';
                        last = ind + 1;
                        arrInd++;
                }
        }
        strArr[arrInd] = malloc(sizeof(char *) * (ind- last + 1));
        memcpy(strArr[arrInd], &str[last], ind - last);
        strArr[arrInd][ind - last] = '\0';
        return(strArr);
}


BusinessNode * create_node(char * stars, char * name, char * address)
{
	BusinessNode * root = malloc(sizeof(BusinessNode));
	root->name = name;
	root->stars = stars;
	root->address = address;
	root->left = NULL;
	root->right = NULL;
	return root;
}
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
	if(root == NULL)
	{
		return node;
	}
	if(strcmp(node->name,root->name) <= 0)
	{ 
		root->left = tree_insert(node, root->left);
		return root;
	}
	root->right = tree_insert(node, root->right); 
	return root;
}
BusinessNode * load_tree_from_file(char * filename)
{
	char line[2049];
	char * delims = "\t";
	int len = 0;
	FILE * fp;
	BusinessNode * root = NULL;
	BusinessNode * node = NULL;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		return NULL;	
	}
	while(fgets(line, 2049, fp) != 0)
	{
		char * * strArr = explode(line, delims, &len);
		node = create_node(strArr[0], strArr[1], strArr[2]);
		root = tree_insert(node, root);
		free(strArr);
	}
	fclose(fp);
	return root;
}
BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(strcmp(name, root->name) ==  0)
	{
		return root;
	}
	if(strcmp(name, root->name) < 0)
	{
		return tree_search_name(name, root->left);
	}
	else
	{
		return tree_search_name(name, root->right);
	}
	
}
void print_node(BusinessNode * node)
{
	printf("%s\n", node->name);
	printf("===================================\n");
	printf("Stars:\n");
	printf("      %s\n", node->stars);
	printf("Address:\n");
	printf("        %s\n", node->address);
}
void print_tree(BusinessNode * tree)
{
	if(tree == NULL){return;}
	print_tree(tree->left);
	print_tree(tree->right);
	print_node(tree);
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
}
