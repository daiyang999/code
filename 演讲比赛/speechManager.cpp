#include"speechManager.h"
SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
void SpeechManager::show_Menu() {
	cout << "***************************" << endl;
	cout << "*****��ӭ�μ��ݽ�����******" << endl;
	cout << "*****1����ʼ�ݽ�����*******" << endl;
	cout << "*****2���鿴�����¼*******" << endl;
	cout << "*****3����ձ�����¼*******" << endl;
	cout << "*****0���˳���������*******" << endl;
	cout << "***************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::startSpeech() {
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->m_Index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->saveRecord();
	cout << "���������ϣ�" << endl;
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw() {
	cout << "�ڡ�" << this->m_Index << "���ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "��ǩ����ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::speechContest() {
	cout << "�ڡ�" << this->m_Index << "���ֱ�����ʽ��ʼ��" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;
	vector<int> v_Src;//����ѡ�ֵ�����
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		deque<double> d;
		num++;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С�������������:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���"
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1]<<endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "�ڡ�" << this->m_Index << "���ֱ���������" << endl;
	system("pause");
}
void SpeechManager::showScore() {
	cout << "�ڡ�" << this->m_Index << "���ֱ�������ѡ����Ϣ���£�" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout<<"ѡ�ֱ�ţ�"<<*it<<" ѡ��������"<<this->m_Speaker[*it].m_Name<<" �÷֣�"
		<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//׷�ӵķ�ʽд�ļ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ����棡" << endl;
	this->fileIsEmpty = false;
}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			//cout << tmp << endl;
			v.push_back(tmp);
			
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
		
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << it->first << "�ھ���ţ�" << it->second[0] << "�ھ��÷֣�" << it->second[1] << endl;
	}*/
}
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "��" << i + 1 << "������Ĺھ�����ǣ�" << m_Record[i][0]
				<< "�ھ��÷��ǣ�" << m_Record[i][1]
				<< "�Ǿ���ţ�" << m_Record[i][2]
				<< "�Ǿ��÷��ǣ�" << m_Record[i][3]
				<< "��������ǣ�" << m_Record[i][4]
				<< "�����÷��ǣ�" << m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord() {
	cout << "ȷ��Ҫɾ����" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}