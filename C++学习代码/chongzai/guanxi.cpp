#include<iostream>
using namespace std;
#include<string>
class person {
public:
	person(string name, int age) {
		mage = age;
		mname = name;
	}
	bool operator==(person& p) {
		if (this->mname == p.mname && this->mage == p.mage) {
			return true;
		}
		else {
			return false;
		}
	}
	string mname;
	int mage;
};
void test() {
	person p1("张三",10);
	person p2("张三", 10);
	if (p1 == p2) {
		cout << 1 << endl;
	}
	else {
		cout << 0 << endl;
	}
}
int main() {
	test();
	return 0;
}