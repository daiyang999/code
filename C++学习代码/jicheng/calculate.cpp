#include<iostream>
using namespace std;
class calculator {
public:
	int getresult(string op) {
		if (op == "+") {
			return num1 + num2;
		}
		else if (op == "-") {
			return num1 - num2;
		}
		else if (op == "*") {
			return num1 * num2;
		}
	}
	int num1;
	int num2;
};
void test() {
	calculator c;
	c.num1 = 10;
	c.num2 = 20;
	cout << c.getresult("*") << endl;
}
class acalculator {
public:
	virtual int getresult() {
		return 0;
	}
	int num1;
	int num2;
};
class add :public acalculator {
public:
	int getresult() {
		return num1+num2;
	}
};
class sub :public acalculator {
public:
	int getresult() {
		return num1 - num2;
	}
};
class multi :public acalculator {
public:
	int getresult() {
		return num1 * num2;
	}
};
void test2() {
	acalculator* abc = new add;
	abc->num1 = 10;
	abc->num2 = 20;
	cout << abc->getresult() << endl;
	delete abc;
	abc = new sub;
	abc->num1 = 5;
	abc->num2 = 6;
	cout << abc->getresult() << endl;
	delete abc;
}
int main() {
	test2();
	return 0;
}