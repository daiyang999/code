#pragma once
#include<graphics.h>
#include<vector>
#include<mmsystem.h>
#include<math.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
//表示落子的位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0,int c=0):row(r),col(c){}
};

typedef enum {
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//获取棋盘大小
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//检查棋局是否结束

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;//棋盘大小
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的顶部边界
	float chessSize;//棋子的大小
	vector<vector<int>> chessMap;//存储当前棋局的棋子分布：0：空白 1：黑子 -1：白子
	bool playerFlag;//true：黑子走 false：白子走

	void updateGameMap(ChessPos* pos);
	bool checkWin();//检查是否胜利
	ChessPos lastPos;//最后落子点的位置
};

