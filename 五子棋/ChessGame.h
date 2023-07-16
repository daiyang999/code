#pragma once
#include"Man.h"
#include"Chess.h"
#include"AI.h"
class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();//开始对局

//添加数据成员
private:
	Man* man;
	AI* ai;
	Chess* chess;
};

