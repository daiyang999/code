#include<iostream>
using namespace std;
class drinking {
public:
	virtual void boil() = 0;
	virtual void brew() = 0;
	virtual void pour() = 0;
	virtual void put() = 0;
	void makedrink() {
		boil();
		brew();
		pour();
		put();
	}
};
class coffee :public drinking{
public:
	virtual void boil() {
		cout << "��ˮ" << endl;
	}
	virtual void brew() {
		cout << "���ݿ���" << endl;
	}
	virtual void pour() {
		cout << "���뱭��" << endl;
	}
	virtual void put() {
		cout << "����ţ�̺���" << endl;
	}
};
class tea :public drinking {
public:
	virtual void boil() {
		cout << "���ˮ" << endl;
	}
	virtual void brew() {
		cout << "���ݲ�Ҷ" << endl;
	}
	virtual void pour() {
		cout << "���뱭��" << endl;
	}
	virtual void put() {
		cout << "��������" << endl;
	}
};
void work(drinking *abs) {
	abs->makedrink();
	delete abs;
}
void test() {
	work(new coffee);
	cout << "----------------" << endl;
	work(new tea);
}
int main() {
	test();
	return 0;
}