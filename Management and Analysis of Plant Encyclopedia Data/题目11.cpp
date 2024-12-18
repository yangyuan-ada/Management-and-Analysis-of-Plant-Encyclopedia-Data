#include "iostream"
#include<bits/stdc++.h>
#include <string>
#include<stdlib.h>
using namespace std;
#define MAXLEN 5000			//������󳤶�

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
    return;
}

void GetNext(string pattern[],int next[],int newlength)
{//��ģʽ��pattern��next����ֵ����������next
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
{//�����ִ洢��������,�����˺������뷨�µı��
	int i,length;
	i=0,length=0;

	while(i<*len)
	{
	    //�ж������Ƿ�������
		if(target[i]>=0x80)
		{
		    //����Ϊ����
			ChiKey[length]=target.substr(i,2);
			i+=2;
		}
		else
        {
            //���ݲ�Ϊ����
			ChiKey[length]=target.substr(i,1);
			i++;
		}
		length++;
	}
	*len=length;
}

int Index_KMP(string target[],string pattern[],int next[],int len1,int len2)
{//KMPƥ���㷨,targetΪ������patternΪ�Ӵ�
//ƥ��ɹ����������������Ӵ���һ�γ��ֵ�λ�ã����򷵻�-1
//����GetNext������ȡģʽ����next����
	int i,j;
	i=0,j=0;

	GetNext(pattern,next,len2);

	while(i<len1&&j<len2)
	{
	    //�״�ƥ���ƥ��ɹ�������ƶ�λ��
		if(j==-1||target[i]==pattern[j])
		{
			i++;
			j++;
		}
		//ƥ�䲻�ɹ����л���
		else
		{
			j=next[j]-1;
		}
	}

	//����Ƿ�ƥ��ɹ��ķ���
	if(j!=len2)
    {
        return -1;
    }
	return i;
}

void SearchInfo(LinkList L,string keyword)
{//���õ���Index_KMP�������йؼ���Ϣ��ѯ
    //�ؼ���Ϣ������ת��
    string pattern[5000];
	int *keylen=new int;
	*keylen=keyword.length();
	GetChinese(keyword,pattern,keylen);

	for(L=L->next;L;L=L->next)
	{
	    //ֲ����Ϣ������ת��
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
{//����һ���յĵ�����L
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
��������
�������񣺱�дһ�������ַ���ģʽƥ���㷨��ֲ��ؼ���Ϣ��ѯ����

���Ҫ��
������ʾ�����Ҳ�༭��������룬���û��������Ȥ�Ĺؼ��ֺ�
ͨ��KMP�㷨���Խ�����Ĺؼ���������������Ϣ����ƥ�䣬�������ƥ�䵽��ֲ�����ơ�

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
