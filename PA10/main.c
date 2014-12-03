#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"answer10.h"
struct YelpDataBST * create_business_bst(const char *, const char * );
void destroy_business_bst(struct YelpDataBST *);
void print_bst(struct YelpDataBST *);
int main(int argc, char * * argv)
{
	struct YelpDataBST * bst = create_business_bst("bus.tsv", "reviews.tsv");
	print_bst(bst);
	destroy_business_bst(bst);
	return EXIT_SUCCESS;
}
