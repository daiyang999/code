#pragma once
#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
class Boss :public worker {
public:
	Boss(int id, string name, int did);
	virtual void showInfo();
	virtual string getDeptname();
};