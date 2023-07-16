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
	cout << "机房的数量为：" << vCom.size() << endl;
}
void Manager::operMenu() {
	cout << "欢迎管理员" << this->m_Name << "登录！" << endl;
	cout << "1、添加账号" << endl;
	cout << "2、查看账号" << endl;
	cout << "3、查看机房" << endl;
	cout << "4、清空预约" << endl;
	cout << "0、注销登录" << endl;
	cout << "请选择你想要的操作：" << endl;
}
void Manager::addPerson() {
	cout << "请输入添加账号的类型：" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	string fileName;
	string tip;
	string errortip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学生的 学号：";
		errortip = "学生学号重复！请重新输入！";
	}
	else {
		fileName = TEACHER_FILE;
		tip = "请输入老师的职工号：";
		errortip = "老师职工号重复！请重新输入！";
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
	
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	ofs << endl<<id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}
void printstudent(Student& s) {
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printreacher(Teacher& t) {
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}
void Manager::showPerson() {
	cout << "请选择查看内容：" << endl;
	cout << "1、学生" << endl;
	cout << "2、老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "所有的学生的信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printstudent);
	}
	else {
		cout << "所有的学生的信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printreacher);
	}
	system("pause");
	system("cls");
}
void Manager::showComputer() {
	cout << "机房的信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
		cout << "机房的编号：" << it->m_ComId << " 机房的最大容量" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector() {
	vStu.clear();
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败！" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败！" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前老师数量为：" << vTea.size() << endl;
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