#include"answer06.h"
#include<stdio.h>
void travel(char ** maze, int x, int y, int w, int h)
{
	int space = 0;
	int x1 = x, x2= x, x3 = x, x4 = x;
	int y1 = y, y2 = y, y3 = y, y4 = y;
	if(x1+1 < h && y1 < w && maze[x1+1][y1] != 'X') //&& maze[x1+1][y1] != '.')
	{
		while(x1+1 < h && y1 < w && maze[x1+1][y1] != 'X')
		{	
			//maze[x1][y1] = '.';
			++x1;
			++space;
		}
		printf("S %d\n", space);
		travel(maze, x1, y1, w, h);
	}
	space = 0;
	if(x2 < h && y2+1 < w && maze[x2][y2+1] != 'X')// && maze[x2][y2+1] != '.')
	{
		while(x2 < h && y2+1 < w && maze[x2][y2 + 1] != 'X')
		{
//			maze[x2][y2] = '.';
			++y2;
			++space;
		}
		printf("E %d\n", space);
		travel(maze, x2, y2, w, h);
	}
	space = 0;
	if(x3-1 >= 0 && y3 >= 0 && maze[x3-1][y3] != 'X')// && maze[x3-1][y] != '.')
	{
		while(x3-1 < h && y3 < w && maze[x3-1][y3] != 'X')
		{
//			maze[x3][y3] = '.';
			--x3;
			++space;
		}
		printf("N %d\n", space);
		travel(maze, x3, y3, w, h);
	}
	space = 0;
	if(x4 >= 0 && y4-1 >= 0 && maze[x4][y4-1] != 'X') //&& maze[x4][y4-1] != '.')
	{
		while(x4 < h && y4-1 < w && maze[x4][y4-1] != 'X')
		{
//			maze[x4][y4] = '.';
			--y4;
			++space;
		}
		printf("W %d\n", space);
		travel(maze, x4, y4, w, h);
	}
	return;
}
void print_directions(char ** maze, int w, int h) {

	int x = 0;
	int y = 0;
	int lcv = 0;
	for(lcv = 0; lcv <= w; lcv++)
	{
		if(maze[0][lcv] == ' ')
		{
			y = lcv;
			break;
		}
	}
	travel(maze, x, y, w, h);
	return;
}

