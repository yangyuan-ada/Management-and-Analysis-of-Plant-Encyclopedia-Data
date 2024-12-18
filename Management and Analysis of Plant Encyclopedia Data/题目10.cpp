#include<bits/stdc++.h>
#include<string>
using namespace std;

struct Plant
{
	//ֲ����Ϣ����
	string name;										//ֲ������
	string sname;										//ѧ��
	string place[100];									//�ֲ���
	string detail;										//��������
};

typedef struct LNode
{
    Plant data;    	    //����������
    struct LNode *next; //ָ����
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{//��ȡ�ļ��������ݴ�������
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
{//�ж��Ƿ�ΪӢ���ַ������ǣ��򷵻�1�������򷵻�0
    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='��'||c=='['||c==']'||c=='.'|| c=='I')
        return 1;
    else
        return 0;
}

int Index_BF(string S,string T,int pos)
{
//����ģʽT������S�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á�
//�������ڣ��򷵻�ֵΪ0
//���У�T�ǿգ�1��pos��S.length
//Ϊ�ж��Ƿ�Ϊ���֣������Is_EngChar����
    int i,j,s,t,len;
    s=S.length();
    t=T.length();

    //��һλ�ý��жԱȲ�����Աȳ���
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
{//����Index_BF�㷨���йؼ���Ϣ��ѯ
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
{//����һ���յĵ�����L
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
	//��plant.txt�ļ�
	string filename="plant.txt";
	ReadFile(L,filename);
	SearchInfo(L,keyWord);
	return 0;
}

/*
��������
�������񣺱�дһ�������ַ���ģʽƥ���㷨��ֲ��ؼ���Ϣ��ѯ����

���Ҫ��
������ʾ�����Ҳ�༭��������룬���û��������Ȥ�Ĺؼ��ֺ�ͨ��BF�㷨���Խ�����Ĺؼ���������������Ϣ����ƥ�䣬�������ƥ�䵽��ֲ�����ơ�

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
���겻���ڣ�
Ԥ�������
ɽ��
����Ƥ
ɽͭ��
��Ҷˮ˿��
*/
