#include<bits/stdc++.h>
using namespace std;
struct Plant
{
	//植物信息定义
	string name;										//植物名称
	string sname;										//学名
	string place[100];									//分布地
	string detail;										//详情描述
};

typedef struct LNode
{
    Plant data;    	   //结点的数据域
    struct LNode *next; //指针域
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{
	ifstream readfile;
    readfile.open(filename.c_str());

    LinkList p;
    p=L;
    string line;

    while(getline(readfile,line))
    {
        Plant temp;
        int flag=0;
        string s;
        stringstream sall(line);

        while(getline(sall,s,'#'))
        {
            if(flag==0)
            {
                temp.name=s;
            }
            if(flag==1)
            {
                temp.sname=s;
            }
            if(flag==2)
            {
                int placenum=0;
                string place;
                stringstream splace(s);

                while(getline(splace,place,'@'))
                {
                    temp.place[placenum]=place;
                    placenum++;
                }
            }
            if(flag==3)
            {
                temp.detail=s;
            }
            flag++;
        }

        int i;
        LinkList q;
        q=new LNode;

        q->data.name=temp.name;
        q->data.sname=temp.sname;
        for(i=0;i<100;i++)
        {
            q->data.place[i]=temp.place[i];
        }
        q->data.detail=temp.detail;

        q->next=NULL;
        p->next=q;
        p=q;
    }
    readfile.close();
    return;
}

bool ChangePlant(LinkList &L,string name,string details,string filename)
{//修改植物信息
 //若该植物名称存在于plant.txt中，返回true，否则,返回false
    //修改指定信息所在结点的信息
    int flag;
    flag=0;
    LinkList p;
    p=L->next;

    for(p=L->next;p->next!=NULL;p=p->next)
    {
        if(p->data.name==name)
        {
            flag=1;
            p->data.detail=details;
        }
    }

    //重新将修改后的链表内容写入文件
    int i;
    ofstream writefile;
    writefile.open(filename.c_str());

    LinkList r;
    r=L->next;
    for(r=L->next;r;r=r->next)
    {
        writefile<<r->data.name<<"#"<<r->data.sname<<"#";
        for(i=0;i<(sizeof(r->data.place[i])/8)-1;i++)
        {
            writefile<<r->data.place[i]<<"@";
        }
        writefile<<r->data.place[i]<<"#";
        writefile<<r->data.detail<<endl;
    }

    //一个函数要求的返回
    if(flag==1)
    {
        return true;
    }
    else if(flag==0)
    {
        return false;
    }
}

void InitList(LinkList &L)
{//构造一个空的单链表L
    L=new LNode;
    L->next=NULL;
}

void Check(string name,string filename)
{//读取文件，输出修改后植物信息
	ifstream infile;
	infile.open(filename.c_str());    						//打开文件
	string line;
	while(getline(infile,line))
	{						//读取一行植物数据
		Plant temp;										//暂存每一行植物数据
		stringstream ss(line);							//分割每一行植物数据的4个数据项
    	string s;
    	int flag=0;
    	while (getline(ss,s,'#'))
		{
    		if(flag==0)	temp.name=s;
    		if(flag==1)	temp.sname=s;
    		if(flag==2)
			{
    			stringstream ssplace(s);				//保存每一行植物数据的分布地
    			string place;
    			int placenum=0;
    			while(getline(ssplace,place,'@'))
				{
    				temp.place[placenum]=place;
    				placenum++;
				}
			}
    		if(flag==3)	temp.detail=s;
    		if(temp.name==name)
			{
			   cout<<line<<endl;
			   break;
		    }
    		flag++;
		}
	}
	infile.close();
}

int main()
{
	string name,details;
	cin>>name>>details;
	string filename="data_edit/plant.txt";
	LinkList L;
	InitList(L);
	//读plant.txt文件
	ReadFile(L,filename);
	if(ChangePlant(L,name,details,filename))
	   Check(name,filename);
	else
	   cout<<"修改失败"<<endl;
	return 0;
}


/*
任务描述
本关任务：已知plant.txt的路径为"data_edit/plant.txt"，从plant.txt中读取植物的基本信息，
创建一个植物信息的链表，基于该链表，实现植物基本信息的修改功能。

编程要求
根据提示，在右侧编辑器补充代码，输入植物名称和修改后的详情描述信息，将修改后的信息存储到plant.txt中。
（注：需要判断该植物名称是否存在于plant.txt中，若存在，则执行修改操作，否则，输出“修改失败”。）

测试说明
平台会对你编写的代码进行测试：

测试输入：

二色补血草
茎丛生，直立或倾斜。叶多根出；匙形或长倒卵形，基部窄狭成翅柄，近于全缘。


罗蒙常山
落叶亚灌木，高达1-2米，下部通常平卧，上部直立；茎、叶柄、叶、花序都有绢状长毛及伏贴、弯曲短柔毛。叶对生，椭圆形，长5-10厘米，宽2.5-5厘米，边缘有锯齿；叶柄长1-2厘米。伞房状聚伞花序顶生，直径通常2-3厘米，具多数而密集的花，无总花梗；花两性，一型，蓝色，花芽时倒卵形，盛开时直径约8毫米，无放射花；
预期输出：
罗蒙常山#Dichroa yaoshanensis#湖南@广西@广东@云南#落叶亚灌木，高达1-2米，下部通常平卧，上部直立；茎、叶柄、叶、花序都有绢状长毛及伏贴、弯曲短柔毛。叶对生，椭圆形，长5-10厘米，宽2.5-5厘米，边缘有锯齿；叶柄长1-2厘米。伞房状聚伞花序顶生，直径通常2-3厘米，具多数而密集的花，无总花梗；花两性，一型，蓝色，花芽时倒卵形，盛开时直径约8毫米，无放射花

测试输入：
芍药 
多年生草本植物,根粗壮，分枝黑褐色。茎高40-70厘米，无毛。下部茎生叶为二回三出复叶，上部茎生叶为三出复叶；小叶狭卵形，椭圆形或披针形。

茉莉
常绿小灌木或藤本状灌木，性喜温暖，不耐霜冻。高可达1米。小枝有棱角，有时有毛。单叶对生，宽卵形或椭圆形，叶脉明显，叶面微皱，叶柄短而向上弯曲，有短柔毛。初夏由叶腋抽出新梢。
预期输出：
修改失败
*/


















