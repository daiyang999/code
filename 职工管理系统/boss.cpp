#include"boss.h"
Boss::Boss(int id, string name, int did) {
	this->m_id = id;
	this->m_name = name;
	this->m_Deptid = did;
}
void Boss::showInfo() {
	cout << "�ϰ��ţ�" << this->m_id
		<< "\t�ϰ�������" << this->m_name
		<< "\t��λ��" << this->getDeptname()
		<< "\t��λְ�𣺹���˾��������" << endl;
}
string Boss::getDeptname() {
	return string("�ϰ�");
}