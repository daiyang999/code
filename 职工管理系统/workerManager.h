#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"
class WorkerManager {
public:
	WorkerManager();

	void Show_Menu();
	void ExistSystem();
	int m_EmpNum;
	worker** m_EmpArray;
	
	void Add_Emp();
	void save();
	bool m_fileisempty;
	int get_EmpNum();
	void init_Emp();
	void Show_Emp();
	void Del_Emp();
	int isExist(int id);
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void Clean_File();
	

	~WorkerManager();
};