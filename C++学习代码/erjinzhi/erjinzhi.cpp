#include<iostream>
using namespace std;
#include<string>
#include<fstream>
class person {
public:
	char name[64];
	int age;
};
void test() {
	ofstream ofs;
	ofs.open("person.txt", ios::out | ios::binary);
	person p = { "张三",18 };
	ofs.write((const char*)&p, sizeof(person));

	ofs.close();
}
void test1() {
	ifstream ifs;
	ifs.open("person.txt", ios::in | ios::binary);
	if (!ifs.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	person p;
	ifs.read((char*)&p, sizeof(person));
	cout << p.name << " " << p.age << endl;
	ifs.close();
}
int main() {
	//test();
	test1();
	return 0;
}