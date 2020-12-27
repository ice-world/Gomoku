# Gomoku
简单的五子棋游戏  
开发目的仅为对自己能力的训练  
水平不高，多多包涵  

# 环境依赖
基于20.08版本的EGE图形库开发，若要编译源代码，请在EGE官方网站下载并配置EGE图形库
https://xege.org/
  
# AI与程序的交互方式
1.AI默认执白(后手)(选择先后手的功能预计在后续版本中增加)  
2.玩家落子后，交互界面将调用当前目录下名为"GomokuAI.exe"的程序  
3.同时，主程序将生成一个文件"chessboard.dat",将棋盘界面输出.空位为0,白棋为1,黑棋为-1.  
4."GomokuAI.exe"需要根据棋盘信息,生成"input.in"文件,以"x y"的格式,输出落子点,然后结束程序.  
5.不断循环,实现人机对战.