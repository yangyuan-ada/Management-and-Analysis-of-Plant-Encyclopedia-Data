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

void DeletePlant(LinkList &L,string name,string filename)
{//删除指定植物信息
    //删除指定信息所在结点
    LinkList p,q;
    p=L;
    for(p=L;p->next!=NULL;p=p->next)
    {
        if(p->next->data.name==name)
        {
            q=p->next;
            p->next=q->next;
            delete q;
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
        for(i=0;i<sizeof(p->data.place)/sizeof(p->data.place[0]);i++)
        {
            writefile<<r->data.place[i]<<"@";
        }
        writefile<<r->data.place[i]<<"#";
        writefile<<r->data.detail<<endl;
    }
    return;
}

void InitList(LinkList &L)
{//构造一个空的单链表L
    L=new LNode;
    L->next=NULL;
}

int Check(string name,string filename)
{//读取文件，判断是否删除成功
	ifstream infile;
	infile.open(filename.c_str());
	string line;
	while(getline(infile,line))
	{						                            //读取一行植物数据
		Plant temp;										//暂存每一行植物数据
		stringstream ss(line);							//分割每一行植物数据的4个数据项
    	string s;
    	int flag=0;
    	while (getline(ss,s,'#'))
		{
    		if(flag==0)	temp.name=s;
    		if(temp.name==name)
			{
				infile.close();
			    return 0;
		    }
    		flag++;
		}
	}
	infile.close();
	return 1;
}

string PlantInfo(string name,string filename)
{//查找待删除植物信息
	ifstream infile;
	infile.open(filename.c_str());				//打开文件
	string line;
	while(getline(infile,line))
	{						//读取一行植物数据
		string temp;										//暂存每一行植物数据
		stringstream ss(line);							//分割每一行植物数据的4个数据项
    	string s;
    	int flag=0;
    	while(getline(ss,s,'#'))
		{
    		if(flag==0)	temp=s;
    		flag++;
    		if(temp==name)
    		   return line;
            break;
		}
	}
     return "";
}

int main()
{
	string name;
	cin>>name;
	LinkList L;
	InitList(L);
	string filename="data_edit/plant.txt";
	//读plant.txt文件
	ReadFile(L,filename);
    string plant;
    if(PlantInfo(name,filename)!="")
    {
		plant=PlantInfo(name,filename);
		DeletePlant(L,name,filename);
		if(Check(name,filename))                  //如果删除成功，输出已删除植物的全部信息
		   	cout<<plant<<endl;
		else
		   	cout<<"删除失败"<<endl;
    }
    else
       	cout<<"删除失败"<<endl;

	return 0;
}

/*
任务描述
本关任务：已知plant.txt的路径为"data_edit/plant.txt"，从plant.txt中读取植物的基本信息，
创建一个植物信息的链表，基于该链表，实现植物基本信息的删除功能。

编程要求
根据提示，在右侧编辑器补充代码，删除植物信息，输入要删除的植物名称，将该植物的全部信息从plant.txt中删除。
（注：需要判断该植物名称是否存在于plant.txt中，若存在，则执行删除操作，否则，输出“删除失败”。）

测试说明
平台会对你编写的代码进行测试：

测试输入：
秋分草；
预期输出：
秋分草#Rhynchospermum verticillatum#湖南@台湾@西藏@广东@福建@贵州@云南@湖北@江西@四川#多年生草本，高25-100厘米。
茎坚硬，单生，或少数簇生，直立，基部直径可达8毫米，通常中部以上有叉状分枝，或有时有总状式花序分枝，被尘状微柔毛。
叶两面被稍稀疏的贴伏短柔毛，基部叶花期脱落稀生存。下部的茎叶倒披针形、长椭圆状倒披针形，或长椭圆形，稀匙形，
长4.5-14厘米，宽2.5-9厘米，顶端急尖，有小尖头，基部楔形渐狭，有长的具冀叶柄，边缘自中部以上有波状的锯齿，
中部茎叶稠密，节间长1.5-2厘米，披针形，有短叶柄，全缘或有波状圆锯齿或尖齿；上部叶渐小，全缘或有尖齿。
头状花序单生叉状分枝顶端或单生叶腋或近总状排列，直径4-5毫米，果期增大，有短花序梗，花序梗密被锈色尘状短柔毛。
总苞宽钟状或果期半球状，宽3-4毫米，总苞片稍不等长，顶端钝，边缘膜质，撕裂，外层卵状长椭圆形，中层长椭圆形，
内层狭长椭圆形。雌花2-3层，花冠长1.2毫米，管部极短，外面被腺点；两性花花冠长2毫米，外面被腺点。雌花瘦果压扁，
长椭圆形，长4毫米，宽1毫米，嚎较长，有脉状加厚的边缘，被棕黄色小腺点；两性花瘦果咏短或无嚎。冠毛纤细，易脱落。花果期8-11月。

测试输入：
玫瑰；
预期输出：
删除失败
*/
