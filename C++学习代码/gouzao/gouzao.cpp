//#include<iostream>
//using namespace std;
//class person {
//public:
//	person() {
//		cout << "Ĭ�Ϲ��캯��" << endl;
//	}
//	person(int a,int h) {
//		age = a;
//		height = new int(h);
//		cout << "�вι��캯��" << endl;
//	}
//	person(const person& p) {
//		cout << "�������캯��" << endl;
//		age = p.age;
//		height = new int(*p.height);
//
//	}
//	~person()
//	{
//		if (height != NULL) {
//			delete height;
//			height = NULL;
//		}
//		cout << "��������" << endl;
//	}
//	int age;
//	int* height;
//};
//void test01() {
//	person p1(18,160);
//	cout << p1.age << "  "<<*p1.height<<endl;
//	person p2(p1);
//	cout << p2.age << "  " << *p2.height << endl;
//}
//int main() {
//	//person p1;
//	//person p2(10);
//	//person p3(p2);
//	//person p4 = 10;
//	test01();
//	return 0;
//}