#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
struct Point {
	int col;
	int row;
};
class Block
{
public:
	Block();
	void drop();
	void moveLeftRight(int offset);
	void rotate();//旋转
	void draw(int leftMargin,int topMargin);
	static IMAGE** getImages();
	Block& operator=(const Block& other);
	bool blockInMap(const vector<vector<int>>&map);
	void solidify( vector<vector<int>>& map);
	int getBlockType();

private:
	int blockType;//方块类型
	Point smallBlocks[4];
	IMAGE *img;

	static IMAGE* imgs[7];
	static int size;
};

