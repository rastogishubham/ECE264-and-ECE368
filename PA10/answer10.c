#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"answer10.h"
#define BUFFER_SIZE 2048
typedef struct LocNode {
	long bus_offset;
	long review_offset;
	struct LocNode * next;
} LocationNode;
typedef struct BusNode {
        char * name;
        LocationNode * head;
        struct BusNode * left;
        struct BusNode * right;
} BusinessNode;
LocationNode * createlocnode(long off)
{
        LocationNode * Node = malloc(sizeof(LocationNode));
        Node->next = NULL;
        Node->bus_offset = off;
	Node->review_offset = 0;
        return(Node);
}
BusinessNode * create_node(char * business_name, long bus_offset)
{
        BusinessNode * root = malloc(sizeof(BusinessNode));
        root->name = strdup(business_name);
	root->head = createlocnode(bus_offset);
        root->left = NULL;
        root->right = NULL;
        return root;
}
LocationNode * createlist(long bus_offset, LocationNode * head)
{
	if(head == NULL)
	{
		return createlocnode(bus_offset);
	}
		head->next = createlist(bus_offset, head->next);
		return head;
}
void print_list(LocationNode * list)
{
	while(list != NULL)
	{
		LocationNode * p = list->next;
		printf("The offset in list is %ld\n", list->bus_offset);
		list = p;
	}
}

// DESTROY FUNTION

void List_destroy(LocationNode * list)
{
        while(list != NULL)
        {
                LocationNode * p = list->next;
                free(list);
                list = p;
        }
}


void destroy_tree(BusinessNode * root)
{
        if(root == NULL){return;}
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root->name);
	List_destroy(root->head);
        free(root);
}
void print_tree(BusinessNode * root)
{
        if(root == NULL) {return;}
        print_tree(root->left);
        print_tree(root->right);
        printf("%s\n", root->name);
	print_list(root->head);
}
/*void print_list(LocationNode * list)
{
	while(list != NULL)
	{
		LocationNode * p = list->next;
		printf("The offset in list is %ld\n", list->bus_offset);
		list = p;
	}
}*/

BusinessNode * tree_insert(char * name, BusinessNode * root, long bus_offset)
{
        if(root == NULL)
        {
                return create_node(name, bus_offset);
        }
        if(strcmp(name,root->name) < 0)
        {
                root->left = tree_insert(name, root->left, bus_offset);
                return root;
        }
	else if(strcmp(name, root->name) == 0)
	{
		root->head = createlist(bus_offset, root->head);
		return root;
	}
	else
	{
        	root->right = tree_insert(name, root->right, bus_offset);
        	return root;
	}
}

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

/*void List_destroy(LocationNode * list)
{
        while(list != NULL)
        {
                LocationNode * p = list->next;
                free(list);
                list = p;
        }
}*/

void readfile(const char * business_path)
{
	FILE * fp = fopen(business_path, "r");
	if(fp == NULL)
	{
		printf("Failed to open file\n");
	}
	else
	{
		printf("File can be opened\n");
	}
	char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
	long bus_offset = 0;
	long int offset = 0;
	int len = 0;
	int lcv = 0;
	offset = ftell(fp);
	BusinessNode * root = NULL;
	while(!feof(fp))
	{
		fgets(buffer, BUFFER_SIZE, fp);
		if(feof(fp))
		{
			break;
		}
                char * * strArr = explode(buffer, "\t", &len);
		bus_offset = strlen(strArr[0]) + strlen(strArr[1]) + offset + 2;
		offset = ftell(fp);
		printf("Offset = %ld\n", bus_offset);
		root = tree_insert(strArr[1], root,bus_offset);
		for(lcv = 0; lcv < len; lcv ++)
		{
			free(strArr[lcv]);
		}
		free(strArr);
	}
	print_tree(root);
	free(buffer);
	fclose(fp);
	destroy_tree(root);
}
