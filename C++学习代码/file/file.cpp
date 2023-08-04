#include<iostream>
using namespace std;
#include<fstream>
#include<string>
void test() {
	//ofstream ofs;
	//ofs.open("test.txt", ios::out);
	//ofs << "姓名：张三" << endl;
	//ofs << "学号：111" << endl;

	//ofs.close();
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	//char buf[1024] = { 0 };
	//while (ifs >> buf) {
	//	cout << buf << endl;
	//}

	//char buf[1024] = { 0 };
	//while (ifs.getline(buf, sizeof(buf))) {
	//	cout << buf << endl;
	//}

	//string buf;
	//while (getline(ifs, buf)) {
	//	cout << buf << endl;
	//}
	
	char c;
	while ((c = ifs.get()) != EOF) {
		cout << c;
	}
	ifs.close();
}
int main() {
	test();
	return 0;
}