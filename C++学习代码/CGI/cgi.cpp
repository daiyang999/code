#include<iostream>
using namespace std;
#include<Windows.h>
int main() {
	//�����ܵ�
	HANDLE output[2];//�ܵ����˵ľ��
	//�ܵ�������
	SECURITY_ATTRIBUTES la;
	la.nLength = sizeof(la);
	la.bInheritHandle = true;
	la.lpSecurityDescriptor = 0;//Ĭ��ֵ
	BOOL bCreate=CreatePipe(&output[0],&output[1],&la,0);
	if (bCreate == false) {
		MessageBox(0, "create cgi pipe error!", 0, 0);
		return 1;
	}

	//�����ӽ���
	char cmd[] = "ping www.baidu.com";
	//�ӽ�����������
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.hStdOutput = output[1];
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi = { 0 };
	bCreate=CreateProcess(NULL, cmd, 0, 0, TRUE, 0, 0, 0, &si, &pi);
	if (bCreate == false) {
		cout << "���̴���ʧ�ܣ�" << endl;
		return 1;
	}
	char buff[1024];
	DWORD size;
	while (1) {
		//cout << "�����룺" << endl;
		//gets_s(buff, sizeof(buff));
		//WriteFile(output[1], buff, strlen(buff) + 1, &size, NULL);
		//cout << "�Ѿ�д����" << size << "���ֽ�" << endl;

		ReadFile(output[0], buff, sizeof(buff), &size, NULL);
		buff[size] = '\0';
		cout << "�Ѿ�������" << size << "���ֽ�:" <<buff<< endl;
	}
	return 0;
}