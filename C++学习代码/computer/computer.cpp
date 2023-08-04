#include<iostream>
using namespace std;
#include<string>;
class cpu {
public:
	virtual void calculate() = 0;
};
class videocard {
public:
	virtual void display() = 0;
};
class memory {
public:
	virtual void storage() = 0;
};
class computer {
public:
	computer(cpu* c, videocard* v, memory* m) {
		c1 = c;
		v1 = v;
		m1 = m;
	}
	void work() {
		c1->calculate();
		v1->display();
		m1->storage();
	}
	~computer() {
		if (c1 != NULL) {
			delete c1;
			c1 = NULL;
		}
		if (v1 != NULL) {
			delete v1;
			v1 = NULL;
		}
		if (m1 != NULL) {
			delete m1;
			m1 = NULL;
		}
	}
private:
	cpu* c1;
	videocard* v1;
	memory* m1;
};
class intelcpu :public cpu{
public:
	virtual void calculate() {
		cout << "intel��cpu��ʼ������" << endl;
	}
};
class intelvideocard :public videocard {
public:
	virtual void display() {
		cout << "intel��videocard��ʼ��ʾ��" << endl;
	}
};
class intelmemory :public memory {
public:
	virtual void storage() {
		cout << "intel��memory��ʼ�洢��" << endl;
	}
};
class Lenovocpu :public cpu{
public:
	virtual void calculate() {
		cout << "Lenovo��cpu��ʼ������" << endl;
	}
};
class Lenovovideocard :public videocard {
public:
	virtual void display() {
		cout << "Lenovo��videocard��ʼ��ʾ��" << endl;
	}
};
class Lenovomemory :public memory {
public:
	virtual void storage() {
		cout << "Lenovo��memory��ʼ�洢��" << endl;
	}
};
void test() {
	cpu* ic = new intelcpu;
	videocard* vc = new intelvideocard;
	memory* mc = new intelmemory;
	computer* computer1 = new computer(ic, vc, mc);
	computer1->work();
	delete computer1;

	computer* computer2 = new computer(new Lenovocpu, new Lenovovideocard, new Lenovomemory);
	computer2->work();
	delete computer2;
}
int main() {
	test();
	return 0;
}