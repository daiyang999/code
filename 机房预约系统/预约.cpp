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
			cout << "�鿴����ԤԼ" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) {
			cout << "���ԤԼ" << endl;
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "ע���ɹ���" << endl;
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
			cout << "����ԤԼ" << endl;
			stu->applyOrder();
		}
		else if (select == 2) {
			cout << "�鿴ԤԼ" << endl;
			stu->showMyOrder();
		}
		else if (select == 3) {
			cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) {
			cout << "ȡ��ԤԼ" << endl;
			stu->cancelOrder();
		}
		else {
			delete student;
			cout << "ע���ɹ���" << endl;
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
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) {
			cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3) {
			cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) {
			cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "ע���ɹ���" << endl;
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
		cout << "�ļ������ڣ�" << endl;
		ifs.close(); 
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1) {
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}
	cout << "����������û�����" << endl;
	cin >> name;
	cout << "������������룺" << endl;
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
				cout << "ѧ����֤��¼�ɹ���" << endl;
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
				cout << "��ʦ��֤��¼�ɹ���" << endl;
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
				cout << "����Ա��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}
int main() {
	
	int select = 0;
	while (true) {
		cout << "��ӭ��������ԤԼϵͳ��" << endl;
		cout << "������������ݣ�" << endl;
		cout << "1��ѧ��" << endl;
		cout << "2����ʦ" << endl;
		cout << "3������Ա" << endl;
		cout << "0���˳�" << endl;
		cout << "���������ѡ��" << endl;
		cin >> select;
		switch (select) {
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
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