#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ����
	string name;										//����
	string sname;										//ѧ��
	string place[100];									//�ֲ���
	string detail;										//��������
};

typedef struct LNode{          							//������
	Plant data;
	struct LNode *next;
}LNode,*LinkList;

void InitList(LinkList &L)
{//�����ʼ��
    L=new LNode;
    L->next=NULL;
    return;
}

void ListInsert(LinkList &L,int i,Plant temp){
//�ڴ�ͷ���ĵ�����L�е�i��λ�ò����½��
    int j;
    j=0;

    LinkList p,q;
    p=L;
    while(p&&j<i-1)
    {
        p=p->next;
        ++j;
    }

    q= new LNode;
    q->data=temp;
    q->next=p->next;
    p->next=q;

    return;
}

int ReadFile(LinkList &L,string filename)
{//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ�������
//������ľ���ݵ�����
    ifstream readfile;
    readfile.open(filename.c_str());

    LinkList p;
    p=L;
    int i;
    i=0;
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
        i++;
        ListInsert(L,i,temp);
    }
    readfile.close();
}

LNode *LocateElem(LinkList L,string key)
{//�ڴ�ͷ���ĵ�����L�в���ֲ��ѧ��Ϊkey��Ԫ��
    LinkList p;
    p=L->next;

    while(p&&p->data.sname!=key)
    {
        p=p->next;
    }
    return p;
}

double ASL_LinkList(LinkList L,int count)
{//���ػ��������˳����ҵ�ASL
    //���ݹ�ʽ����ASL����
    double asl;
    LinkList p;
    p=L->next;

    count=0;
    while(p)
    {
        count++;
        p=p->next;
    }
    asl=(count+1)/2.0;

    return asl;
}

int main(){
	LinkList L;
	InitList(L);
	string filename="plant.txt";
	int count=0;
	count=ReadFile(L,filename);
	string sname;										//����Ҫ���ҵ�ֲ������
	getline(cin,sname);
	LNode *p=LocateElem(L,sname);
	if(p!=NULL){
		cout<<"���ҳɹ���"<<endl;
		cout<<"���ƣ�"<<p->data.name<<endl;
		cout<<"�ֲ��أ�" ;
		for(int j=0;j<100;j++)
			if(p->data.place[j]!="")
				cout<<p->data.place[j]<<" ";
		cout<<endl;
		cout<<"����������"<<p->data.detail<<endl;
		cout<<"ƽ�����ҳ���ASLΪ��"<<fixed<<setprecision(2)<<ASL_LinkList(L,count)<<endl;
	}else{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	return 0;
}


/*
��������
��plant.txt�ж�ȡֲ��Ļ�����Ϣ��ʵ�ֻ��������˳����ҡ�

���Ҫ��
������ʾ�����Ҳ�༭��������룬����ֲ��ѧ���������ҳɹ��������ֲ���Ӧ�Ļ�����Ϣ�����ơ��ֲ��ء�������������ͬʱ��������ҳɹ�ʱ��ƽ�����ҳ���ASL���������������ʧ�ܣ�����

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
Gentiana omeiensis
Ԥ�������
���ҳɹ���
���ƣ���ü����
�ֲ��أ��Ĵ�
�����������������ݱ�����30-40���ף��������ں�ɫ����Ĥ��Ҷ�ʰ�Χ�������������쳤��ƽ�Ի�б�죬�߶��������ʵ������֦2-4��������������1-3��Ӫ��֦��1����֦����ֱ֦��������ɫ����ʱ�Ϻ�ɫ���пգ���Բ�Σ��⻬��Ҷ�󲿷ֻ���������Բ�λ���Բ״�����Σ���5.5-12���ף���1-1.5���ף��ȶ˶ۣ�����������Ҷ��3��������������ԣ�����������ͻ��Ҷ��Ĥ�ʣ���4-8���ף�����Ҷ�٣�2-4�ԣ����Σ�ϡ����Բ�Σ���4-6���ף���1.5-2���ף��ȶ˶ۣ�����������Ҷ��1-3��������������ԣ���������ͻ��Ҷ����1-4.5���ף������ϲ�Ҷ��С�������̡������������������ϲ�ҶҸ�г���ɡ״��ϡ�����²���֦���г��ܻ�������С���������������Σ���11-13���ף����泣����ɫ����Ͳ���ʣ�һ�࿪�ѣ��ʷ����״����ԵĤ�ʣ���ݼ�С�����Σ���1-1.5���ף���ȱ�������Σ�������ɫ������ɫ���ƺͰߵ㣬Ͳ״���Σ���3.5-4���ף���Ƭ���Σ���4.5-5.5���ף��ȶ�Բ�λ�ۣ��ϰ벿ȫԵ���°벿�в�����ϸ�ݣ���ƫб�����λ������Σ���1-1.5���ף��ȶ˼��⣬��Ե�в�����ϸ�ݣ����������ڹ�Ͳ�²������룬��˿��״���Σ���13-16���ף���ҩ����Բ�Σ���3-3.5���ף��ӷ���״�����Σ���10-13���ף����˽���������10-13���ף������̶��֣���2-2.5���ף���ͷС��2�ѣ���Ƭ��Բ�Ρ������ڲأ�����Բ�Σ���1.3-1.5���ף����˶ۣ�������1-2���ף����ӻƺ�ɫ���й��󣬾�Բ�Σ���1-1.2���ף�����ߺ���״��϶��������7-9�¡�
ƽ�����ҳ���ASLΪ��3245.50

�������룺
Pelargonium hortorum
Ԥ�������
����ʧ�ܣ�
*/
