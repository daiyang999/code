#include"student.h"
Student::Student() {

}
Student::Student(int id, string name, string pwd) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
}
void Student::operMenu() {
	cout << "��ӭѧ��" << this->m_Name << "��¼��" << endl;
	cout << "1������ԤԼ" << endl;
	cout << "2���鿴ԤԼ" << endl;
	cout << "3���鿴����ԤԼ" << endl;
	cout << "4��ȡ��ԤԼ" << endl;
	cout << "0��ע����¼" << endl;
	cout << "��ѡ������Ҫ�Ĳ�����" << endl;
}
void Student::applyOrder() {
	cout << "��������ʱ��Ϊ��һ~���壬����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	int date = 0;
	int interval=0;
	int room=0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "������������������!" << endl;
	}
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "�����������������룡" << endl;
	}
	cout << "��ѡ�������" << endl;
	for (int i = 0; i < vCom.size(); i++) {
		cout << vCom[i].m_ComId << "�Ż���������Ϊ" << vCom[i].m_MaxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "�������������¸����룡" << endl;
	}
	cout << "ԤԼ�ɹ�������У�" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
	
}
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"]=="1"?"����":"����");
			cout << "  �����ţ�" << of.m_orderData[i]["roomId"];
			string status = "״̬";//1 ����� 2��ԤԼ -1ԤԼʧ�� 0ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "ԤԼ�ɹ���";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "ԤԼʧ�ܣ����δͨ����";
			}
			else if (of.m_orderData[i]["status"] == "0") {
				status += "ԤԼ��ȡ����";
			}
			cout << " ԤԼ״̬��" << status << endl;
		}
		cout << endl;
	}
	system("pause");
	system("cls");
}
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			cout <<"�� "<< i + 1 << " ����Ϣ��";
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " �����ţ�" << of.m_orderData[i]["roomId"];
			cout << " ԤԼ�ˣ�" << of.m_orderData[i]["stuName"];
			cout << " ԤԼ��ѧ�ţ�" << of.m_orderData[i]["stuId"];
			string status = " ״̬��";//1 ����� 2��ԤԼ -1ԤԼʧ�� 0ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "ԤԼ�ɹ���";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "ԤԼʧ�ܣ����δͨ����";
			}
			else if (of.m_orderData[i]["status"] == "0") {
				status += "ԤԼ��ȡ����";
			}
			cout << status << endl;
		}
		cout << endl;
	}
	system("pause");
	system("cls");
}
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << " ����л�ԤԼ�ɹ��ļ�¼����ȡ��ԤԼ����������Ҫȡ���ļ�¼" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout<<" ԤԼ��ʱ��Σ�"<< (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << "  �����ţ�" << of.m_orderData[i]["roomId"];
				string status = " ״̬��";//1 ����� 2��ԤԼ -1ԤԼʧ�� 0ȡ��ԤԼ
				if (of.m_orderData[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "ԤԼ�ɹ���";
				}
				cout << status << endl;
			}
		}
	}
	cout << "������ȡ���ļ�¼���,0������" << endl;
	int select;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "��ȡ���ɹ���" << endl;
				break;
			}

		}
		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");
}