//#include<iostream>
//using namespace std;
//class person {
//public:
//	person(int age) {
//		mage = new int(age);
//	}
//	~person() {
//		if (mage != NULL) {
//			delete mage;
//			mage = NULL;
//		}
//	}
//	person& operator=(person& p) {
//		if (mage != NULL) {
//			delete mage;
//			mage = NULL;
//		}
//		mage=new int(*p.mage);
//		return *this;
//	}
//	int* mage;
//};
//void test() {
//	person p1(20);
//	person p2(21);
//	person p3(30);
//	cout << *p1.mage << endl;
//	cout << *p2.mage << endl;
//	p3=p2 = p1;
//	cout << *p1.mage << endl;
//	cout << *p2.mage << endl;
//	cout << *p3.mage << endl;
//}
//int main() {
//	test();
//	return 0;
//}