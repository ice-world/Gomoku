#include<stdio.h>
#include<string.h>
#include "Gomokubasic.h"


FILE* fp;
FILE* in;
FILE* test;
void init();
void input();
void Judge(int x,int y);

int num_count(int x, int y, int d, int color);

int chessboard[SIZE][SIZE];
int score[SIZE][SIZE];
int color = WHITE;
int main()
{
	init();
	for (int i = 1; i < SIZE; i++)
		for (int j = 1; j < SIZE; j++)
			Judge(i,j);
	input();
	fclose(in);
	fclose(test);
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
	fclose(fp);

	memset(score, 0, sizeof(score));
}
void input()
{
	in = fopen("input.in", "w");
	test = fopen("test.in", "w");
	int x = 1, y = 1;
	int max = 0;
	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			if (score[i][j] >= max)
			{
				x = i;
				y = j;
				max = score[i][j];
			}
			if (chessboard[i][j] == 0)
				fprintf(test, "%5d", score[i][j]);
			else
				fprintf(test, "    5");
		}
		fprintf(test, "\n");
	}
	fprintf(in, "%d %d", x, y);
}

void Judge(int x,int y)
{
	int n = 0;
	if (chessboard[x][y] != 0)
		return;
	int my_score = 0;
	int opp_score = 0;
	int my[8] = {0};
	int opp[8] = { 0 };
	int f;//测试变量，临时使用
	for (int i = 0; i < 4; i++)
	{
		my_score = num_count(x, y, i,color)+ num_count(x, y, i+4, color) ;
		opp_score = num_count(x, y, i, -color)+ num_count(x, y, i + 4, -color);
		f = my_score;
		if (f >= 3)
			score[x][y] += f*1000;
		else
		f = opp_score;
		if (f >= 3)
			score[x][y] += f*1000;
	}
	score[x][y] += (my_score + opp_score) * 10;
}
int num_count(int x, int y, int d, int color)      //区域扫描
{
	int count = 0;
	if (chessboard[x + dir[d][0]][y + dir[d][1]] == -color)
		return 0;
	for (int i = 1; i < 5; i++)
	{
		if (x + i * dir[d][0] >= SIZE || x + i * dir[d][0] < 1 || y + i * dir[d][1] >= SIZE || y + i * dir[d][1] < 1)
			return count;
		if (chessboard[x + i * dir[d][0]][y + i * dir[d][1]] == -color)
				return --count;
		else if(chessboard[x + i * dir[d][0]][y + i * dir[d][1]] == 0)
			return count;
		count++;
	}
	return count;
}