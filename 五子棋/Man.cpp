#include "Man.h"
using namespace std;
void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	//获取鼠标点击信息
	
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	cout << pos.row << " " << pos.col << endl;
	//落子
	chess->chessDown(&pos, CHESS_BLACK);
}
