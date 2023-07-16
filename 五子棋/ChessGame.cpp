#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

void ChessGame::play()
{
	chess->init();
	while (1) {
		man->go();//ÈË×ß
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
		ai->go();//AI×ß
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
