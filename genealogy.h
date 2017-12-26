class Genealogy{
private:
	Person *root;	//家谱老祖宗
	Num num;	//人数统计
	double ave_age;	//平均年龄
	double ave_height;	//平均身高
	double ratio;	//男女比例
	//疾病史暂不统计
	int sumage;	//总共年龄
	double sumheight;	//总共身高
public:
	Genealogy();	//构造函数初始化
	Person* get_root();
	void set_root(Person *root);
	bool Create(Person **p,Person **root);
	bool Login();	//管理员登录
	Person* Search(Person* p,const string name);
	Person* Search(Person* p,const string name,int tag);
	Person* FindPre(Person* p);
	bool Delete(Person* p,const string name); //按名字删除
	bool Update(Person* p,const string name);	//更改族谱
	bool Add(Person* p,string name,Rel rel);	//添加新成员
	void Show(Person* p,int depth);
	bool MemSearch();		//按成员查询
	bool RelSearch();	//查找成员之间的关系
	bool Statistics(Person* p);
	double GetAge();	//获取平均年龄	
	double GetHeight();	//获取平均身高
	double GetRatio();	//获取男女比例
};

Genealogy::Genealogy()
{
	this->root = NULL;
	this->num.sum = 0;
	this->num.mnum = 0;
	this->num.fnum = 0;
	this->num.lnum = 0;
	this->num.dnum = 0;
	this->num.gnum = 0;
	this->sumage = 0;
	this->sumheight = 0;
	this->ave_age = 0;
	this->ave_height = 0;
	this->ratio = 0;
}

Person* Genealogy::get_root()
{
	return root;
}

void Genealogy::set_root(Person* root)
{
	this->root = root;
}


