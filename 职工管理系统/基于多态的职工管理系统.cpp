#include<iostream>
using namespace std;
#include<string>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
int main() {
	//worker* work = NULL;
	//work = new Employee(1, "����", 1);
	//work->showInfo();
	//delete work;
	//work = new Manager(2, "����", 2);
	//work->showInfo();
	//delete work;
	//work = new Boss(3, "����", 3);
	//work->showInfo();
	//delete work;

	WorkerManager wm;
	int choice;
	while (true) {
		wm.Show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			wm.ExistSystem();
			break;
		case 1://���ְ��
			wm.Add_Emp();
			break;
		case 2://��ʾԱ��
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
		//{	int ret = wm.isExist(5);
		//	cout << ret << endl;
		//	break;
		//}
			wm.Del_Emp();
			break;
		case 4://�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����
			wm.Sort_Emp();
			break;
		case 7://����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}