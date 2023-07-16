#include"workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}
	int num = this->get_EmpNum();
	cout << "职工的人数为：" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new worker * [this->m_EmpNum];
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << this->m_EmpArray[i]->m_id << " " << this->m_EmpArray[i]->m_name << " " << this->m_EmpArray[i]->m_Deptid << endl;
	//}
	
}
void WorkerManager::Show_Menu() {
	cout << "**********************************" << endl;
	cout << "******欢迎使用职工管理系统!*******" << endl;
	cout << "********* 0.退出管理程序 *********" << endl;
	cout << "********* 1.增加职工信息 *********" << endl;
	cout << "********* 2.显示职工信息 *********" << endl;
	cout << "********* 3.删除离职职工 *********" << endl;
	cout << "********* 4.修改职工信息 *********" << endl;
	cout << "********* 5.查找职工信息 *********" << endl;
	cout << "********* 6.按照编号排序 *********" << endl;
	cout << "********* 7.清空所有文档 *********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
void WorkerManager::ExistSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		worker** newSpace=new worker* [newSize];
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dselect;
			cout << "请输入第" << i + 1 << "个员工的编号:" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个员工的姓名:" << endl;
			cin >> name;
			cout << "请选择该员工的岗位:" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;

			worker* work = NULL;
			switch (dselect) {
			case 1:
				work = new Employee(id, name, 1);
				break;
			case 2:
				work = new Manager(id, name, 2);
				break;
			case 3:
				work = new Boss(id, name, 3);
				break;
			default:
				cout << "添加失败！" << endl;
				break;
			}
			newSpace[this->m_EmpNum + i] = work;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->save();
		this->m_fileisempty = false;
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else {
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_Deptid << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	return num;
}
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		worker* work = NULL;
		if (did == 1) {
			work = new Employee(id, name, did);
		}
		else if (did == 2) {
			work = new Manager(id, name, did);
		}
		else {
			work = new Boss(id, name, did);
		}
		this->m_EmpArray[index++] = work;
	}
	ifs.close();
}
void WorkerManager::Show_Emp() {
	if (this->m_fileisempty) {
		cout << "文件不存在或记录为空！" << endl;
		
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Del_Emp() {
	if (this->m_fileisempty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		if (this->isExist(id) != -1) {
			cout << "找到该员工！" << endl;
			for (int i = this->isExist(id); i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_id == id) {
			index = i;
			break;
		}
	}
	return index;
}
void WorkerManager::Mod_Emp() {
	if (this->m_fileisempty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入想要修改的职工编号：" << endl;
		int id = 0;
		cin >> id;
		if (this->isExist(id) != -1) {
			cout << "找到该员工！" << endl;
			delete this->m_EmpArray[this->isExist(id)];
			int newid = 0;
			string newname = "";
			int dselect = 0;
			cout << "请输入新的职工号:" << endl;
			cin >> newid;
			cout << "请输入新的姓名：" << endl;
			cin >> newname;
			cout << "请输入新的岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;

			worker* work = NULL;
			switch (dselect) {
			case 1:
				work = new Employee(newid, newname, dselect);
			case 2:
				work = new Manager(newid, newname, dselect);
			case 3:
				work = new Boss(newid, newname, dselect);
			default:
				break;
			}
			this->m_EmpArray[this->isExist(id)] = work;
			this->save();
			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败，未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp() {
	if (this->m_fileisempty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入想要查找的方式：" << endl;
		cout << "1、按照职工的编号查找" << endl;
		cout << "2、按照职工的姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入需要查找的编号：" << endl;
			cin >> id;
			int ret = isExist(id);
			if (ret != -1) {
				cout << "找到职工！该职工的信息如下:" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_name == name) {
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_id
						<< "的职工的信息如下：" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else {
			cout << "输入选项有误！" << endl;
		}
		
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp() {
	if (this->m_fileisempty) {
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请输入排序的方式：" << endl;
		cout << "1、按照职工号进行升序" << endl;
		cout << "2、按照职工号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++) {
			int minormax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EmpArray[minormax]->m_id > this->m_EmpArray[j]->m_id) {
						minormax = j;
					}
				}
				else {
					if (this->m_EmpArray[minormax]->m_id < this->m_EmpArray[j]->m_id) {
						minormax = j;
					}
				}
			}
			if (i != minormax) {
				worker* tmp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = tmp;
			}
			
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}
void WorkerManager::Clean_File() {
	cout << "确认清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_fileisempty = true;
		}
		cout << "清空成功！" << endl;
		system("pause");
		system("cls");
	}

}
WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}