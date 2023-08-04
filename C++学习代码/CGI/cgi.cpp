#include<iostream>
using namespace std;
#include<Windows.h>
int main() {
	//创建管道
	HANDLE output[2];//管道两端的句柄
	//管道的属性
	SECURITY_ATTRIBUTES la;
	la.nLength = sizeof(la);
	la.bInheritHandle = true;
	la.lpSecurityDescriptor = 0;//默认值
	BOOL bCreate=CreatePipe(&output[0],&output[1],&la,0);
	if (bCreate == false) {
		MessageBox(0, "create cgi pipe error!", 0, 0);
		return 1;
	}

	//创建子进程
	char cmd[] = "ping www.baidu.com";
	//子进程启动属性
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.hStdOutput = output[1];
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi = { 0 };
	bCreate=CreateProcess(NULL, cmd, 0, 0, TRUE, 0, 0, 0, &si, &pi);
	if (bCreate == false) {
		cout << "进程创建失败！" << endl;
		return 1;
	}
	char buff[1024];
	DWORD size;
	while (1) {
		//cout << "请输入：" << endl;
		//gets_s(buff, sizeof(buff));
		//WriteFile(output[1], buff, strlen(buff) + 1, &size, NULL);
		//cout << "已经写入了" << size << "个字节" << endl;

		ReadFile(output[0], buff, sizeof(buff), &size, NULL);
		buff[size] = '\0';
		cout << "已经读到了" << size << "个字节:" <<buff<< endl;
	}
	return 0;
}