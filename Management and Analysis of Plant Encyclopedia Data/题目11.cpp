#include "iostream"
#include<bits/stdc++.h>
#include <string>
#include<stdlib.h>
using namespace std;
#define MAXLEN 5000			//串的最大长度

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
    return;
}

void GetNext(string pattern[],int next[],int newlength)
{//求模式串pattern的next函数值并存入数组next
    int i,j,k;
    i=0,j=-1;
    next[0]=0;

    while(i<newlength-1)
    {
        if(j==-1||pattern[i]==pattern[j])
        {
            i++;
            j++;
            next[i]=j+1;
        }
        else
        {
            j=next[j]-1;
        }
    }
}

void GetChinese(string target,string ChiKey[],int *len)
{//将汉字存储在数组里,包括了汉字输入法下的标点
	int i,length;
	i=0,length=0;

	while(i<*len)
	{
	    //判断内容是否是中文
		if(target[i]>=0x80)
		{
		    //内容为中文
			ChiKey[length]=target.substr(i,2);
			i+=2;
		}
		else
        {
            //内容不为中文
			ChiKey[length]=target.substr(i,1);
			i++;
		}
		length++;
	}
	*len=length;
}

int Index_KMP(string target[],string pattern[],int next[],int len1,int len2)
{//KMP匹配算法,target为主串，pattern为子串
//匹配成功返回主串中所含子串第一次出现的位置，否则返回-1
//调用GetNext函数获取模式串的next数组
	int i,j;
	i=0,j=0;

	GetNext(pattern,next,len2);

	while(i<len1&&j<len2)
	{
	    //首次匹配或匹配成功后进行移动位置
		if(j==-1||target[i]==pattern[j])
		{
			i++;
			j++;
		}
		//匹配不成功进行回退
		else
		{
			j=next[j]-1;
		}
	}

	//最后是否匹配成功的返回
	if(j!=len2)
    {
        return -1;
    }
	return i;
}

void SearchInfo(LinkList L,string keyword)
{//调用调用Index_KMP函数进行关键信息查询
    //关键信息的中文转换
    string pattern[5000];
	int *keylen=new int;
	*keylen=keyword.length();
	GetChinese(keyword,pattern,keylen);

	for(L=L->next;L;L=L->next)
	{
	    //植物信息的中文转换
	    string Chi[5000];
		int next[5000];
        int *len= new int;
		*len=L->data.detail.length();
		GetChinese(L->data.detail,Chi,len);

		int flag;
		flag=Index_KMP(Chi,pattern,next,*len,*keylen);
		if(flag!=-1)
		{
			cout<<L->data.name<<endl;
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
	string keyword;
	cin >> keyword;
	LinkList L;
	InitList(L);
	string filename="plant.txt";
	ReadFile(L,filename);
	int num = keyword.length();
	SearchInfo(L,keyword);
	return 0;
}

/*
任务描述
本关任务：编写一个基于字符串模式匹配算法的植物关键信息查询程序。

编程要求
根据提示，在右侧编辑器补充代码，当用户输入感兴趣的关键字后，
通过KMP算法可以将输入的关键字与详情描述信息进行匹配，输出所有匹配到的植物名称。

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
