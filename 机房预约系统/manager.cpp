#include"manager.h"
Manager::Manager() {

}
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
	cout << "����������Ϊ��" << vCom.size() << endl;
}
void Manager::operMenu() {
	cout << "��ӭ����Ա" << this->m_Name << "��¼��" << endl;
	cout << "1������˺�" << endl;
	cout << "2���鿴�˺�" << endl;
	cout << "3���鿴����" << endl;
	cout << "4�����ԤԼ" << endl;
	cout << "0��ע����¼" << endl;
	cout << "��ѡ������Ҫ�Ĳ�����" << endl;
}
void Manager::addPerson() {
	cout << "����������˺ŵ����ͣ�" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;
	string fileName;
	string tip;
	string errortip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "������ѧ���� ѧ�ţ�";
		errortip = "ѧ��ѧ���ظ������������룡";
	}
	else {
		fileName = TEACHER_FILE;
		tip = "��������ʦ��ְ���ţ�";
		errortip = "��ʦְ�����ظ������������룡";
	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret=checkRepeat(id, select);
		if (ret) {
			cout << errortip << endl;
		}
		else {
			break;
		}
	}
	
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	ofs << endl<<id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}
void printstudent(Student& s) {
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}
void printreacher(Teacher& t) {
	cout << "ְ���ţ�" << t.m_EmpId << " ������" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}
void Manager::showPerson() {
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1��ѧ��" << endl;
	cout << "2����ʦ" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "���е�ѧ������Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printstudent);
	}
	else {
		cout << "���е�ѧ������Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printreacher);
	}
	system("pause");
	system("cls");
}
void Manager::showComputer() {
	cout << "��������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
		cout << "�����ı�ţ�" << it->m_ComId << " �������������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector() {
	vStu.clear();
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();
}
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (it->m_Id == id) {
				return true;
			}
		}
	}
	else {
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (it->m_EmpId == id) {
				return true;
			}
		}
	}
	return false;
}