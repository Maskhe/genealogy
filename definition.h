typedef struct num{
	int sum;	//总人数
	int fnum;	//女性人数
	int mnum;	//男性人数
	int dnum;	//逝去人数
	int lnum;	//健在人数
	int gnum;	//有重大贡献的人数
}Num;
typedef struct info{
	string name;
	string job;
	double height;
	wstring birthplace;
	string birthday;
	string deathday;
	string education;
	int age;
	bool great;
	bool live;
	bool gender;
}Info;

typedef struct person{
	Info info;		//具体信息
	Info mate;		//配偶信息
	struct person* parent;
	struct person* firstchild;
	struct person* nexsilbing;
}Person;

typedef enum rel{parent,brother}Rel;
