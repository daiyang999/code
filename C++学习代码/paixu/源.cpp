#include<iostream>
using namespace std;
#include<vector>
void quicksort(vector<int>& a, int low, int high) {
	if (low >= high)return;
	int left = low;
	int right = high;
	int key = a[left];
	while (left < right) {
		while (left<right && a[right]>key) {
			right--;
		}
		if (left < right) {
			a[left] = a[right];
			left++;
		}
		while(left<right&&a[left]<=key){
			left++;
		}
		if (left < right) {
			a[right] = a[left];
			right--;
		}
		a[left] = key;
		quicksort(a, low, left - 1);
		quicksort(a, right + 1, high);
	}
}
int main() {
	vector<int> a;
	a.push_back(5);
	a.push_back(1);
	a.push_back(6);
	a.push_back(2);
	a.push_back(3);
	quicksort(a, 0, a.size() - 1);
	for (int i : a) {
		cout << i << " ";
	}
	return 0;
}