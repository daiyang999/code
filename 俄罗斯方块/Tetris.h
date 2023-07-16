#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"
using namespace std;
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();//��ʼ��
	void play();//��ʼ��Ϸ

private:
	void keyEvent();
	void updateWindow();
	int getDelay();//���ؾ�����һ�ε��øú���������˶೤ʱ��
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
	int level;//��ǰ�Ĺؿ�
	int lineCount;//��ǰ�Ѿ���������
	int highestScore;//��߷�
	bool gameOver;

	Block* curBlock;
	Block* nextBlock;//Ԥ�淽��
	Block bakBlock;

	IMAGE imgOver;
	IMAGE imgWin;
};

