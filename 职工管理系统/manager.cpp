#include"manager.h"
Manager::Manager(int id, string name, int did) {
	this->m_id = id;
	this->m_name = name;
	this->m_Deptid = did;
}
void Manager::showInfo() {
	cout << "�����ţ�" << this->m_id
		<< "\t����������" << this->m_name
		<< "\t��λ��" << this->getDeptname()
		<< "\t��λְ������ϰ彻�������񣬲��·������Ա��" << endl;
}
string Manager::getDeptname() {
	return string("����");
}