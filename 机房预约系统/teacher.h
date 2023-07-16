#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include"computerRoom.h"
#include"globalFile.h"
#include"orderFile.h"
#include<string>
#include<fstream>
#include<vector>
class Teacher :public Identity {
public:
	Teacher();
	Teacher(int empId, string name, string pwd);
	virtual void operMenu();
	void showAllOrder();
	void validOrder();
	int m_EmpId;
};