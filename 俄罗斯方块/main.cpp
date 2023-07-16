#include<iostream>
using namespace std;
//Block 表示方块
//Tetris 表示游戏
#include"Tetris.h"
int main() {
	Tetris game(20,10,263,133,36);
	game.play();
	return 0;
}