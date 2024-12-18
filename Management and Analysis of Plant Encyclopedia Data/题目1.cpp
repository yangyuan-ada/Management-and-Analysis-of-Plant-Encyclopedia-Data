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
{//���ļ��ж�ȡ���ݣ���������L��
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

int InPlant(LinkList L,string name)
{//�жϸ�ֲ������name�Ƿ������������
    int flag=0;
    LinkList p;
    p=L->next;

    for(p=L->next;p->next!=NULL;p=p->next)
    {
        if(p->data.name==name)
        {
            flag=1;
        }
    }

    return flag;
}

bool InsertPlant(LinkList &L,string filename)
{//����ֲ����Ϣ������ֲ������ơ�ѧ�����ֲ��غ�����������Ϣ������ֲ��Ļ�����Ϣ��ӵ�plant.txt�е����
 //�����ֲ�����ƴ�����plant.txt�У�����false�����򣬷���true
    int i,j,n;
    string addname;

    LinkList p;
    p=L->next;
    while(p->next!=NULL)
    {
        p=p->next;
    }

    getline(cin,addname);
    i=InPlant(L,addname);
    if(i==1)
    {
        return false;
    }
    else
    {
        LinkList q;
        q=new LNode;
        q->next=NULL;
        p->next=q;

        //��ȡ������Ϣ
        q->data.name=addname;
        getline(cin,q->data.sname);
        cin>>n;
        for(j=0;j<n;j++)
        {
            cin>>q->data.place[j];
        }
        cin>>q->data.detail;

        //������������
        LinkList p;
        p=L->next;

        //���½��޸ĺ����������д���ļ�
        ofstream writefile;
        writefile.open(filename.c_str(),ios::app);
        for(p=L->next;p;p=p->next)
        {
            writefile<<p->data.name<<"#"<<p->data.sname<<"#";
            for(j=0;j<n-1;j++)
            {
                writefile<<p->data.place[j]<<"@";
            }
            writefile<<p->data.place[j]<<"#";
            writefile<<p->data.detail<<endl;
        }
        return true;
    }
}

void InitList(LinkList &L)
{//����һ���յĵ�����L
    L=new LNode;
    L->next=NULL;
}

void Check(string filename)
{//��ȡ�ļ����һ�����ݣ�������ֲ����Ϣ
	ifstream infile;
	infile.open(filename.c_str());    						//���ļ�
	string line, last_line;
	while (getline(infile, line))
	{
		last_line = line;
	}
	cout << last_line << endl;
	infile.close();
}

int main(){
	LinkList L;
	string filename="data_edit/plant.txt";
	InitList(L);
	//��plant.txt�ļ�
	ReadFile(L,filename);
	if(InsertPlant(L,filename))
	   Check(filename);
	else
	   cout<<"����ʧ��\n";
	return 0;
}

/*
��������
����������֪plant.txt��·��Ϊ"data_edit/plant.txt"����plant.txt�ж�ȡֲ��Ļ�����Ϣ������һ��ֲ����Ϣ���������ڸ�����ʵ��ֲ�������Ϣ�����ӹ��ܡ�

���Ҫ��
������ʾ�����Ҳ�༭��������룬����ֲ������ơ�ѧ�����ֲ��غ�����������Ϣ������ֲ��Ļ�����Ϣ��ӵ�plant.txt�е����
��ע������ֲ��������Ψһ�ģ����������ʱ��Ҫ�жϸ�ֲ�������Ƿ������plant.txt�У������ڣ������������ʧ�ܡ�������ֲ���ʱ��������ֲ��ظ���������������ֲ��أ�

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
�ѹ�Ӣ
Taraxacum mongolicum
2
������
����
�������ݱ������Գ�Բ׶״����������4��10���ף������غ�ɫ����������ͷ������ɫ��ư�ɫ��ë�ס�Ҷ�ɵ���״�����Ρ��������λ�Բ״�����Σ���4��20���ף���1-5���ף��ȶ˶ۻ򼱼⣬��Ե��ʱ�߲�״�ݻ���״���ѣ���ʱ������״���ѻ��ͷ��״���ѣ�������Ƭ�ϴ������λ�����״��Σ�ȫԵ��߳ݣ�ÿ����Ƭ3��5Ƭ����Ƭ�����λ�����״�����Σ�ͨ���߳ݣ�ƽչ������Ƭ�䳣����С�ݣ�����������Ҷ����Ҷ����������������ɫ���豻��˿״��ɫ��ë����ë��

��ҩ
Paeonia lactiflora Pall
3
����
�㽭
����
�������ݱ�ֲ�����׳����֦�ں�ɫ������40-70���ף���ë���²�����ҶΪ����������Ҷ���ϲ�����ҶΪ������Ҷ��СҶ�����Σ���Բ�λ������Ρ�
 
���������
�ѹ�Ӣ#Taraxacum mongolicum#������@����#�������ݱ������Գ�Բ׶״����������4��10���ף������غ�ɫ����������ͷ������ɫ��ư�ɫ��ë�ס�Ҷ�ɵ���״�����Ρ��������λ�Բ״�����Σ���4��20���ף���1-5���ף��ȶ˶ۻ򼱼⣬��Ե��ʱ�߲�״�ݻ���״���ѣ���ʱ������״���ѻ��ͷ��״���ѣ�������Ƭ�ϴ������λ�����״��Σ�ȫԵ��߳ݣ�ÿ����Ƭ3��5Ƭ����Ƭ�����λ�����״�����Σ�ͨ���߳ݣ�ƽչ������Ƭ�䳣����С�ݣ�����������Ҷ����Ҷ����������������ɫ���豻��˿״��ɫ��ë����ë��

�������룺
����������
Anemone obtusiloba
2
����
�Ĵ�
ֲ���10-30���ס�����Ҷ7-15���г����������ܱ�����ë��ҶƬ��״����λ�����Σ���1.2-3���ף���1.7-5.5���ף��������Σ���ȫ�ѻ�ż�����ѽ���������ȫ��Ƭ��״�����Σ�����ǳ�ѣ���ȫ��Ƭ����ȫ��Ƭ���ȴ����С��������Ƭ��������ڽӻ��Ը�ѹ������ƽ��Ҷ��3-18���ס�����2-5���п�չ����ë����Ƭ3���ޱ����Բ��ȴ󣬿����λ�Ш�Σ��������ѣ���1-2���ף������ܱ���ë������1-2����1.5-8���ף���Ƭ5(-8)����ɫ����ɫ���ɫ�������λ��������Σ���0.8-1.2���ף���5-8���ף���������ë�����ﳤԼ4���ף���ҩ��Բ�Σ���ƤԼ8���ӷ��ܱ���ë��5����7�¿�������

���������
����ʧ��

��ɫ��Ѫ��
Limonium bicolor
4
����
����
������
����
�������ݱ�����20-50���ף�ȫ��(������)��ë��Ҷ������ż�ɻ������²�1-3������Ҷ������Ҷ�����ڣ���������Բ״���Σ���3-15���ף���0.5-3���ף��ȶ�ͨ��Բ��ۣ�����������ƽ��ı�������Բ׶״�������ᵥ������2-5ö���ɲ�ͬ��Ҷ����������ͨ����3-4��ǣ���ʱ�߹��ۣ�ż������Բ��״��ס�����в����������ط�֦��ĩ��С֦�����Σ�����֦��(�������˺�ʱ���²�������������֦)��ͨ���򵥣�λ�ڷ�֦�²������ڷֲ洦����״�����б����ޱ��������ڻ����֦���ϲ������ˣ���3-5(9)��С����ɣ�С�뺬2-3(5)��(��4-5��ʱ�򱻵�һ�ڰ�������1-2����������)�������Լ2.5-3.5���ף���Բ״������(���ʲ������λ�Բ��)����һ�ڰ���Լ6-6.5���ף��೤6-7���ף�©��״����Ͳ��Լ1���ף�ȫ�����°벿�����ܱ���ë�����ܳ�ʱ���Ϻ��ۺ�ɫ��������ף���Ϊ����ȫ����һ��(3-3.5����)�����ŷ�������ĳ�����ȣ���Ƭ��̶��ȶ�ͨ��Բ��ż����һ�������⣬������Ƭ���ԣ�����������Ƭ��Ե(���ϱ�Ϊ��ɫ)��������΢��ë�����ë�����ڻ�ɫ������5(��Ѯ)-7�£�����6-8�¡�

*/
