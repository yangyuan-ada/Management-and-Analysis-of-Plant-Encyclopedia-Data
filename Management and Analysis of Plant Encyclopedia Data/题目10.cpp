#include<bits/stdc++.h>
#include<string>
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
    Plant data;    	    //结点的数据域
    struct LNode *next; //指针域
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{//读取文件，将数据存入链表
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
        LinkList q;
        q=new LNode;
        q->data=temp;
        q->next=NULL;
        p->next=q;
        p=q;
    }

    readfile.close();
}

int Is_EngChar(char c)
{//判断是否为英文字符，若是，则返回1，不是则返回0
    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='×'||c=='['||c==']'||c=='.'|| c=='I')
        return 1;
    else
        return 0;
}

int Index_BF(string S,string T,int pos)
{
//返回模式T在主串S中第pos个字符开始第一次出现的位置。
//若不存在，则返回值为0
//其中，T非空，1≤pos≤S.length
//为判断是否为汉字，需调用Is_EngChar函数
    int i,j,s,t,len;
    s=S.length();
    t=T.length();

    //逐一位置进行对比并计算对比长度
    for(i=0;i<s;i++)
    {
        len=0;
        for(j=0;j<t;j++)
        {
            if(S[i+j]==T[j])
            {
                len++;
            }

            if(len==t)
            {
                return i;
            }
        }
    }
    return 0;
}

void SearchInfo(LinkList L,string keyWord)
{//调用Index_BF算法进行关键信息查询
    LinkList p;

    for(p=L->next;p;p=p->next)
    {
        if(Index_BF(p->data.detail,keyWord,1)!=0)
        {
            cout<<p->data.name<<endl;
        }
    }
}

void InitList(LinkList &L)
{//构造一个空的单链表L
    L=new LNode;
    L->next=NULL;
    return;
}

int main()
{
	string keyWord;
	cin>>keyWord;
	LinkList L;
	InitList(L);
	//读plant.txt文件
	string filename="plant.txt";
	ReadFile(L,filename);
	SearchInfo(L,keyWord);
	return 0;
}

/*
任务描述
本关任务：编写一个基于字符串模式匹配算法的植物关键信息查询程序。

编程要求
根据提示，在右侧编辑器补充代码，当用户输入感兴趣的关键字后，通过BF算法可以将输入的关键字与详情描述信息进行匹配，输出所有匹配到的植物名称。

测试说明
平台会对你编写的代码进行测试：

测试输入：
花瓣不存在；
预期输出：
山桂花
栀子皮
山铜材
尖叶水丝梨
*/
