//#include<iostream>
//using namespace std;
//class myin {
//	friend ostream& operator<<(ostream& cout, myin myint);
//public:
//	myin() {
//		num = 0;
//	}
//	//����ǰ��++
//	myin& operator++() {
//		num++;
//		return *this;
//	}
//
//	//���غ���++
//	myin operator++(int) {
//		myin tmp = *this;
//		num++;
//		return tmp;
//	}
//
//private:
//	int num;
//};
//ostream& operator<<(ostream& cout, myin myint) {
//	cout << myint.num;
//	return cout;
//}
//void test() {
//	myin myint;
//	cout << ++(++myint) << endl;
//	cout << myint++ << endl;
//	cout << myint++ << endl;
//}
//int main() {
//	test();
//	return 0;
//}