#include<iostream>
using namespace std;
//int* func() {
//	int* p = new int(10);
//	return p;
//}
//void test(const int &a) {
//	a = 10;
//	
//}
int func(int a, int b=20, int c) {
	return a + b + c;
}
int main() {
	//int* p = func();
	//cout << *p << endl;
	//cout << p << endl;
	//delete p;
	//cout << *p << endl;
	//int a = 10;
	//int& b = a;
	//int b = 20;
	//test(b);
	cout << func(10,10,20) << endl;
	return 0;
}