#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"
using namespace std;
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();//初始化
	void play();//开始游戏

private:
	void keyEvent();
	void updateWindow();
	int getDelay();//返回距离上一次调用该函数，间隔了多长时间
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void drawScore();
	void checkOver();
	void saveScore();
	void displayOver();

private:
	int delay;
	bool update;
	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;
	int score;
	int level;//当前的关卡
	int lineCount;//当前已经消除的行
	int highestScore;//最高分
	bool gameOver;

	Block* curBlock;
	Block* nextBlock;//预告方块
	Block bakBlock;

	IMAGE imgOver;
	IMAGE imgWin;
};

