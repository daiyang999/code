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
	cout << "欢迎学生" << this->m_Name << "登录！" << endl;
	cout << "1、申请预约" << endl;
	cout << "2、查看预约" << endl;
	cout << "3、查看所有预约" << endl;
	cout << "4、取消预约" << endl;
	cout << "0、注销登录" << endl;
	cout << "请选择你想要的操作：" << endl;
}
void Student::applyOrder() {
	cout << "机房开放时间为周一~周五，请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int date = 0;
	int interval=0;
	int room=0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "输入有误，请重新输入!" << endl;
	}
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "请选择机房：" << endl;
	for (int i = 0; i < vCom.size(); i++) {
		cout << vCom[i].m_ComId << "号机房的容量为" << vCom[i].m_MaxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "输入有误，请重新改输入！" << endl;
	}
	cout << "预约成功，审核中！" << endl;
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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"]=="1"?"上午":"下午");
			cout << "  机房号：" << of.m_orderData[i]["roomId"];
			string status = "状态";//1 审核中 2已预约 -1预约失败 0取消预约
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "预约成功！";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "预约失败，审核未通过！";
			}
			else if (of.m_orderData[i]["status"] == "0") {
				status += "预约已取消！";
			}
			cout << " 预约状态：" << status << endl;
		}
		cout << endl;
	}
	system("pause");
	system("cls");
}
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			cout <<"第 "<< i + 1 << " 条信息：";
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			cout << " 预约人：" << of.m_orderData[i]["stuName"];
			cout << " 预约人学号：" << of.m_orderData[i]["stuId"];
			string status = " 状态：";//1 审核中 2已预约 -1预约失败 0取消预约
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "预约成功！";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "预约失败，审核未通过！";
			}
			else if (of.m_orderData[i]["status"] == "0") {
				status += "预约已取消！";
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
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << " 审核中或预约成功的记录可以取消预约，请输入想要取消的记录" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout<<" 预约的时间段："<< (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "  机房号：" << of.m_orderData[i]["roomId"];
				string status = " 状态：";//1 审核中 2已预约 -1预约失败 0取消预约
				if (of.m_orderData[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "预约成功！";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录编号,0代表返回" << endl;
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
				cout << "已取消成功！" << endl;
				break;
			}

		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}