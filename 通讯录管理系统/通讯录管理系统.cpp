#include<iostream>
using namespace std;
#include<string>
#define MAX 1000
void showMenu() {
	cout << "********************" << endl;
	cout << "****1.�����ϵ��****" << endl;
	cout << "****2.��ʾ��ϵ��****" << endl;
	cout << "****3.ɾ����ϵ��****" << endl;
	cout << "****4.������ϵ��****" << endl;
	cout << "****5.�޸���ϵ��****" << endl;
	cout << "****6.�����ϵ��****" << endl;
	cout << "****0.�˳�ͨѶ¼****" << endl;
	cout << "********************" << endl;

}

struct person {
	string name;
	int age;
	string tele;
	int sex;
	string home;
};
struct address {
	struct person personarray[MAX];
	int size;
};
void addperson(struct address* abs) {
	if (abs->size == MAX) {
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else {
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personarray[abs->size].name = name;
		cout << "�������Ա�" << endl;
		cout << "1--�У�2--Ů" << endl;
		int sex = 0;
		
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[abs->size].sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}
		cout << "���������䣺" << endl;
		int age = 0;

		while (true) {
			cin >> age;
			if (age>0&&age<=100) {
				abs->personarray[abs->size].age = age;
				break;
			}
			cout << "�����������������룡" << endl;
		}
		cout << "��������ϵ�绰��" << endl;
		string tele;
		cin >> tele;
		abs->personarray[abs->size].tele = tele;

		cout << "�������ͥסַ��" << endl;
		string home;
		cin >> home;
		abs->personarray[abs->size].home = home;

		abs->size++;
		cout << "��ӳɹ���" << endl;
		system("pause");
		system("cls");//����
	}
}
void showperson(struct address* abs) {
	if (abs->size == 0) {
		cout << "��¼Ϊ�գ�" << endl;
		
	}
	else {
		for (int i = 0; i < abs->size; i++) {
			cout << "������" << abs->personarray[i].name << "\t";
			cout << "�Ա�" << (abs->personarray[i].sex==1?"��":"Ů") << "\t";
			cout << "���䣺" << abs->personarray[i].age << "\t";
			cout << "�绰��" << abs->personarray[i].tele << "\t";
			cout << "סַ��" << abs->personarray[i].home << endl;
			
		}
		
	}
	system("pause");
	system("cls");
}
int isexist(struct address* abs, string name) {
	for (int i = 0; i < abs->size; i++) {
		if (abs->personarray[i].name == name) {
			return i;
		}
	}
	return -1;
}
void deleteperson(struct address* abs) {
	cout << "��������Ҫɾ������ϵ��������" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		for (int i = flag; i < abs->size; i++) {
			abs->personarray[i] = abs->personarray[i + 1];
		}
		abs->size--;
		cout << "ɾ���ɹ���" << endl;
	}
	else {
		cout << "���޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}
void findperson(struct address* abs) {
	cout << "��������Ҫ���ҵ���ϵ��������" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		cout << "������" << abs->personarray[flag].name << "\t";
		cout << "�Ա�" << (abs->personarray[flag].sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << abs->personarray[flag].age << "\t";
		cout << "�绰��" << abs->personarray[flag].tele << "\t";
		cout << "סַ��" << abs->personarray[flag].home << endl;
		cout << "���ҳɹ���" << endl;
	}
	else {
		cout << "���޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}
void modifyperson(struct address* abs) {
	cout << "��������Ҫ�޸ĵ���ϵ��������" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		string name;
		cout << "����������:" << endl;
		cin >> name;
		abs->personarray[flag].name = name;
		cout << "�������Ա�:" << endl;
		cout << "1--�У�2--Ů" << endl;
		int sex = 0;

		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[flag].sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}
		cout << "���������䣺" << endl;
		int age = 0;

		while (true) {
			cin >> age;
			if (age > 0 && age <= 100) {
				abs->personarray[flag].age = age;
				break;
			}
			cout << "�����������������룡" << endl;
		}
		cout << "��������ϵ�绰��" << endl;
		string tele;
		cin >> tele;
		abs->personarray[flag].tele = tele;

		cout << "�������ͥסַ��" << endl;
		string home;
		cin >> home;
		abs->personarray[flag].home = home;

		cout << "�޸ĳɹ���" << endl;
	}
	else {
		cout << "���޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}
void cleanperson(struct address* abs) {
	abs->size = 0;
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}
int main() {
	int select = 0;
	address abs;
	abs.personarray[0] = { "����",22,"13800000000",1,"�й�"};
	abs.personarray[1] = { "����",25,"13800000001",2,"�ձ�" };
	abs.size = 2;

	while (true) {
		showMenu();
		cin >> select;
		switch (select) {
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			return 0;
			break;

		case 1://�����ϵ��
			addperson(&abs);
			break;

		case 2://��ʾ��ϵ��
			showperson(&abs);
			break;

		case 3://ɾ����ϵ��
			deleteperson(&abs);
			break;

		case 4://������ϵ��
			findperson(&abs);
			break;

		case 5://�޸���ϵ��
			modifyperson(&abs);
			break;

		case 6:
			cleanperson(&abs);
			break;

		default:
			cout << "�����������ţ�" << endl;
			system("pause");
			system("cls");
			break;

		}
	}
	


	return 0;

}