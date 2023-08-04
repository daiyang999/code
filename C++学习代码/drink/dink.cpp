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
		cout << "ÖóË®" << endl;
	}
	virtual void brew() {
		cout << "³åÅÝ¿§·È" << endl;
	}
	virtual void pour() {
		cout << "µ¹Èë±­ÖÐ" << endl;
	}
	virtual void put() {
		cout << "¼ÓÈëÅ£ÄÌºÍÌÇ" << endl;
	}
};
class tea :public drinking {
public:
	virtual void boil() {
		cout << "Öó²èË®" << endl;
	}
	virtual void brew() {
		cout << "³åÅÝ²èÒ¶" << endl;
	}
	virtual void pour() {
		cout << "µ¹Èë±­ÖÐ" << endl;
	}
	virtual void put() {
		cout << "¼ÓÈëÄûÃÊ" << endl;
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