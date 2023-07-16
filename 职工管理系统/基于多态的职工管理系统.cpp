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
	//work = new Employee(1, "张三", 1);
	//work->showInfo();
	//delete work;
	//work = new Manager(2, "李四", 2);
	//work->showInfo();
	//delete work;
	//work = new Boss(3, "王五", 3);
	//work->showInfo();
	//delete work;

	WorkerManager wm;
	int choice;
	while (true) {
		wm.Show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			wm.ExistSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示员工
			wm.Show_Emp();
			break;
		case 3://删除职工
		//{	int ret = wm.isExist(5);
		//	cout << ret << endl;
		//	break;
		//}
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://排序
			wm.Sort_Emp();
			break;
		case 7://清空文件
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}