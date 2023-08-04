#include<iostream>
using namespace std;
#include<string>
//#include"swap.h"
//void swap(int *a, int *b) {
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
struct student {
	string name;
	int age;
	int score;
};
struct teacher {
	int id;
	string name;
	int age;
	student s[10];
};
void x(const student* p) {
	p->name = "´÷Ñô´÷Ñô";
}

int main() {
	//int arr[5] = { 1,2,3,4,5 };
	//cout << sizeof(arr)/sizeof(arr[0]) << endl;
	//cout << (int)arr << endl;
	//cout << (int)&arr[1] << endl;
	//system("pause");
	//int a = 10;
	//int b = 20;
	//swap(&a, &b);
	//cout << a << endl;
	//cout << b << endl;
	student s[10];
	s[0].name = "´÷Ñô";
	s[0].age = 23;
	s[0].score = 80;
	cout << s[0].name << s[0].age << s[0].score << endl;
	teacher t1;
	t1.name = "ÀÏÍõ";
	t1.age = 50;
	t1.id = 123;
	t1.s[0].age = 222;
	x(&s[0]);
	cout << s[0].name << t1.s[0].age << s[0].score << endl;
	return 0;
}