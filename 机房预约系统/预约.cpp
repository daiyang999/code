#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include"Identity.h"
#include"student.h"
#include"manager.h"
#include"teacher.h"
#include"globalFile.h"
void teacherMenu(Identity*& teacher) {
	while (true) {
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "查看所有预约" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) {
			cout << "审核预约" << endl;
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void studentMenu(Identity*& student) {
	while (true) {
		student->operMenu();
		Student* stu = (Student*)student;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "申请预约" << endl;
			stu->applyOrder();
		}
		else if (select == 2) {
			cout << "查看预约" << endl;
			stu->showMyOrder();
		}
		else if (select == 3) {
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) {
			cout << "取消预约" << endl;
			stu->cancelOrder();
		}
		else {
			delete student;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void managerMenu(Identity*& manager) {
	while (true) {
		manager->operMenu();
		Manager* man = (Manager*)manager;
		int select;
		cin >> select;
		if (select == 1) {
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) {
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) {
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) {
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void LoginIn(string fileName, int type) {
	Identity* person = NULL;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		ifs.close(); 
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1) {
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入你的用户名：" << endl;
	cin >> name;
	cout << "请输入你的密码：" << endl;
	cin >> pwd;
	if (type == 1) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			/*cout << fId << endl;
			cout << fName << endl;
			cout << fPwd << endl;
			cout << endl;*/
			if (fName == name && fId == id && fPwd == pwd) {
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			/*cout << fId << endl;
			cout << fName << endl;
			cout << fPwd << endl;
			cout << endl;*/
			if (fName == name && fId == id && fPwd == pwd) {
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if(type==3){
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			/*cout << fId << endl;
			cout << fName << endl;
			cout << fPwd << endl;
			cout << endl;*/
			if (fName == name && fPwd == pwd) {
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}
int main() {
	
	int select = 0;
	while (true) {
		cout << "欢迎来到机房预约系统！" << endl;
		cout << "请输入您的身份：" << endl;
		cout << "1、学生" << endl;
		cout << "2、老师" << endl;
		cout << "3、管理员" << endl;
		cout << "0、退出" << endl;
		cout << "请输入你的选择：" << endl;
		cin >> select;
		switch (select) {
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		case 0:
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		}
	}
	return 0;
}