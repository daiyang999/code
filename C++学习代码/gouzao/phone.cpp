#include<iostream>
#include<string>
using namespace std;
class person {
public:
	person(int age) {
		this->age = age;
	}
	person add(person& p) {
		this->age += p.age;
		return *this;
	}
	int age;
};
void test() {
	person p(18);
	cout << p.age << endl;
	person p2(15);
	p2.add(p).add(p).add(p).add(p).add(p).add(p);
	cout << p2.age << endl;
}
int main() {
	test();
	
	return 0;
}