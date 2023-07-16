#include"teacher.h"
Teacher::Teacher() {

}
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}
void Teacher::operMenu() {
	cout << "��ӭ��ʦ" << this->m_Name << "��¼��" << endl;
	cout << "1���鿴����ԤԼ" << endl;
	cout << "2�����ԤԼ" << endl;
	cout << "0��ע����¼" << endl;
	cout << "��ѡ������Ҫ�Ĳ�����" << endl;
}
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			cout << "�� " << i + 1 << " ����Ϣ��";
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
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << " ����˵�ԤԼ��¼���£�" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			if (of.m_orderData[i]["status"] == "1") {
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ԤԼ��ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << "  �����ţ�" << of.m_orderData[i]["roomId"];
				cout << " ԤԼ�ˣ�" << of.m_orderData[i]["stuName"];
				cout << " ԤԼ��ѧ�ţ�" << of.m_orderData[i]["stuId"];
				cout << " ״̬�������" << endl;
			}
		}
	}
	cout << "��������Ҫ��˵ļ�¼���,0������" << endl;
	int select;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "��������˽����" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else {
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "�����ϣ�" << endl;
				break;
			}

		}
		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");
}