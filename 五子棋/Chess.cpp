#include "Chess.h"
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	initgraph(897, 895,EW_SHOWCONSOLE);
	//显示棋盘图片
	loadimage(0, "res/qipan2.jpg");
	mciSendString("play res/start.wav", 0, 0, 0);

	loadimage(&chessBlackImg, "res/black.png",chessSize,chessSize,true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize,true);

	//清理棋盘
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4;
	int len;
	bool ret = false;

	do {
		//左上角判断
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0)ret = true;
			break;
		}

		//右上角判断
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row;
			pos->col = col+1;
			if (chessMap[pos->row][pos->col] == 0)ret = true;
			break;
		}

		//左下角判断
		int x3 = leftTopPosX;
		int y3 = leftTopPosY + chessSize;
		len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
		if (len < offset) {
			pos->row = row+1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0)ret = true;
			break;
		}

		//右下角判断
		int x4 = leftTopPosX + chessSize;
		int y4 = leftTopPosY + chessSize;
		len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col+1;
			if (chessMap[pos->row][pos->col] == 0)ret = true;
			break;
		}

	} while (0);
	
	
	return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play res/down7.WAV", 0, 0, 0);
	int x = margin_x + chessSize * pos->col-0.5*chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(1500);
		if (playerFlag == false) {
			mciSendString("play res/不错.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
		}
		_getch();//暂停
		return true;
	}
	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;//黑白方交换走棋
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;

	//水平方向
	for (int i = 0; i < 5; i++) {
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i + 2] == chessMap[row][col - i] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4] ) {
			return true;
		}
	}
	//垂直方向
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row-i][col] == chessMap[row-i+1][col] &&
			chessMap[row-i][col] == chessMap[row - i + 2][col] &&
			chessMap[row-i][col] == chessMap[row - i + 3][col] &&
			chessMap[row-i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}
	// /方向
	for (int i = 0; i < 5; i++) {
		if (row - i >=0 && row-i+4<gradeSize &&
			col - i >=0 && col-i+4<gradeSize &&
			chessMap[row - i][col-i] == chessMap[row - i + 1][col-i+1] &&
			chessMap[row - i][col-i] == chessMap[row - i + 2][col-i+2] &&
			chessMap[row - i][col-i] == chessMap[row - i + 3][col-i+3] &&
			chessMap[row - i][col-i] == chessMap[row - i + 4][col-i+4]) {
			return true;
		}
	}
	// \方向
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}

	return false;
}
