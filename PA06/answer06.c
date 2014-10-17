#include"answer06.h"
#include<stdio.h>
/*void travel(char ** maze, int x, int y, int w, int h, char direction)
{
	int space = 0;
	int x1 = x, x2= x, x3 = x, x4 = x;
	int y1 = y, y2 = y, y3 = y, y4 = y;
	if(((direction  == 'S' || direction == 'N') && maze[x][y+1] == 'X' && maze[x][y-1] == 'X') || ((direction == 'W' || direction == 'E') && maze[x+1][y] != 'X' && maze[x-1][y] != 'X'))
	{
		return;
	}
	if(x1+1 < h && y1 < w && maze[x1+1][y1] != 'X') //&& maze[x1+1][y1] != '.')
	{
		direction = 'S';
		while(x1+1 < h && y1 < w && maze[x1+1][y1] != 'X' && maze[x1][y1-1] != ' ' && maze[x1][y1+1] != ' ')
		{	
			//maze[x1][y1] = '.';
			++x1;
			++space;
		}
		printf("S %d\n", space);
		travel(maze, x1, y1, w, h, direction);
		printf("N %d\n", space);
	}
	space = 0;
	if(x2 < h && y2+1 < w && maze[x2][y2+1] != 'X')// && maze[x2][y2+1] != '.')
	{
		direction = 'E';
		while(x2 < h && y2+1 < w && maze[x2][y2 + 1] != 'X' && maze[x2+1][y2] != ' ' && maze[x2-1][y2] != ' ')
		{
//			maze[x2][y2] = '.';
			++y2;
			++space;
		}
		printf("E %d\n", space);
		travel(maze, x2, y2, w, h, direction);
		printf("W %d\n", space);
	}
	space = 0;
	if(x3-1 >= 0 && y3 >= 0 && maze[x3-1][y3] != 'X')// && maze[x3-1][y] != '.')
	{
		direction = 'N';
		while(x3-1 < h && y3 < w && maze[x3-1][y3] != 'X' && maze[x3][y3+1] != ' ' && maze[x3][y3-1] != ' ')
		{
//			maze[x3][y3] = '.';
			--x3;
			++space;
		}
		printf("N %d\n", space);
		travel(maze, x3, y3, w, h, direction);
		printf("S %d\n", space);
	}
	space = 0;
	if(x4 >= 0 && y4-1 >= 0 && maze[x4][y4-1] != 'X') //&& maze[x4][y4-1] != '.')
	{
		direction = 'W';
		while(x4 < h && y4-1 < w && maze[x4][y4-1] != 'X' && maze[x4+1][y4] != ' ' && maze[x4-1][y4] != ' ')
		{
//			maze[x4][y4] = '.';
			--y4;
			++space;
		}
		printf("W %d\n", space);
		travel(maze, x4, y4, w, h, direction);
		printf("E %d\n", space);
	}
	return;
}*/
void move(int direction, int * row, int * column, int w, int h, char * * maze)
{
	if(direction == 0)// && * row + 1 < w && * column < h && maze[*row +1][column] != 'X') 
	{
		maze[*row][*column] = '.';
		*row = *row + 1;
	}
	if(direction == 1) //&& * row - 1 >= 0 && * column < h && maze[*row - 1][column] != 'X')
	{
		maze[*row][*column] = '.';
		*row = *row - 1;
	}
	if(direction == 2)// && * row < w && *column + 1 < h && maze[*row][*column - 1] != 'X')
	{
		maze[*row][*column] = '.';
		*column = *column + 1;
	}
	if(direction == 3)// && *row < w && *column - 1 < h
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
	//char direction = ' ';
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
//	travel(maze, x, y, w, h, direction);
	recurse(0, row, column, w, h, maze);
	return;
}