bool Genealogy::Create(Person **p,Person **root)
{
	bool mate;
	int tag;
	*p = new Person;
	if (!(*p))
	{
		return false;
	}
	(*p)->parent = NULL;
	(*p)->firstchild = NULL;
	(*p)->nexsilbing = NULL;
	cout<<"本人："<<endl;
	input(&((*p)->info));
	cout<<"是否有配偶？（1表示有，0表示没有）"<<endl;
	Detect(&mate);
	if (mate)
	{
		cout<<"配偶："<<endl;
		input(&((*p)->mate));
	}
	Show(*root,0);
	cout<<"1.添加"<<(*p)->info.name<<"的孩子"<<endl;
	cout<<"2.添加"<<(*p)->info.name<<"的兄弟姐妹"<<endl;
	cout<<"3.不再添加"<<(*p)->info.name<<"的后代及同胞"<<endl;
	cout<<"输入你的选择：";
	Detect(&tag);
	switch(tag)
	{
	case 1:
		Create(&((*p)->firstchild),root);
		if ((*p)->firstchild)
			(*p)->firstchild->parent = *p;
		cout<<"******是否添加"<<(*p)->info.name<<"的兄弟姐妹"<<endl;
		Detect(&tag);
		if(tag)
		{
			Create(&((*p)->nexsilbing),root);
			if ((*p)->nexsilbing)
				(*p)->nexsilbing->parent = (*p)->parent;
		}
		else
			(*p)->nexsilbing = NULL;
		return true;
		break;
	case 2:
		Create(&((*p)->nexsilbing),root);
		if ((*p)->nexsilbing)
			(*p)->nexsilbing->parent = (*p)->parent;
		cout<<"******是否添加"<<(*p)->info.name<<"的孩子？（1表示是，0表示不添加）"<<endl;
		Detect(&tag);
		if(tag)
		{
			Create(&((*p)->firstchild),root);
			if ((*p)->firstchild)
				(*p)->firstchild->parent = *p;
		}
		else
			(*p)->firstchild = NULL;
		return true;
		break;
	case 3:
		(*p)->firstchild = NULL;
		(*p)->nexsilbing = NULL;
		return true;
		break;
	default:
		(*p)->firstchild = NULL;
		(*p)->nexsilbing = NULL;
		return true;
		break;
	}
}
/*bool Genealogy::Create(Person **p)
{
	int tag;
	bool mate;
	cout<<"输入一个数（输入0表示该节点为空）:"<<endl;
	cin>>tag;
	if (!tag)
	{
		*p =  NULL;
	}
	else
	{
		*p = new Person;
		if (!(*p))
		{
			return false;
		}
		(*p)->parent = NULL;
		cout<<"本人："<<endl;
		input(&((*p)->info));
		cout<<"是否有配偶？（1表示有，0表示没有）"<<endl;
		cin>>mate;
		if (mate)//有配偶才有孩子
		{
			cout<<"配偶："<<endl;
			input(&((*p)->mate));
			Create(&((*p)->firstchild));
			if ((*p)->firstchild)
				(*p)->firstchild->parent = *p;
		}
		else
		{
			(*p)->firstchild = NULL;
		}
		Create(&((*p)->nexsilbing));
		if ((*p)->nexsilbing)
			(*p)->nexsilbing->parent = (*p)->parent;
	}
	return true;
}*/
/*bool Genealogy::Create(Person **p)
{
	bool mate;
	if((*p)->parent)
	{
		int tag;
		cout<<"1.添加"<<(*p)->parent->info.name<<"的孩子"<<endl;
		cout<<"2.添加"<<(*p)->parent->info.name<<"的兄弟姐妹"<<endl;
		cout<<"3.不再添加"<<(*p)->parent->info.name<<"的后代及同胞"<<endl;
		cout<<"输入你的选择：";
		Detect(&tag);
		switch(tag)
		{
		case 1:

			break;
		case 2:
			break;
		case 3:
			*p = NULL;
			return true;
			break;
		default:
			*p = NULL;
			return true;
			break;
		}
	}
	else
	{
		*p = new Person;
		if (!(*p))
		{
			return false;
		}
		(*p)->parent = NULL;
		cout<<"基本信息："<<endl;
		input(&((*p)->info));
		cout<<"是否有配偶？（1表示有，0表示没有）"<<endl;
		Detect(&mate);	//合法性检测
		if (mate)//有配偶才有孩子
		{
			cout<<"配偶："<<endl;
			input(&((*p)->mate));
			Create(&((*p)->firstchild));
			if ((*p)->firstchild)
				(*p)->firstchild->parent = *p;
		}
		else
		{
			(*p)->firstchild = NULL;
		}
		Create(&((*p)->nexsilbing));
		if ((*p)->nexsilbing)
			(*p)->nexsilbing->parent = (*p)->parent;
	}
	if (!tag)
	{
		*p =  NULL;
	}
	else
	{
		*p = new Person;
		if (!(*p))
		{
			return false;
		}
		(*p)->parent = NULL;
		cout<<"基本信息："<<endl;
		input(&((*p)->info));
		cout<<"是否有配偶？（1表示有，0表示没有）"<<endl;
		Detect(&mate);	//合法性检测
		if (mate)//有配偶才有孩子
		{
			cout<<"配偶："<<endl;
			input(&((*p)->mate));
			Create(&((*p)->firstchild));
			if ((*p)->firstchild)
				(*p)->firstchild->parent = *p;
		}
		else
		{
			(*p)->firstchild = NULL;
		}
		Create(&((*p)->nexsilbing));
		if ((*p)->nexsilbing)
			(*p)->nexsilbing->parent = (*p)->parent;
	}
	return true;
}*/
Person* Genealogy::FindPre(Person* p)//找到与p节点相连的前一个节点
{
	if(p)
	{
		Person* temp;
		Person* pre;
		Person* current;
		if(p->parent)	
		{
			temp = p->parent;
			if (temp->firstchild!=p) //判断p是否是第一个孩子
			{
				current = temp->firstchild;
				while(current!=p)
				{
					pre = current;
					current = current->nexsilbing;
				}
				return pre;//返回前一个兄弟
			}
			else	//是第一个孩子，直接返回父节点
				return temp;
		}
		else		//只有第一代人才没有父节点
		{
			if(root==p)
				return NULL;
			else{
				current = root;
				while(current!=p)
				{
					pre = current;
					current = current->nexsilbing;
				}
				return pre;
			}
		}
	}
	return NULL;
}
Person* Genealogy::Search(Person* p,const string name)
{
	if(p)
	{
		//Person* pre;	//标记名字匹配节点的前一个节点
		Person* temp;
		//pre = p;
		if (p->info.name==name)
			return p;
		else
		{
			temp = Search(p->firstchild,name);
			if(temp)
				return temp;
			temp = Search(p->nexsilbing,name);
			if (temp)
				return temp;
			return NULL;
		}
	}
	return NULL;
}
Person* Genealogy::Search(Person* p,const string name,int tag)	//模糊查询
{
	if(p)
	{
		return NULL;
	}
	return NULL;
}
/*Person* Search(Person* p,const string name)
{
	Person* temp;
	if (p->info.name==name)
		return p;
	else
	{
		if (p->firstchild)
			temp = Search(p->firstchild,name);
			if (temp)
				return temp;
		if (p->nexsilbing)
			temp = Search(p->nexsilbing,name);
			if (temp)
				return temp;
		if (!p->firstchild&&!p->nexsilbing)
			return NULL;
	}
}*/

bool Genealogy::Delete(Person *p,const string name)//此处bug:如果删除的节点为根节点，怎么将根置为NULL,双指针。
{
	if(p)
	{
		Person* target;
		Person* pre;
		target = Search(p,name);
		if (target)
		{
			if(target->firstchild||target->nexsilbing)
			{
				cout<<"该节点不能被删除"<<endl;
				return false;
			}
			else
			{
				pre = FindPre(target);
				if (pre)//目标节点前一个节点存在
				{
					if (pre->firstchild==target)
						pre->firstchild=NULL;
					else
						pre->nexsilbing = NULL;
				}
				free(target);
				return true;
			}
		}
		return false;//家谱中没有这个人
	}
	return false;
}

