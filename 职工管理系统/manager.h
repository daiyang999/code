#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
class Manager :public worker {
public:
	Manager(int id, string name, int did);
	virtual void showInfo();
	virtual string getDeptname();
};