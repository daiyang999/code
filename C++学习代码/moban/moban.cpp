#include<iostream>
using namespace std;
template<typename T>
void myswap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}
void test() {
	int a = 10;
	int b = 20;
	//myswap(a, b);
	myswap<int>(a, b);
	cout << a << " " << b << endl;
}
int main() {
	test();
	return 0;
}