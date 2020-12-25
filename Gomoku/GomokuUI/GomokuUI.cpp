#include <graphics.h>					//包含EGE的头文件
#include <math.h>

#define SIZE 15
#define WINDOW_HIGHT 600
#define WINDOW_WIDTH 640

#define BLACK -1
#define WHITE 1

void Play();
void Init();

int chessboard[SIZE][SIZE];
int Color = BLACK;

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
	initgraph(WINDOW_WIDTH, WINDOW_HIGHT);			//初始化图形界面
	setbkcolor(EGERGB(245, 222, 179));
	setcaption("五子棋");

	unit_width = WINDOW_WIDTH / (SIZE + 2.0);
	unit_hight = WINDOW_HIGHT / (SIZE + 2.0);

	double start_x = unit_width;
	double end_x = WINDOW_WIDTH - unit_width;
	double start_y = unit_hight;
	double end_y = WINDOW_HIGHT - unit_hight;

	line(start_x, start_y, start_x, end_y);		//绘制边框
	line(start_x, start_y, end_x, start_y);
	line(start_x, end_y, end_x, end_y);
	line(end_x, start_y, end_x, end_y);

	for (double i = start_x; i < end_x; i += unit_width)	//绘制竖线
		line(i, start_y, i, end_y);
	for (double  i = start_y; i < end_y; i += unit_hight)	//绘制横线
		line(start_x, i, end_x, i);
}

void Play()
{
	int x, y;
	bool click = false;
	mouse_msg Mouse_msg;

	while (1)
	{
		Mouse_msg = mouse_msg();

		while (mousemsg())
		{
			
			Mouse_msg = getmouse();
			delay_fps(60);
			if (Mouse_msg.is_left())
			{
				fillellipse(round(Mouse_msg.x /unit_hight)*unit_hight, round(Mouse_msg.y / unit_width) * unit_width, unit_hight/2, unit_width/2);
				break;
			}
		}
		/*if (click==true)
		{
			click = false;
			x = Mouse_msg.x;
			y = Mouse_msg.y;


			fillellipse(x, y, unit_width, unit_hight);
		}*/
		//int clickCount = 0;
		//for (; is_run(); delay_fps(60)) {
		//	//定义个鼠标结构体变量
		//	mouse_msg msg = { 0 };
		//	//获取鼠标消息
		//	while (mousemsg()) {
		//		msg = getmouse();
		//	}

		//	if (msg.is_left() && msg.is_down()) {
		//		clickCount++;
		//		fillellipse(msg.x, msg.y, 40, 40);
		//	}

		//	xyprintf(20, 20, "点击次数：%d", clickCount);
		//}
	}
}