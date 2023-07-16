#include<iostream>
using namespace std;
#include<string>
#define MAX 1000
void showMenu() {
	cout << "********************" << endl;
	cout << "****1.添加联系人****" << endl;
	cout << "****2.显示联系人****" << endl;
	cout << "****3.删除联系人****" << endl;
	cout << "****4.查找联系人****" << endl;
	cout << "****5.修改联系人****" << endl;
	cout << "****6.清空联系人****" << endl;
	cout << "****0.退出通讯录****" << endl;
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
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else {
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personarray[abs->size].name = name;
		cout << "请输入性别：" << endl;
		cout << "1--男，2--女" << endl;
		int sex = 0;
		
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[abs->size].sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		cout << "请输入年龄：" << endl;
		int age = 0;

		while (true) {
			cin >> age;
			if (age>0&&age<=100) {
				abs->personarray[abs->size].age = age;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		cout << "请输入联系电话：" << endl;
		string tele;
		cin >> tele;
		abs->personarray[abs->size].tele = tele;

		cout << "请输入家庭住址：" << endl;
		string home;
		cin >> home;
		abs->personarray[abs->size].home = home;

		abs->size++;
		cout << "添加成功！" << endl;
		system("pause");
		system("cls");//清屏
	}
}
void showperson(struct address* abs) {
	if (abs->size == 0) {
		cout << "记录为空！" << endl;
		
	}
	else {
		for (int i = 0; i < abs->size; i++) {
			cout << "姓名：" << abs->personarray[i].name << "\t";
			cout << "性别：" << (abs->personarray[i].sex==1?"男":"女") << "\t";
			cout << "年龄：" << abs->personarray[i].age << "\t";
			cout << "电话：" << abs->personarray[i].tele << "\t";
			cout << "住址：" << abs->personarray[i].home << endl;
			
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
	cout << "请输入需要删除的联系人姓名：" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		for (int i = flag; i < abs->size; i++) {
			abs->personarray[i] = abs->personarray[i + 1];
		}
		abs->size--;
		cout << "删除成功！" << endl;
	}
	else {
		cout << "查无此人！" << endl;
	}
	system("pause");
	system("cls");
}
void findperson(struct address* abs) {
	cout << "请输入需要查找的联系人姓名：" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		cout << "姓名：" << abs->personarray[flag].name << "\t";
		cout << "性别：" << (abs->personarray[flag].sex == 1 ? "男" : "女") << "\t";
		cout << "年龄：" << abs->personarray[flag].age << "\t";
		cout << "电话：" << abs->personarray[flag].tele << "\t";
		cout << "住址：" << abs->personarray[flag].home << endl;
		cout << "查找成功！" << endl;
	}
	else {
		cout << "查无此人！" << endl;
	}
	system("pause");
	system("cls");
}
void modifyperson(struct address* abs) {
	cout << "请输入需要修改的联系人姓名：" << endl;
	string name;
	cin >> name;
	int flag = isexist(abs, name);
	if (flag != -1) {
		string name;
		cout << "请输入姓名:" << endl;
		cin >> name;
		abs->personarray[flag].name = name;
		cout << "请输入性别:" << endl;
		cout << "1--男，2--女" << endl;
		int sex = 0;

		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[flag].sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		cout << "请输入年龄：" << endl;
		int age = 0;

		while (true) {
			cin >> age;
			if (age > 0 && age <= 100) {
				abs->personarray[flag].age = age;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		cout << "请输入联系电话：" << endl;
		string tele;
		cin >> tele;
		abs->personarray[flag].tele = tele;

		cout << "请输入家庭住址：" << endl;
		string home;
		cin >> home;
		abs->personarray[flag].home = home;

		cout << "修改成功！" << endl;
	}
	else {
		cout << "查无此人！" << endl;
	}
	system("pause");
	system("cls");
}
void cleanperson(struct address* abs) {
	abs->size = 0;
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
int main() {
	int select = 0;
	address abs;
	abs.personarray[0] = { "张三",22,"13800000000",1,"中国"};
	abs.personarray[1] = { "李四",25,"13800000001",2,"日本" };
	abs.size = 2;

	while (true) {
		showMenu();
		cin >> select;
		switch (select) {
		case 0:
			cout << "欢迎下次使用！" << endl;
			return 0;
			break;

		case 1://添加联系人
			addperson(&abs);
			break;

		case 2://显示联系人
			showperson(&abs);
			break;

		case 3://删除联系人
			deleteperson(&abs);
			break;

		case 4://查找联系人
			findperson(&abs);
			break;

		case 5://修改联系人
			modifyperson(&abs);
			break;

		case 6:
			cleanperson(&abs);
			break;

		default:
			cout << "请重新输入编号！" << endl;
			system("pause");
			system("cls");
			break;

		}
	}
	


	return 0;

}