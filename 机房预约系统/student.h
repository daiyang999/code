#pragma once
#include<iostream>
#include"Identity.h"
#include"computerRoom.h"
#include"globalFile.h"
#include"orderFile.h"
using namespace std;
#include<string>
#include<fstream>
#include<vector>
class Student :public Identity {
public:
	Student();
	Student(int id, string name, string pwd);
	virtual void operMenu();
	void applyOrder();
	void showMyOrder();
	void showAllOrder();
	void cancelOrder();
	int m_Id;
	vector<ComputerRoom> vCom;
};