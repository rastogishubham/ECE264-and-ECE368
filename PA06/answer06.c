#include"answer06.h"
#include<stdio.h>
void move(int direction, int * row, int * column, int w, int h, char * * maze)
{
	if(direction == 0)
	{
		maze[*row][*column] = '.';
		*row = *row + 1;
	}
	if(direction == 1)
	{
		maze[*row][*column] = '.';
		*row = *row - 1;
	}
	if(direction == 2)
	{
		maze[*row][*column] = '.';
		*column = *column + 1;
	}
	if(direction == 3)
	{
		maze[*row][*column] = '.';
		*column = *column - 1;
	}
}
int canmove(int direction, int row, int column, int w, int h, char ** maze)
{
	if(direction == 0 && row +1 < h && column < w && maze[row+1][column] == ' ')
	{
		return 1;
	}
	else if(direction == 1 && row - 1 >= 0 && column < w && maze[row-1][column] == ' ')
	{
		return 1;
	}
	else if(direction == 2 && row < h && column + 1 < w && maze[row][column+1] == ' ')
	{
		return 1;
	}
	else if(direction == 3 && row < h && column -1 >= 0 && maze[row][column-1] == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void recurse(int direction, int row, int column, int w, int h, char ** maze)
{
	int lcv = 0;
	if(canmove(0, row, column, w, h, maze) == 1)
	{
		move(0, &row, &column, w, h, maze);
		printf("S 1\n");
		for(lcv = 0; lcv < 4; lcv++)
		{
			if(canmove(lcv, row, column, w, h, maze) == 1)
			{
				recurse(lcv, row, column, w, h, maze);
			}
		}
		move(1, &row, &column, w, h, maze);
		printf("N 1\n");
	}
	else if(canmove(1, row, column, w, h, maze) == 1)
	{
		move(1, &row, &column, w, h, maze);
		printf("N 1\n");
		for(lcv = 0; lcv < 4; lcv++)
		{
			if(canmove(lcv, row, column, w, h, maze) == 1)
			{
				recurse(lcv, row, column, w, h, maze);
			}
		}
		move(0, &row, &column, w, h, maze);
		printf("S 1\n");
	}
	else if(canmove(2, row, column, w, h, maze) == 1)
	{
		move(2, &row, &column, w, h, maze);
		printf("E 1\n");
		for(lcv = 0; lcv < 4; lcv++)
		{
			if(canmove(lcv, row, column, w, h, maze) == 1)
			{
				recurse(lcv, row, column, w, h, maze);
			}
		}
		move(3, &row, &column, w, h, maze);
		printf("W 1\n");
	}
	else if(canmove(3, row, column, w, h, maze) == 1)
	{
		move(3, &row, &column, w, h, maze);
		printf("W 1\n");
		for(lcv = 0; lcv < 4; lcv++)
		{
			if(canmove(lcv, row, column, w, h, maze) == 1)
			{
				recurse(lcv, row, column, w, h, maze);
			}
		}
		move(2, &row, &column, w, h, maze);
		printf("E 1\n");
	}
	else return;
}
	
void print_directions(char ** maze, int w, int h) {
	int row= 0;
	int column = 0;
	int lcv = 0;
	for(lcv = 0; lcv <= w; lcv++)
	{
		if(maze[0][lcv] == ' ')
		{
			column = lcv;
			break;
		}
	}
	recurse(0, row, column, w, h, maze);
	return;
}