void Genealogy::Show(Person* p,int depth)
{
	if(p)
	{
		int i;
		for (i = 1;i<=depth;i++)
		{
			cout<<"\t";
		}
		cout<<p->info.name<<endl;
		Show(p->firstchild,depth+1);
		Show(p->nexsilbing,depth);
	}
}
/*bool Genealogy::Delete(Person getroot(),const string name)
{
	const char* M=name.c_str();
	const char* N=getroot().info.name.c_str();

	if((&getroot()!=NULL))
	{
		if((!strcmp(N,M))&&(getroot().firstchild==NULL)&&(getroot().nexsilbing==NULL))
		{
			free(&getroot());
			cout<<"已成功删除此人信息！"<<endl;
			return true;
		}
		else if((!strcmp(N,M))&&(getroot().firstchild!=NULL)||(getroot().nexsilbing!=NULL))
		{
			cout<<"此人不可删除！"<<endl;
			return true;
		}
		else if(getroot().firstchild!=NULL)
		{
			Delete(getroot().firstchild,name);
		}
		else if(getroot().nexsilbing!=NULL)
		{
			Delete(getroot().nexsilbing,name);
		}
	}
	else 
		{
			cout<<"未找到此人！"<<endl;
			return false;
		}
}
*/



bool Genealogy::Update(Person* p,const string name)
{
	Person* temp;
	temp = Search(p,name);
	if (temp)
	{
		Display(temp);	//显示初始信息
		input(&(temp->info));	//进行更改
		return true;
	}
	else
		cout<<"家谱中无该成员！"<<endl;
		return false;
}

bool Genealogy::Add(Person *p,string name,Rel rel)
{
	Person* temp;
	Person* point;//接受父、兄
	bool mate;
	point = Search(p,name);
	if (point)
	{
		temp = new Person;
		input(&(temp->info));
		temp->firstchild = NULL;
		temp->nexsilbing = NULL;
		temp->parent = NULL;
		cout<<"是否有配偶：（1表示有，0没有）"<<endl;
		cin>>mate;
		if (mate)
		{
			input(&(temp->mate));
		}
		else
		{
			temp->mate.name = "无";		//没有配偶就将配偶名字置为无
		}
		if (rel==parent)
		{
			if (point->firstchild)
			{
				Person* child,*prechild;
				child = point->firstchild;
				while(child)
				{
					prechild = child;
					child = child->nexsilbing;
				}
				prechild->nexsilbing = temp;	//把temp添加到父亲的这几个儿子的最后
				temp->parent = prechild->parent;
			}
			else
			{
				point->firstchild = temp;
				temp->parent = point;
			}
		}
		else
		{
			if(point->nexsilbing)
			{
				Person* child,*prechild;
				child = point->nexsilbing;
				while(child)
				{
					prechild = child;
					child = child->nexsilbing;
				}
				prechild->nexsilbing = temp;
				temp->parent = prechild->parent;
				return true;
			}
			else
			{
				point->nexsilbing = temp;
				temp->parent = point->parent;
			}
		}
	}
	else
		return false;
}


bool Genealogy::Statistics(Person* p)
{
	if(p)
	{
		if(p->info.gender==0)
			num.fnum++;
		if(p->info.gender==1)
			num.mnum++;
		if(p->info.live)
			num.lnum++;
		if(!p->info.live)
			num.dnum++;
		if(p->mate.great)
			num.gnum++;
		if(p->info.live==0)
			sumage+=p->info.age;
		if(p->info.live==0)
			sumheight+=p->info.height;
		num.sum++;
		Statistics(p->firstchild);
		Statistics(p->nexsilbing);
	}
	return false;
}


double Genealogy::GetAge()
{
	if(num.dnum)
	{
		ave_age = sumage/double(num.dnum);
		cout<<"平均年龄为："<<ave_age<<endl;
		return ave_age;
	}
	cout<<"目前无法统计"<<endl;
	return 1000;
}
double Genealogy::GetHeight()
{
	if(num.dnum)
	{
		ave_height = sumheight/num.dnum;  
		cout<<"平均身高："<<ave_height<<endl;
		return ave_height;
	}
	cout<<"目前无法统计"<<endl;
	return 10000;
	
}
double Genealogy::GetRatio()
{
	if(num.fnum)
	{
		ratio = num.mnum/double(num.fnum);
		cout<<"该家族男女比例为："<<num.mnum<<"："<<num.fnum<<endl;
		return ratio;
	}
	else
	{
		ratio = 1;
		cout<<"该家族男女比例为："<<num.mnum<<"："<<num.fnum<<endl;
		return ratio;
	}
}