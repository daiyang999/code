#include<iostream>
using namespace std;
class cube {
public:
	void setl(int a) {
		l = a;
	}
	void seth(int b) {
		h = b;
	}
	void setw(int c) {
		w = c;
	}
	int getl() {
		return l;
	}
	int geth() {
		return h;
	}
	int getw() {
		return w;
	}
	int mianji() {
		return 2 * l * h + 2 * l * w + 2 * h * w;
	}
	int tiji() {
		return h * w * l;
	}
	bool issamebyclass(cube& c1) {
		if (c1.getl() == l && c1.geth() == h && c1.getw() == w) {
			return true;
		}
		return false;
	}

private:
	int l;
	int h;
	int w;
};
bool issame(cube &c1, cube &c2) {
	if (c1.getl() == c2.getl() && c1.geth() == c2.geth() && c1.getw() == c2.getw()) {
		return true;
	}
	return false;
}
int main() {
	cube c;
	c.seth(10);
	c.setl(11);
	c.setw(12);
	cout << c.mianji() << endl;
	cout << c.tiji() << endl;
	cube c2;
	c2.seth(10);
	c2.setl(11);
	c2.setw(12);
	if (c.issamebyclass(c2)) {
		cout << "1" << endl;
	}
	else {
		cout << "0" << endl;
	}
	return 0; 
}