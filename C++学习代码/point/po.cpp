#include<iostream>
using namespace std;
#include<math.h>
#include"circle.h"
#include"point.h"
//class point {
//public:
//	void setx(int x) {
//		px = x;
//	}
//	int getx() {
//		return px;
//	}
//	void sety(int y) {
//		py = y;
//	}
//	int gety() {
//		return py;
//	}
//
//private:
//	int px;
//	int py;
//};
//class circle {
//public:
//	void setcenter(point center1) {
//		center=center1;
//	}
//	point getcenter() {
//		return center;
//	}
//	void setr(int r1) {
//		r = r1;
//	}
//	int getr() {
//		return r;
//	}
//
//private:
//	point center;
//	int r;
//
//};
void isincircle(circle& c, point& p) {
	int distance = (c.getcenter().getx() - p.getx()) * (c.getcenter().getx() - p.getx()) +
		(c.getcenter().gety() - p.gety()) * (c.getcenter().gety() - p.gety());
	if (distance == c.getr() * c.getr()) {
		cout << "点在圆上" << endl;
	}
	else if (distance < c.getr() * c.getr()) {
		cout << "点在圆内" << endl;
	}
	else {
		cout << "点在圆外" << endl;
	}
		
}
int main() {
	circle c;
	point center;
	c.setr(10);
	center.setx(10);
	center.sety(0);
	c.setcenter(center);
	point p;
	p.setx(10);
	p.sety(1);
	isincircle(c, p);
	return 0;
}