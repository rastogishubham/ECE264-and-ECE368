#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"answer07.h"
#define TRUE 1
#define FALSE 0
Image * Image_load(const char * filename)
{
	FILE * fp = NULL;
	ImageHeader header;
	Image * img;
	size_t read;
	size_t read1;
	fp = fopen(filename, "rb");
	if(fp == NULL)
	{
		return NULL;
	}
	//header = malloc(sizeof(ImageHeader));
/*	if(header == NULL)
	{
		free(header);
		return NULL;
	}*/
	read = fread(&header, sizeof(ImageHeader), 1, fp);
	if(read != 1);
	{
		fprintf(stderr, "fread failed in file %s\n", filename);
		return NULL;
	}
	if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
	{
		fprintf(stderr, "magic number not the same in file %s\n", filename);
		return NULL;
	}
	if(header.width == 0 || header.height == 0)
	{
		fprintf(stderr, "width or height is 0\n");
		return NULL;
	}
	if(header.comment_len == 0)
	{
		fprintf(stderr, "comment length in %s is 0\n", filename);
		return NULL;
	}
	img = malloc(sizeof(Image));
	if(img == NULL)
	{
		fprintf(stderr, "colud not malloc for imagefor file %s\n", filename);
		return NULL;
	}
	img->comment = malloc(sizeof(char *) * header.comment_len);
	img->width = header.width;
	img->height = header.height;
	img->data = malloc(sizeof(unsigned char) * img->width * img->height);
	if(img->data == NULL)
	{
		fprintf(stderr, "data is null in %s\n", filename);
		return NULL;
	}
	read1 = fread(&img->comment, (sizeof(char *) * header.comment_len), 1, fp);
	if(read1 != 1)
	{
		fprintf(stderr, "failed to read comment in %s\n", filename);
		return NULL;
	}
	if(strchr(img->comment, '\0') == NULL)
	{
		fprintf(stderr, "the comment does not end in null byte in %s\n", filename);
		return NULL;
	}
	if(fread(&img->data, (sizeof(unsigned char)* img->height * img->width), 1, fp) != 1)
	{
		fprintf(stderr, "Failed to read image data for %s\n", filename);
		return NULL;
	}
	if(fgetc(fp) != EOF)
	{
		fprintf(stderr, "did not reach end of file for %s\n", filename);
		return NULL;
	}
	fclose(fp);
	return img;	
}
int Image_save(const char * filename, Image * image)
{
	return 0;
}
void Image_free(Image * image)
{
	if(image != NULL)
	{
		free(image->data);
		free(image->comment);
		free(image);
	}
	return ;
}
void linearNormalization(int width, int height, uint8_t * intensity)
{
	return ;
}
