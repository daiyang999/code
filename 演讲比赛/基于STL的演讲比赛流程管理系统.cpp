#include<iostream>
#include"speechManager.h"
#include<string>
#include<ctime>
using namespace std;
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
	//	cout << "ѡ�ֱ�ţ�" << it->first << " ������" << it->second.m_Name << " ������" << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "���������ѡ��:" << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			sm.exitSystem();
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			break;
		}
	}
	
	return 0;
}