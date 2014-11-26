#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"answer10.h"
#define BUFFER_SIZE 20000
long get_reviews(int, int *, FILE *, FILE *);
typedef struct LocNode {
	long bus_offset;
	long review_offset;
	int num_of_rev;
	struct LocNode * next;
} LocationNode;

typedef struct BusNode {
        char * name;
        LocationNode * head;
        struct BusNode * left;
        struct BusNode * right;
} BusinessNode;

void destroy_strArr(char * * strArr, int len)
{
  int ind;
  for(ind = 0; ind < len; ++ind)
    free(strArr[ind]);
  free(strArr);
}


LocationNode * createlocnode(long b_off, int count, long r_off)
{
        LocationNode * Node = malloc(sizeof(LocationNode));
        Node->next = NULL;
        Node->bus_offset = b_off;
	Node->review_offset = r_off;
	Node->num_of_rev = count;
        return(Node);
}
BusinessNode * create_node(char * business_name, long bus_offset, int count, long review_offset)
{
        BusinessNode * root = malloc(sizeof(BusinessNode));
        root->name = strdup(business_name);
	root->head = createlocnode(bus_offset, count, review_offset);
        root->left = NULL;
        root->right = NULL;
        return root;
}
LocationNode * createlist(long bus_offset, LocationNode * head, int count, long review_offset)
{
	if(head == NULL)
	{
		return createlocnode(bus_offset, count, review_offset);
	}
		head->next = createlist(bus_offset, head->next, count, review_offset);
		return head;
}
void print_list(LocationNode * list)
{
	while(list != NULL)
	{
		LocationNode * p = list->next;
		printf("The offset in list is %ld\n", list->bus_offset);
		printf("the review offset is %ld\n", list->review_offset);
		printf("The number of reviews are %d\n", list->num_of_rev);
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

BusinessNode * tree_insert(char * name, BusinessNode * root, long bus_offset, int count, long review_offset)
{
        if(root == NULL)
        {
                return create_node(name, bus_offset, count , review_offset);
        }
        if(strcmp(name,root->name) < 0)
        {
                root->left = tree_insert(name, root->left, bus_offset, count, review_offset);
                return root;
        }
	else if(strcmp(name, root->name) == 0)
	{
		root->head = createlist(bus_offset, root->head, count , review_offset);
		return root;
	}
	else
	{
        	root->right = tree_insert(name, root->right, bus_offset, count, review_offset);
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
void readfile(const char * business_path, const char * reviews_path)
{
	FILE * fp = fopen(business_path, "r");
	FILE * fp2 = fopen(reviews_path, "r");
	FILE * fp_tmp = fopen(reviews_path, "r");
	if(fp == NULL || fp2 == NULL)
	{
		printf("Failed to open file\n");
	}
	else
	{
		printf("File can be opened\n");
	}
	char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
	long bus_offset = 0;
	long review_offset = 0;
	int len = 0;
	int count = 0;
	BusinessNode * root = NULL;
	while(!feof(fp))
	{
		bus_offset = ftell(fp);
		fgets(buffer, BUFFER_SIZE, fp);
		if(feof(fp))
		{
			break;
		}
                char * * strArr = explode(buffer, "\t", &len);
		review_offset = get_reviews(atoi(strArr[0]), &count, fp2, fp_tmp);
		printf("Id=%s, offset = %ld, revoff = %ld\n", strArr[0], bus_offset, review_offset);
		root = tree_insert(strArr[1], root, bus_offset, count, review_offset);
		count = 0;
		review_offset = 0;
		destroy_strArr(strArr, len);
	}
	print_tree(root);
	free(buffer);
	fclose(fp);
	fclose(fp2);
	destroy_tree(root);
}

long get_reviews(int id, int * count, FILE * fp, FILE * fp_tmp)
{
	char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int len = 0;
	long review_offset = -1;
	long rev_temp = 0;
	while(!feof(fp))
	{
		rev_temp = ftell(fp);
		fgets(buffer, BUFFER_SIZE, fp);
		if(feof(fp))
		{
			break;
		}
		char * * strArr = explode(buffer, "\t", &len);
		if(atoi(strArr[0]) == id && review_offset == -1)
		{
			review_offset = rev_temp;
		}
		if(atoi(strArr[0]) == id)
		{
			* count = * count + 1;
		}
		else
		{
			destroy_strArr(strArr, len);
			break;
		}
		destroy_strArr(strArr, len);
		fgets(buffer, BUFFER_SIZE, fp_tmp);
	}
	printf("ftell fp = %ld, ftell fp_tmp = %ld\n", ftell(fp), ftell(fp_tmp));
//	if(review_offset != -1)
//	{
		fseek(fp, ftell(fp_tmp), SEEK_SET);
//	}
	free(buffer);
	return review_offset;
}
