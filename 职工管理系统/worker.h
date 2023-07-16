#pragma once
#include<iostream>
#include<string>
using namespace std;
class worker {
public:
	virtual void showInfo() = 0;
	virtual string getDeptname() = 0;
public:
	int m_id;
	string m_name;
	int m_Deptid;
};