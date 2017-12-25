#include "base.h"
#include "definition.h"
#include "function.h"
#include "genealogy.h"

int main()
{
	Genealogy gen;
	Person *root = NULL;
	Person *temp;	//存放对象中的root
	Person* result;
	string name;	//搜索时用姓名
	Rel rel;//关系
	int rel_num;
	login:if (Login())
	{
		int choice;
		while(true)
		{
			cout<<"**************家谱管理系统管理界面**************"<<endl;
			cout<<"1.新建"<<endl;
			cout<<"2.删除"<<endl;
			cout<<"4.按名字搜索"<<endl;
			cout<<"5.显示族谱"<<endl;
			cout<<"6.更新数据"<<endl;
			cout<<"7.添加家族成员"<<endl;
			cout<<"8.统计数据"<<endl;
			cout<<"1024.切换用户"<<endl;
			cout<<"0.退出\n"<<endl;

			cout<<"输入你的选择："<<endl;
			cin>>choice;
			switch(choice)
			{
			case 1:
				if (gen.Create(&root))
				{
					gen.set_root(root);
					cout<<"创建成功！"<<endl;
				}
				else
					cout<<"创建失败！"<<endl;
				break;
			case 2:
				cout<<"输入你想要删除的人的名字："<<endl;
				cin>>name;
				temp = gen.get_root();
				if(gen.Delete(temp,name))
					cout<<"删除成功"<<endl;
				else
					cout<<"删除失败"<<endl;
				break;
			case 4:
				temp = gen.get_root();
				cout<<"输入一个名字："<<endl;
				cin>>name;
				result = gen.Search(temp,name);
				if(result)
					Display(result);
				else
					cout<<"家谱中没有这个人"<<endl;
				break;
			case 5:
				temp =gen.get_root();
				gen.Show(temp,0);
				break;
			case 6:
				temp =gen.get_root();
				cout<<"输入一个名字："<<endl;
				cin>>name;
				gen.Update(temp,name);
				break;
			case 7:
				temp =gen.get_root();
				cout<<"输入一个名字："<<endl;
				cin>>name;
				cout<<"这个人与将要添加的人的关系：（parent/brother）"<<endl;
				cin>>rel_num;	
				switch(rel_num)
				{
				case 0:
					rel = brother;
					break;
				default:
					rel = parent;
					break;
				}

				if(gen.Add(temp,name,rel))
					cout<<"添加成功"<<endl;
				else
					cout<<"添加失败"<<endl;
				break;
			case 8:
				temp =gen.get_root();
				if(gen.Statistics(temp))
					cout<<"统计完成"<<endl;
				gen.GetAge();
				gen.GetHeight();
				gen.GetRatio();
				break;
			case 1024:
				goto login;
				break;
			case 0:
				exit(0);
				break;
			default:
				cout<<"输入有误"<<endl;
				break;
			}
		}
	}
	else
	{
		int choice;
		while(true)
		{
			cout<<"**************家谱管理系统普通界面**************"<<endl;
			cout<<"1.查看家谱"<<endl;
			cout<<"2.搜索"<<endl;
			cout<<"3."<<endl;
			cout<<"4."<<endl;
			cout<<"1024.切换用户"<<endl;
			cout<<"0.退出\n"<<endl;

			cout<<"输入你的选择："<<endl;
			cin>>choice;
			switch(choice)
			{
			case 1:
				temp =gen.get_root();
				gen.Show(temp,0);
				break;
			case 2:
				temp = gen.get_root();
				cout<<"输入一个名字："<<endl;
				cin>>name;
				result = gen.Search(temp,name);
				if (result)
					Display(result);
				else
					cout<<"家谱中没有这个人"<<endl;
				break;
			case 1024:
				goto login;
				break;
			case 0:
				exit(0);
				break;
			}
		}
	}
	system("pause");
	return 0;
}