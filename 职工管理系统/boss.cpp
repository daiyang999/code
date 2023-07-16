#include"boss.h"
Boss::Boss(int id, string name, int did) {
	this->m_id = id;
	this->m_name = name;
	this->m_Deptid = did;
}
void Boss::showInfo() {
	cout << "老板编号：" << this->m_id
		<< "\t老板姓名：" << this->m_name
		<< "\t岗位：" << this->getDeptname()
		<< "\t岗位职责：管理公司所有事务" << endl;
}
string Boss::getDeptname() {
	return string("老板");
}