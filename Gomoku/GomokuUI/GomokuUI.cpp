#include <graphics.h>					//包含EGE的头文件
#include <math.h>
#include<windows.h>
#include <stdio.h>
#include<Gomokubasic.h>

void Play();
void Init();
bool Click(int& x, int& y);
int Winning_check();
bool Winning_check_onedir(int t, int x, int y,int color);
void AI_input(int &x_i,int &y_i);

int chessboard[SIZE][SIZE];
int color = BLACK;
int dir[8][2] = { {1,0},{1,1},{0,1},{-1,1},
				{-1,0},{-1,-1},{-1,0},{-1,1} };
bool again = false;

FILE* fp;
int game_mode = 2;
double unit_width;
double unit_hight;

int main()
{
AGAIN:
	Init();
	Play();
	if (again == true)
		goto AGAIN;
	closegraph();
	return 0;
}

void Init()
{
	memset(chessboard, 0, sizeof(chessboard));
	initgraph(WINDOW_WIDTH, WINDOW_HIGHT);			//初始化图形界面
	cleardevice();
	setbkcolor(EGERGB(245, 222, 179));
	setcaption("五子棋");

	fp = fopen("chessboard.dat", "w");
	again = false;

	unit_width = WINDOW_WIDTH / (SIZE);
	unit_hight = WINDOW_HIGHT / (SIZE);

	double start_x = unit_width;
	double end_x = WINDOW_WIDTH - unit_width;
	double start_y = unit_hight;
	double end_y = WINDOW_HIGHT - unit_hight;

	line((int)start_x, (int)start_y, (int)start_x, (int)end_y);		//绘制边框
	line((int)start_x, (int)start_y, (int)end_x, (int)start_y);
	line((int)start_x, (int)end_y, (int)end_x, (int)end_y);
	line((int)end_x, (int)start_y, (int)end_x, (int)end_y);

	for (double i = start_x; i < end_x; i += unit_width)	//绘制竖线
		line((int)i, (int)start_y, (int)i, (int)end_y);
	for (double i = start_y; i < end_y; i += unit_hight)	//绘制横线
		line((int)start_x, (int)i, (int)end_x, (int)i);

	color = BLACK;  
}

void Play()
{
	int x, y;
	bool click = false;
	for (; is_run(); delay_fps(60))
	{
		click = Click(x, y);
		if (click)
		{
			if (game_mode == 2)						//AI交互
			{
				int x_i, y_i;
				AI_input(x_i, y_i);
				chessboard[x_i][y_i] = color;				//为了在显示上将棋子显示的位置于数组中的位置相对，将xy位置对换
				fillellipse((int)(y_i * unit_width), (int)(x_i * unit_hight), (int)(unit_width / 2), (int)(unit_hight / 2));
				if (color == BLACK)
				{
					setfillcolor(EGERGB(255, 255, 255));
					color = -color;
				}
				else if (color == WHITE)
				{
					setfillcolor(EGERGB(0, 0, 0));
					color = -color;
				}

			}
			int win_check = Winning_check();
			if (win_check != 0)
			{
				Sleep(500);
				if (win_check == 1)
					MessageBox(NULL, TEXT("白棋获胜"), TEXT("游戏结束"), MB_SYSTEMMODAL);
				if (win_check == -1)
					MessageBox(NULL, TEXT("黑棋获胜"), TEXT("游戏结束"), MB_SYSTEMMODAL);
				if (MessageBox(NULL, TEXT("是否再来一局"), TEXT("游戏结束"), MB_SYSTEMMODAL | MB_YESNO) == IDYES)
				{
					again = true;
					return;
				}
				else
					return;
			}

		}
	}
}

bool Click(int& x, int& y)
{
	mouse_msg Mouse_msg = { 0 };
	bool click = false;

	click = false;
	while (mousemsg())
	{
		Mouse_msg = getmouse();
		if (Mouse_msg.is_left() && Mouse_msg.is_down())
		{
			click = true;
		}
	}
	if (click == true)
	{
		click = false;
		x = Mouse_msg.x;
		y = Mouse_msg.y;
		
		y = (int)round(y / unit_hight);
		x = (int)round(x / unit_width);
		if (chessboard[y][x] != 0)
		{
			MessageBox(NULL, TEXT("请在有空位的位置上落子"), TEXT(""), MB_SYSTEMMODAL| MB_ICONWARNING);
		}
		else if (x < 1 || x >= SIZE || y < 1 || y >= SIZE)
		{
			MessageBox(NULL, TEXT("请在棋盘内落子"), TEXT(""), MB_SYSTEMMODAL | MB_ICONWARNING);
		}
		else
		{
			chessboard[y][x] = color;				//为了在显示上将棋子显示的位置于数组中的位置相对，将xy位置对换
			fillellipse((int)(x * unit_width), (int)(y * unit_hight), (int)(unit_width / 2), (int)(unit_hight / 2));
			if (color == BLACK)
			{
				setfillcolor(EGERGB(255, 255, 255));
				color = -color;
			}
			else if (color == WHITE)
			{
				setfillcolor(EGERGB(0, 0, 0));
				color = -color;
			}
			return true;
			

		}

	}
	return false;
}

int Winning_check()
{
	for (int t = 0; t < 8; t++)
	{
		for (int i = 1; i < SIZE; i++)
			for (int j = 1; j < SIZE; j++)
			{
				if(chessboard[i][j]!=0)
					if(Winning_check_onedir(t,i,j,chessboard[i][j]))
						return chessboard[i][j];
			}
	}
	return 0;
}

bool Winning_check_onedir(int d,int x,int y,int c)
{
	for (int i = 1; i < 5; i++)
	{
		if (x + i * dir[d][0] >= SIZE || x + i * dir[d][0] < 1 || y + i * dir[d][1] >= SIZE || y + i * dir[d][1] < 1)
			return false;
		if (chessboard[x + i * dir[d][0]][y + i * dir[d][1]] != c)
			return false;
	}
	return true;
}

void AI_input(int &x_i,int &y_i)
{
	fp = fopen("chessboard.dat", "w");
	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
			fprintf(fp, "%d ", chessboard[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
	ShellExecute(NULL, TEXT("open"), TEXT("GomokuAI.exe"), TEXT(""), TEXT(""), SW_HIDE);
	Sleep(200);
	FILE* in;
	in = fopen("input.in", "r");
	fscanf(in, "%d%d", &x_i, &y_i);
	fclose(in);
}