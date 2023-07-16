#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<algorithm>
#include"speaker.h"
using namespace std;
//提供菜单界面与用户交互
//对演讲比赛流程进行控制
//与文件的读写进行交互
class SpeechManager {
public:
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeech();
	void createSpeaker();
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void showRecord();
	void clearRecord();

	~SpeechManager();
	
	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Speaker>m_Speaker;
	int m_Index;
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
};