#include<iostream>
#include<thread>
using namespace std;
void p(int left, int right) {
	for (int i = left; i <= right; i++) {
		cout << i << " ";
	}
	cout << endl;
}
int main() {
	thread t1(p, 1, 25);
	thread t2(p, 26, 50);
	thread t3(p, 51, 100);
	t1.join();
	t2.join();
	t3.join();
	return 0;
}