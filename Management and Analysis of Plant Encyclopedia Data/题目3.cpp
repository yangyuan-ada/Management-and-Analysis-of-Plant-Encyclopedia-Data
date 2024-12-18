#include<bits/stdc++.h>
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
    Plant data;    	   //����������
    struct LNode *next; //ָ����
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
{//�޸�ֲ����Ϣ
 //����ֲ�����ƴ�����plant.txt�У�����true������,����false
    //�޸�ָ����Ϣ���ڽ�����Ϣ
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

    //���½��޸ĺ����������д���ļ�
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

    //һ������Ҫ��ķ���
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
{//����һ���յĵ�����L
    L=new LNode;
    L->next=NULL;
}

void Check(string name,string filename)
{//��ȡ�ļ�������޸ĺ�ֲ����Ϣ
	ifstream infile;
	infile.open(filename.c_str());    						//���ļ�
	string line;
	while(getline(infile,line))
	{						//��ȡһ��ֲ������
		Plant temp;										//�ݴ�ÿһ��ֲ������
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������
    	string s;
    	int flag=0;
    	while (getline(ss,s,'#'))
		{
    		if(flag==0)	temp.name=s;
    		if(flag==1)	temp.sname=s;
    		if(flag==2)
			{
    			stringstream ssplace(s);				//����ÿһ��ֲ�����ݵķֲ���
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
	//��plant.txt�ļ�
	ReadFile(L,filename);
	if(ChangePlant(L,name,details,filename))
	   Check(name,filename);
	else
	   cout<<"�޸�ʧ��"<<endl;
	return 0;
}


/*
��������
����������֪plant.txt��·��Ϊ"data_edit/plant.txt"����plant.txt�ж�ȡֲ��Ļ�����Ϣ��
����һ��ֲ����Ϣ���������ڸ�����ʵ��ֲ�������Ϣ���޸Ĺ��ܡ�

���Ҫ��
������ʾ�����Ҳ�༭��������룬����ֲ�����ƺ��޸ĺ������������Ϣ�����޸ĺ����Ϣ�洢��plant.txt�С�
��ע����Ҫ�жϸ�ֲ�������Ƿ������plant.txt�У������ڣ���ִ���޸Ĳ���������������޸�ʧ�ܡ�����

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺

��ɫ��Ѫ��
��������ֱ������б��Ҷ����������λ򳤵����Σ�����խ���ɳ��������ȫԵ��


���ɳ�ɽ
��Ҷ�ǹ�ľ���ߴ�1-2�ף��²�ͨ��ƽ�ԣ��ϲ�ֱ��������Ҷ����Ҷ�������о�״��ë����������������ë��Ҷ��������Բ�Σ���5-10���ף���2.5-5���ף���Ե�о�ݣ�Ҷ����1-2���ס�ɡ��״��ɡ��������ֱ��ͨ��2-3���ף��߶������ܼ��Ļ������ܻ����������ԣ�һ�ͣ���ɫ����ѿʱ�����Σ�ʢ��ʱֱ��Լ8���ף��޷��仨��
Ԥ�������
���ɳ�ɽ#Dichroa yaoshanensis#����@����@�㶫@����#��Ҷ�ǹ�ľ���ߴ�1-2�ף��²�ͨ��ƽ�ԣ��ϲ�ֱ��������Ҷ����Ҷ�������о�״��ë����������������ë��Ҷ��������Բ�Σ���5-10���ף���2.5-5���ף���Ե�о�ݣ�Ҷ����1-2���ס�ɡ��״��ɡ��������ֱ��ͨ��2-3���ף��߶������ܼ��Ļ������ܻ����������ԣ�һ�ͣ���ɫ����ѿʱ�����Σ�ʢ��ʱֱ��Լ8���ף��޷��仨

�������룺
��ҩ 
�������ݱ�ֲ��,����׳����֦�ں�ɫ������40-70���ף���ë���²�����ҶΪ����������Ҷ���ϲ�����ҶΪ������Ҷ��СҶ�����Σ���Բ�λ������Ρ�

����
����С��ľ���ٱ�״��ľ����ϲ��ů������˪�����߿ɴ�1�ס�С֦����ǣ���ʱ��ë����Ҷ�����������λ���Բ�Σ�Ҷ�����ԣ�Ҷ��΢�壬Ҷ���̶������������ж���ë��������ҶҸ������ҡ�
Ԥ�������
�޸�ʧ��
*/


















