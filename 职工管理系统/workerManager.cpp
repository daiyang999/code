#include"workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ������ڣ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}
	int num = this->get_EmpNum();
	cout << "ְ��������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new worker * [this->m_EmpNum];
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << this->m_EmpArray[i]->m_id << " " << this->m_EmpArray[i]->m_name << " " << this->m_EmpArray[i]->m_Deptid << endl;
	//}
	
}
void WorkerManager::Show_Menu() {
	cout << "**********************************" << endl;
	cout << "******��ӭʹ��ְ������ϵͳ!*******" << endl;
	cout << "********* 0.�˳�������� *********" << endl;
	cout << "********* 1.����ְ����Ϣ *********" << endl;
	cout << "********* 2.��ʾְ����Ϣ *********" << endl;
	cout << "********* 3.ɾ����ְְ�� *********" << endl;
	cout << "********* 4.�޸�ְ����Ϣ *********" << endl;
	cout << "********* 5.����ְ����Ϣ *********" << endl;
	cout << "********* 6.���ձ������ *********" << endl;
	cout << "********* 7.��������ĵ� *********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
void WorkerManager::ExistSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp() {
	cout << "���������ְ����������" << endl;
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
			cout << "�������" << i + 1 << "��Ա���ı��:" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��Ա��������:" << endl;
			cin >> name;
			cout << "��ѡ���Ա���ĸ�λ:" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
				cout << "���ʧ�ܣ�" << endl;
				break;
			}
			newSpace[this->m_EmpNum + i] = work;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->save();
		this->m_fileisempty = false;
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else {
		cout << "��������" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		if (this->isExist(id) != -1) {
			cout << "�ҵ���Ա����" << endl;
			for (int i = this->isExist(id); i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		if (this->isExist(id) != -1) {
			cout << "�ҵ���Ա����" << endl;
			delete this->m_EmpArray[this->isExist(id)];
			int newid = 0;
			string newname = "";
			int dselect = 0;
			cout << "�������µ�ְ����:" << endl;
			cin >> newid;
			cout << "�������µ�������" << endl;
			cin >> newname;
			cout << "�������µĸ�λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			cout << "�޸ĳɹ���" << endl;
		}
		else {
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp() {
	if (this->m_fileisempty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫ���ҵķ�ʽ��" << endl;
		cout << "1������ְ���ı�Ų���" << endl;
		cout << "2������ְ������������" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������Ҫ���ҵı�ţ�" << endl;
			cin >> id;
			int ret = isExist(id);
			if (ret != -1) {
				cout << "�ҵ�ְ������ְ������Ϣ����:" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_name == name) {
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_id
						<< "��ְ������Ϣ���£�" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
		
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp() {
	if (this->m_fileisempty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "����������ķ�ʽ��" << endl;
		cout << "1������ְ���Ž�������" << endl;
		cout << "2������ְ���Ž��н���" << endl;
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
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}
}
void WorkerManager::Clean_File() {
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
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
		cout << "��ճɹ���" << endl;
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