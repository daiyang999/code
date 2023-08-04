//#include<iostream>
//using namespace std;
//class person {
//public:
//	person() {
//		cout << "默认构造函数" << endl;
//	}
//	person(int a,int h) {
//		age = a;
//		height = new int(h);
//		cout << "有参构造函数" << endl;
//	}
//	person(const person& p) {
//		cout << "拷贝构造函数" << endl;
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
//		cout << "析构函数" << endl;
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