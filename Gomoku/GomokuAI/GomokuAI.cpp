#include<stdio.h>
#include "Gomokubasic.h"
int chessboard[SIZE][SIZE];
FILE* fp;
FILE* in;
void init();
void input();

int main()
{
	init();
	input();
	fclose(fp);
	fclose(in);
	return 0;
}

void init()
{
	fp = fopen("chessboard.dat", "r");
	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
			fscanf(fp, "%d", &chessboard[i][j]);
	}
}
void input()
{
	in = fopen("input.in", "w");
	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
			if (chessboard[i][j] == 0)
			{
				fprintf(in, "%d %d", i, j);
				return;
			}

	}
}