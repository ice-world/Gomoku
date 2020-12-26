#include <graphics.h>					//����EGE��ͷ�ļ�
#include <math.h>
#include<windows.h>

#define SIZE 16    //	������������  ����ʵ�ʴ�СΪSIZE-2

#define WINDOW_HIGHT 640
#define WINDOW_WIDTH 640

#define BLACK -1
#define WHITE 1

void Play();
void Init();
void Click(int& x, int& y);
int Winning_check();
bool Winning_check_onedir(int t, int x, int y,int color);

int chessboard[SIZE][SIZE];
int color = BLACK;
int dir[8][2] = { {1,0},{1,1},{0,1},{-1,1},
				{-1,0},{-1,-1},{-1,0},{-1,1} };
bool again = false;

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
	initgraph(WINDOW_WIDTH, WINDOW_HIGHT);			//��ʼ��ͼ�ν���
	cleardevice();
	setbkcolor(EGERGB(245, 222, 179));

	setcaption("������");

	unit_width = WINDOW_WIDTH / (SIZE);
	unit_hight = WINDOW_HIGHT / (SIZE);

	double start_x = unit_width;
	double end_x = WINDOW_WIDTH - unit_width;
	double start_y = unit_hight;
	double end_y = WINDOW_HIGHT - unit_hight;

	line((int)start_x, (int)start_y, (int)start_x, (int)end_y);		//���Ʊ߿�
	line((int)start_x, (int)start_y, (int)end_x, (int)start_y);
	line((int)start_x, (int)end_y, (int)end_x, (int)end_y);
	line((int)end_x, (int)start_y, (int)end_x, (int)end_y);

	for (double i = start_x; i < end_x; i += unit_width)	//��������
		line((int)i, (int)start_y, (int)i, (int)end_y);
	for (double i = start_y; i < end_y; i += unit_hight)	//���ƺ���
		line((int)start_x, (int)i, (int)end_x, (int)i);

	color = WHITE;  //���ڿ�ʼ��Ϸʱ����һ����ɫת������˳�ʼ��ΪWHITE
}

void Play()
{
	int x, y;
	for (; is_run(); delay_fps(60))
	{
		Click(x, y);
		int win_check = Winning_check();
		if (win_check != 0)
		{
			Sleep(500);
			if (win_check == 1)
				MessageBox(NULL, TEXT("�����ʤ"), TEXT("��Ϸ����"), MB_SYSTEMMODAL);
			if (win_check == -1)
				MessageBox(NULL, TEXT("�����ʤ"), TEXT("��Ϸ����"), MB_SYSTEMMODAL);
			if (MessageBox(NULL, TEXT("�Ƿ�����һ��"), TEXT("��Ϸ����"), MB_SYSTEMMODAL | MB_YESNO) == IDYES)
			{
				again = true;
				return;
			}
			else
				return;
		}
	}
}

void Click(int& x, int& y)
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
		y = (int)round(y / unit_hight);
		x = (int)round(x / unit_width);
		if (chessboard[y][x] != 0)
		{
			MessageBox(NULL, TEXT("�����п�λ��λ��������"), TEXT(""), MB_SYSTEMMODAL);
			color = -color;  //���ڶ���ɫ���Ƶ�ά��,���������ʱҪר�Ÿı���ɫ
		}
		else if (x < 1 || x >= SIZE || y < 1 || y >= SIZE)
		{
			MessageBox(NULL, TEXT("��������������"), TEXT(""), MB_SYSTEMMODAL);
			color = -color;
		}
		else
		{
			chessboard[y][x] = color;				//Ϊ������ʾ�Ͻ�������ʾ��λ���������е�λ����ԣ���xyλ�öԻ�
			fillellipse((int)(x * unit_width), (int)(y * unit_hight), (int)(unit_width / 2), (int)(unit_hight / 2));
		}
	}
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