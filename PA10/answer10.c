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
LocationNode * createNode()
{
        LocationNode * Node = malloc(sizeof(LocationNode));
        Node->next = NULL;
        Node->bus_offset = 0;
	Node->review_offset = 0;
        return(Node);
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

void List_destroy(LocationNode * list)
{
        while(list != NULL)
        {
                LocationNode * p = list->next;
                free(list);
                list = p;
        }
}

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
	int len = 0;
	int lcv = 0;
	while(!feof(fp))
	{
		bus_offset = ftell(fp);
		fgets(buffer, BUFFER_SIZE, fp);
		if(feof(fp))
		{
			break;
		}
                char * * strArr = explode(buffer, "\t", &len);
                printf("Business name = %s\n", strArr[1]);
		for(lcv = 0; lcv < len; lcv ++)
		{
			free(strArr[lcv]);
		}
		free(strArr);
		printf("Bus offset = %ld\n", bus_offset);
                printf("Buffer = %s\n", buffer);
	}
	free(buffer);
	fclose(fp);	
}

