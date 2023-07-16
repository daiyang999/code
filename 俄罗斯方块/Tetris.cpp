#include "Tetris.h"
#include<time.h>
#include<iostream>
#include<stdlib.h>
#include"Block.h"
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<fstream>
#define RECORD_FILE "record.txt"
#define MAX_LEVEL 5
const int SPEED_NORMAL[MAX_LEVEL] = { 500,300,150,100,80 };
const int SPEED_QUICK = 30;//ms

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	delay = SPEED_NORMAL[0];
	srand(time(NULL));//�����������

	initgraph(938,896);//������Ϸ����
	loadimage(&imgBg, "res/bg2.png");//���ر���ͼƬ
	loadimage(&imgWin, "res/win.png");
	loadimage(&imgOver, "res/over.png");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
	score = 0;
	lineCount = 0;
	level = 1;
	gameOver = false;

	//��ʼ����߷�
	ifstream file(RECORD_FILE);
	if (!file.is_open()) {
		cout << RECORD_FILE << "��ʧ�ܣ�" << endl;
		highestScore = 0;
	}
	else {
		file >> highestScore;
	}
	file.close();
}

void Tetris::play()
{
	init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (1) {
		//�����û�������
		keyEvent();
		timer += getDelay();
		if (timer > delay) {
			
			timer = 0;
			drop();
			update = true;
		}
		if (update) {
			updateWindow();//��Ⱦ��Ϸ����
			update = false;
			clearLine();//������Ϸ����
		}
		if (gameOver) {
			saveScore();

			//������Ϸ��������
			displayOver();
			system("pause");
			init();
		}
		
		
	}
}

void Tetris::keyEvent()
{
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;
	if (_kbhit()) {
		ch=_getch();
		//�Ϸ����������224 72
		//�·����������224 80
		//�����������224 75
		//�ҷ����������224 77
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				rotateFlag = true;
				break;
			case 80:
				delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (rotateFlag) {
		rotate();
		update = true;
	}
	if (dx != 0) {
		//ʵ�������ƶ�
		moveLeftRight(dx);
		update = true;
	}
	
	
}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg);//���Ʊ���ͼƬ
	//���Է���
	//Block block;
	//block.draw(263,133);
	IMAGE** imgs = Block::getImages();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0)continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);
	drawScore();

	EndBatchDraw();
}
//��һ�ε��÷���0
//���ؾ�����һ�ε��ã�����˶���ms
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret=currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	if (curBlock->blockInMap(map) == false) {
		//�ѷ���̻�
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		//�����Ϸ�Ƿ����
		checkOver();
	}
	delay = SPEED_NORMAL[level-1];
}

void Tetris::clearLine()
{
	int k = rows - 1;//�洢���ݵ�����
	int lines = 0;
	for (int i = rows - 1; i >= 0; i--) {
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < cols) {
			k--;
		}
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];

		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		update = true;

		level = (score + 99) / 100;
		if (level > MAX_LEVEL) {
			gameOver = true;
		}
		lineCount += lines;
	}
	
}

void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;
	bakBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);
	setcolor(RGB(180, 180, 180));
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(670, 727, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224 - 30, 727, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", highestScore);
	outtextxy(670, 817, scoreText);
}

void Tetris::checkOver()
{
	gameOver = (curBlock->blockInMap(map) == false);
}

void Tetris::saveScore()
{
	if (score > highestScore) {
		highestScore = score;

		ofstream file(RECORD_FILE);
		file << highestScore;
		file.close();
	}
}

void Tetris::displayOver()
{
	mciSendString("stop res/bg.mp3", 0, 0, 0);
	if (level <= MAX_LEVEL) {
		putimage(262, 361, &imgOver);
		mciSendString("play res/over.mp3", 0, 0, 0);
	}
	else {
		putimage(262, 361, &imgWin);
		mciSendString("play res/win.mp3", 0, 0, 0);
	}
}
