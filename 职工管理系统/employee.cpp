#include"employee.h"
Employee::Employee(int id, string name, int did) {
	this->m_id = id;
	this->m_name = name;
	this->m_Deptid = did;
}
void Employee::showInfo() {
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDeptname()
		<< "\t��λְ����ɾ�����������" << endl;
}
string Employee::getDeptname() {
	return string("Ա��");
}