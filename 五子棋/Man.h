#pragma once
#include"Chess.h"
#include<iostream>
class Man
{
public:
	void init(Chess* chess);
	void go();

private:
	Chess* chess;
};

