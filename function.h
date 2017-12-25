#include <iostream>
#include <string>
using namespace std;

bool input(Info *info)	//此处返回时，注意局部变量的地址不能返回
{
	string name;
	cout<<"请输入相关信息："<<endl;
	cout<<"姓名：";
	cin>>info->name;
	cout<<"工作：";
	cin>>info->job;
	cout<<"身高：";
	cin>>info->height;
	cout<<"出生地：";
	wcin>>info->birthplace;	//宽字符
	cout<<"出生日期：";
	cin>>info->birthday;
	cout<<"死亡日期：";
	cin>>info->deathday;
	cout<<"享年："<<endl;
	cin>>info->age;
	cout<<"文化水平：";
	cin>>info->education;
	cout<<"是否有过卓著贡献：";
	cin>>info->great;
	cout<<"是否健在：";
	cin>>info->live;
	cout<<"性别(男1女0)：";
	cin>>info->gender;
	return true;
}

void Display(Person* p)
{
	cout<<"基本信息："<<endl;
	cout<<"姓名："<<p->info.name<<endl;
	cout<<"职业："<<p->info.job<<endl;
	cout<<"性别："<<p->info.gender<<endl;
	cout<<"身高："<<p->info.height<<endl;
	wcout<<"出生地："<<p->info.birthplace<<endl;
	cout<<"出生日期："<<p->info.birthday<<endl;
	cout<<"教育水平："<<p->info.education<<endl;
	cout<<"是否死亡："<<p->info.live<<endl;
	cout<<"死亡日期："<<p->info.deathday<<endl;
	cout<<"享年："<<p->info.age<<endl;
	cout<<"是否有过卓越贡献："<<p->info.great<<endl;
}
bool login_confirm()
{
	string passwd = "123456";
	string mypasswd;
	cout<<"输入密码：";
	cin>>mypasswd;
	if (passwd==mypasswd)
		return true;
	else
		return false;
}
bool Login()
{
	cout<<"********欢迎来到家谱管理系统管理员登录界面************"<<endl;
	int choice;
	while(true)
	{
		cout<<"1.我是管理员"<<endl;
		cout<<"2.我不是管理员\n"<<endl;
		cout<<"输入你的选择："<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			int count;
			if (login_confirm())
				return true;
			else
			{
				cout<<"*****提示：密码错误，你还有两次机会！"<<endl;
				for(count = 1;count<=3;count++)
				{
					if (login_confirm())
					{
						return true;
						break;
					}
					cout<<"*****提示：密码错误！"<<endl;
				}
				cout<<"你已经失败三次，自动跳转至普通界面"<<endl;
				return false;
			}
			break;
		case 2:
			return false;
			break;
		default:
			cout<<"没有这个选项！自动为你跳转普通界面"<<endl;
			return false;
		}
	}
}

/*bool Loging()
{
	char a[10];
	char b[10];
	char c[10]="abc123";
	char d[10]="123456";
	int flag;
	cout<<"请输入用户名："<<endl;
	cin>>a;
	cout<<"请输入密码："<<endl;
	cin>>b;
	if((!strcmp(a,c))&&(!strcmp(b,d)))
	{
		cout<<"验证通过!"<<endl;
		return true;
	}
	else
	{
		cout<<"请确认输入的账号密码是否正确！"<<endl;
		cout<<endl;
		cout<<"想要再次输入请按1，放弃请按2！"<<endl;
		cin>>flag;
		if(flag==1)
		{
			if(Loging())
			{
				return true;
			}
			else
				return false;
		}
		else 
			return false;
	}
}

bool Login()
{
	cout<<"如果你是管理员，请输入“1”后输入账号和密码！否则请输入“2”跳过~"<<endl;
	int i;
	cin>>i;
	switch(i)
	{
		case 1 :
			return Loging();
			break;
		case 2 :
			return false;
			break;
		default :
			return false;
			break;
	}
}*/

