#pragma once
#include"Man.h"
#include"Chess.h"
#include"AI.h"
class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();//��ʼ�Ծ�

//������ݳ�Ա
private:
	Man* man;
	AI* ai;
	Chess* chess;
};

