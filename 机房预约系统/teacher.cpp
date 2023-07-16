#include"teacher.h"
Teacher::Teacher() {

}
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}
void Teacher::operMenu() {
	cout << "欢迎教师" << this->m_Name << "登录！" << endl;
	cout << "1、查看所有预约" << endl;
	cout << "2、审核预约" << endl;
	cout << "0、注销登录" << endl;
	cout << "请选择你想要的操作：" << endl;
}
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			cout << "第 " << i + 1 << " 条信息：";
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
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << " 待审核的预约记录如下：" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (true) {
			if (of.m_orderData[i]["status"] == "1") {
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << " 预约的时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "  机房号：" << of.m_orderData[i]["roomId"];
				cout << " 预约人：" << of.m_orderData[i]["stuName"];
				cout << " 预约人学号：" << of.m_orderData[i]["stuId"];
				cout << " 状态：审核中" << endl;
			}
		}
	}
	cout << "请输入想要审核的记录编号,0代表返回" << endl;
	int select;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "请输入审核结果：" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else {
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}

		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}