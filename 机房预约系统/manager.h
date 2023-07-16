#pragma once
#include<iostream>
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
#include<algorithm>
#include<string>
using namespace std;
class Manager :public Identity {
public:
	Manager();
	Manager(string name, string pwd);
	virtual void operMenu();
	void addPerson();
	void showPerson();
	void showComputer();
	void cleanFile();
	void initVector();
	bool checkRepeat(int id, int type);
	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
};