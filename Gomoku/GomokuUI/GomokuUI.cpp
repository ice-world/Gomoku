<<<<<<< HEAD
#include <graphics.h>
#include <stdio.h>

int main()
{
    initgraph(640, 480);
    ;
    closegraph();
    return 0;
}
=======
#include <graphics.h>					//包含EGE的头文件

#define SIZE 15
#define WINDOW_HIGHT 640
#define WINDOW_WIDTH 640

void Init();

int chessboard[SIZE][SIZE];

double unit_width;
double unit_hight;

int main()
{
	Init();
	getch();
	closegraph();
	return 0;
}

void Init()
{
	initgraph(WINDOW_WIDTH, WINDOW_HIGHT);			//初始化图形界面
	setbkcolor(EGERGB(245, 222, 179));

	unit_width = WINDOW_WIDTH / (SIZE + 2);
	unit_hight = WINDOW_HIGHT / (SIZE + 2);

	double start_x = unit_width;
	double end_x = WINDOW_WIDTH - unit_width;

	double start_y = unit_hight;
	double end_y = WINDOW_HIGHT - unit_hight;

	line(start_x, start_y, start_x, end_y);
	line(start_x, start_y, end_x, start_y);
	line(start_x, end_y, end_x, end_y);
	line(end_x, start_y, end_x, end_y);
}
>>>>>>> d8ce2dac3e8791c62b337d422bf25d82b30524d5
