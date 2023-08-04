//#include<iostream>
//using namespace std;
//class person {
//public:
//	//person operator+(person& p) {
//	//	person tmp;
//	//	tmp.a = this->a + p.a;
//	//	tmp.b = this->b + p.b;
//	//	return tmp;
//	//}
//	int a;
//	int b;
//};
//person operator+(person& p1, person& p2) {
//	person tmp;
//	tmp.a = p1.a + p2.a;
//	tmp.b = p1.b + p2.b;
//	return tmp;
//}
//void test() {
//	person p1;
//	p1.a = 10;
//	p1.b = 20;
//
//	person p2;
//	p2.a = 11;
//	p2.b = 22;
//
//	person p3 = p1 + p2;
//	cout << p3.a << endl;
//	cout << p3.b << endl;
//}
//
//int main() {
//	test();
//	return 0;
//}