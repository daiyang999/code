#pragma once
#include<graphics.h>
#include<vector>
#include<mmsystem.h>
#include<math.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
//��ʾ���ӵ�λ��
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0,int c=0):row(r),col(c){}
};

typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//��ȡ���̴�С
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//�������Ƿ����

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;//���̴�С
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;//���ӵĴ�С
	vector<vector<int>> chessMap;//�洢��ǰ��ֵ����ӷֲ���0���հ� 1������ -1������
	bool playerFlag;//true�������� false��������

	void updateGameMap(ChessPos* pos);
	bool checkWin();//����Ƿ�ʤ��
	ChessPos lastPos;//������ӵ��λ��
};

