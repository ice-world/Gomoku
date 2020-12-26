#include <graphics.h>					//����EGE��ͷ�ļ�
#include <math.h>
#include<windows.h>

#define SIZE 14
#define WINDOW_HIGHT 640
#define WINDOW_WIDTH 640

#define BLACK -1
#define WHITE 1

void Play();
void Init();
void Click(int& x, int& y);

int chessboard[SIZE + 2][SIZE + 2];
int color = BLACK;

double unit_width;
double unit_hight;


int main()
{
	Init();
	Play();
	closegraph();
	return 0;
}

void Init()
{
	initgraph(WINDOW_WIDTH, WINDOW_HIGHT);			//��ʼ��ͼ�ν���
	setbkcolor(EGERGB(245, 222, 179));

	setcaption("������");

	unit_width = WINDOW_WIDTH / (SIZE + 2.0);
	unit_hight = WINDOW_HIGHT / (SIZE + 2.0);

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
			MessageBox(NULL, TEXT("�����п�λ��λ��������"), TEXT(""), MB_SYSTEMMODAL);
		else if (x < 1 || x >= SIZE + 2 || y < 1 || y >= SIZE + 2)
			MessageBox(NULL, TEXT("��������������"), TEXT(""), MB_SYSTEMMODAL);
		else
		{
			chessboard[y][x] = color;	//Ϊ������ʾ�Ͻ�������ʾ��λ���������е�λ����ԣ���xyλ�öԻ�
			fillellipse((int)(x * unit_width), (int)(y * unit_hight), (int)(unit_width / 2), (int)(unit_hight / 2));
		}

	}
}