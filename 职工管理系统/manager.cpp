#include"manager.h"
Manager::Manager(int id, string name, int did) {
	this->m_id = id;
	this->m_name = name;
	this->m_Deptid = did;
}
void Manager::showInfo() {
	cout << "经理编号：" << this->m_id
		<< "\t经理姓名：" << this->m_name
		<< "\t岗位：" << this->getDeptname()
		<< "\t岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}
string Manager::getDeptname() {
	return string("经理");
}