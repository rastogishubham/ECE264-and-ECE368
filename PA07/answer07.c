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
	Image * img = NULL;
	Image *  tmp_img = NULL;
	size_t read;
	size_t read1;
	int err = FALSE;
	fp = fopen(filename, "rb");
	if(!err)
	{
		if(fp == NULL)
		{
	//		fclose(fp);
			err = TRUE;
//			return NULL;
		}
	}
	//header = malloc(sizeof(ImageHeader));
/*	if(header == NULL)
	{
		free(header);
		return NULL;
	}*/
	if(!err)
	{
		read = fread(&header, sizeof(ImageHeader), 1, fp);
		if(read != 1)
		{
			//fclose(fp);
			fprintf(stderr, "fread failed in file %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
		{
			//fclose(fp);
			fprintf(stderr, "magic number not the same in file %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		if(header.width == 0 || header.height == 0 || header.width > 1000000 || header.height > 1000000)
		{
			//fclose(fp);
			fprintf(stderr, "width or height is 0\n");
			err = TRUE;

//			return NULL;
		}
	}
	if(!err)
	{
		if(header.comment_len == 0 || header.comment_len > 10000000)
		{
	//		fclose(fp);
			fprintf(stderr, "comment length in %s is 0\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		tmp_img = malloc(sizeof(Image));
		if(tmp_img == NULL)
		{
	//		fclose(fp);
			fprintf(stderr, "colud not malloc for imagefor file %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		tmp_img->comment = malloc(sizeof(char) * header.comment_len);
		tmp_img->width = header.width;
		tmp_img->height = header.height;
		tmp_img->data = malloc(sizeof(uint8_t) * tmp_img->width * tmp_img->height);
		if(tmp_img->data == NULL)
		{
	//		fclose(fp);
			fprintf(stderr, "data is null in %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		read1 = fread(tmp_img->comment, sizeof(char), header.comment_len, fp);
		if(read1 != header.comment_len || tmp_img->comment[header.comment_len - 1] != '\0')
		{
	//		fclose(fp);
			fprintf(stderr, "failed to read comment in %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	/*if(!err)
	{
		if(tmp_img->comment[header.comment_len - 1] != '\0')
		{
	//		fclose(fp);
			fprintf(stderr, "the comment does not end in null byte in %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}*/
	if(!err)
	{
		if(fread(tmp_img->data, sizeof(uint8_t), header.height * header.width * sizeof(uint8_t), fp) != header.height * header.width *sizeof(uint8_t))
		{
	//		fclose(fp);
			fprintf(stderr, "Failed to read image data for %s\n", filename);
			err = TRUE;
//			return NULL;
		}
	}
	if(!err)
	{
		uint8_t byte;
		if(fread(&byte, sizeof(uint8_t), 1, fp) != 0)
		{
			err = TRUE;	
		}
	}
	if(!err)
	{
		img = tmp_img;
		tmp_img = NULL;
	}
	if(tmp_img != NULL)
	{
		free(tmp_img->comment);
		free(tmp_img->data);
		free(tmp_img);
	}
	if(fp)
	{
		fclose(fp);
	}
	return img;	
}
int Image_save(const char * filename, Image * image)
{
	FILE * fp = NULL;
	fp = fopen(filename, "w");
	ImageHeader header;
	header.width =  image->width;
	header.height = image->height;
	header.comment_len = strlen(image->comment) + 1;
	header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
	//printf("%d", header.width);
	if(fp == NULL)
	{
		return 0;

	}
	if(fwrite(&header, sizeof(ImageHeader), 1, fp) != 1)
	{
		fclose(fp);
		return 0;
	}
	if(fwrite(image->comment, sizeof(char), header.comment_len, fp) != header.comment_len)
	{
		fclose(fp);
		return 0;
	}
	if(fwrite(image->data, sizeof(uint8_t), image->height * image->width, fp) != image->height * image->width)
	{
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}
void Image_free(Image * image)
{
	free(image->data);
	free(image->comment);
	free(image);
	return ;
}
void linearNormalization(int width, int height, uint8_t * intensity)
{
	int lcv1 = 0;
	int lcv2 = 0;
	uint8_t max = intensity[0];
	uint8_t min = intensity[0];
	for(lcv1 = 0; lcv1 < (width * height); lcv1++)
	{
		if(min > intensity[lcv1])
		{
			min = intensity[lcv1];
		}
		if(max < intensity[lcv1])
		{
			max = intensity[lcv1];
		}
	}
	for(lcv2 = 0; lcv2 < (width * height); lcv2++)
	{
		intensity[lcv2] = (intensity[lcv2] - min) * 255.0 / (max - min);
	}

	return ;
}
