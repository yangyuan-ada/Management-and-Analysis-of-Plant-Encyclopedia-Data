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

void DeletePlant(LinkList &L,string name,string filename)
{//ɾ��ָ��ֲ����Ϣ
    //ɾ��ָ����Ϣ���ڽ��
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

    //���½��޸ĺ����������д���ļ�
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
{//����һ���յĵ�����L
    L=new LNode;
    L->next=NULL;
}

int Check(string name,string filename)
{//��ȡ�ļ����ж��Ƿ�ɾ���ɹ�
	ifstream infile;
	infile.open(filename.c_str());
	string line;
	while(getline(infile,line))
	{						                            //��ȡһ��ֲ������
		Plant temp;										//�ݴ�ÿһ��ֲ������
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������
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
{//���Ҵ�ɾ��ֲ����Ϣ
	ifstream infile;
	infile.open(filename.c_str());				//���ļ�
	string line;
	while(getline(infile,line))
	{						//��ȡһ��ֲ������
		string temp;										//�ݴ�ÿһ��ֲ������
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������
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
	//��plant.txt�ļ�
	ReadFile(L,filename);
    string plant;
    if(PlantInfo(name,filename)!="")
    {
		plant=PlantInfo(name,filename);
		DeletePlant(L,name,filename);
		if(Check(name,filename))                  //���ɾ���ɹ��������ɾ��ֲ���ȫ����Ϣ
		   	cout<<plant<<endl;
		else
		   	cout<<"ɾ��ʧ��"<<endl;
    }
    else
       	cout<<"ɾ��ʧ��"<<endl;

	return 0;
}

/*
��������
����������֪plant.txt��·��Ϊ"data_edit/plant.txt"����plant.txt�ж�ȡֲ��Ļ�����Ϣ��
����һ��ֲ����Ϣ���������ڸ�����ʵ��ֲ�������Ϣ��ɾ�����ܡ�

���Ҫ��
������ʾ�����Ҳ�༭��������룬ɾ��ֲ����Ϣ������Ҫɾ����ֲ�����ƣ�����ֲ���ȫ����Ϣ��plant.txt��ɾ����
��ע����Ҫ�жϸ�ֲ�������Ƿ������plant.txt�У������ڣ���ִ��ɾ�����������������ɾ��ʧ�ܡ�����

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
��ֲݣ�
Ԥ�������
��ֲ�#Rhynchospermum verticillatum#����@̨��@����@�㶫@����@����@����@����@����@�Ĵ�#�������ݱ�����25-100���ס�
����Ӳ��������������������ֱ��������ֱ���ɴ�8���ף�ͨ���в������в�״��֦������ʱ����״ʽ�����֦������״΢��ë��
Ҷ���汻��ϡ�����������ë������Ҷ��������ϡ���档�²��ľ�Ҷ�������Ρ�����Բ״�������Σ�����Բ�Σ�ϡ���Σ�
��4.5-14���ף���2.5-9���ף����˼��⣬��С��ͷ������Ш�ν������г��ľ߼�Ҷ������Ե���в������в�״�ľ�ݣ�
�в���Ҷ���ܣ��ڼ䳤1.5-2���ף������Σ��ж�Ҷ����ȫԵ���в�״Բ��ݻ��ݣ��ϲ�Ҷ��С��ȫԵ���м�ݡ�
ͷ״��������״��֦���˻���ҶҸ�����״���У�ֱ��4-5���ף����������ж̻��򹣣������ܱ���ɫ��״����ë��
�ܰ�����״����ڰ���״����3-4���ף��ܰ�Ƭ�Բ��ȳ������˶ۣ���ԵĤ�ʣ�˺�ѣ������״����Բ�Σ��в㳤��Բ�Σ�
�ڲ�������Բ�Ρ��ƻ�2-3�㣬���ڳ�1.2���ף��ܲ����̣����汻�ٵ㣻���Ի����ڳ�2���ף����汻�ٵ㡣�ƻ��ݹ�ѹ�⣬
����Բ�Σ���4���ף���1���ף����ϳ�������״�Ӻ�ı�Ե�����ػ�ɫС�ٵ㣻���Ի��ݹ�ӽ�̻��޺�����ë��ϸ�������䡣������8-11�¡�

�������룺
õ�壻
Ԥ�������
ɾ��ʧ��
*/
