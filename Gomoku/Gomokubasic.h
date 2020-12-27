#define SIZE 16    //	由于四周留空  棋盘实际大小为SIZE-2

#define WINDOW_HIGHT 640
#define WINDOW_WIDTH 640

#define BLACK -1
#define WHITE 1

int dir[8][2] = { {1,0},{1,1},{0,1},{-1,1},
				{-1,0},{-1,-1},{-1,0},{-1,1} };