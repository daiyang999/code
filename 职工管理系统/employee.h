#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"worker.h"
class Employee :public worker {
public:
	Employee(int id, string name, int did);
	virtual void showInfo();
	virtual string getDeptname();
};