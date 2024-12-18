#include<bits/stdc++.h>
#define m 6600											//ɢ�б�ı�
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
LinkList H[m];                                         	//����ַ��ɢ�б�Ĵ洢��ʾ��m��������

void InitList()
{//�����ʼ��
    int i;
    for(i=0;i<m;i++)
    {
        H[i]=new LNode;
        H[i]->next=NULL;
    }
    return;
}

int Hash(string sname)
{//ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���6599ȡ��
	int i,key,keysum,keylength,Hash; 
	key=0;
	keysum=0;
	keylength=sname.length();
	Hash=0;
	
	for(i=0;i<keylength;i++)
	{
		key=i*i*int(sname[i]);
		keysum+=key;
	}
	
	Hash=keysum%6599;
	return Hash;
}

void ListInsert(Plant p,int &sumCmp)
{//��ɢ�б��в����µ�ֲ��p
//�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
    //ɢ�б��һ�μ���õ���λ��
    int i;
    i=Hash(p.sname);
    LinkList r;
    r=H[i];
    sumCmp++;

    //ɢ�б����õ���λ����������
    while(r->next!=NULL)
    {
        r=r->next;
        sumCmp++;
    }

    LinkList s;
    s=new LNode;
    s->data=p;
    s->next=NULL;

    r->next=s;
    r=r->next;

    return;
}

int ReadFile(int &sumCmp,string filename)
{//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳���
//������ľ���ݵ�����
    ifstream readfile;
    readfile.open(filename.c_str());

    int plantnum;
    plantnum=0;
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
        ListInsert(temp,sumCmp);
        plantnum++;
    }
    readfile.close();
    return plantnum;
}

int SearchHL(string key)
{//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1
    int i;
    i=Hash(key);

    LinkList r;
    r=H[i];

    while(r->next)
    {
        if(r->next->data.sname==key)
        {
            return i;
        }
        r=r->next;
    }

    return -1;
}

double ASL_HL(int sumCmp,int count)
{//���ػ�������ַ����ɢ�в��ҵ�ASL
    //ASL�Ķ������
    double asl;
    asl=1.0*sumCmp/count;

    return asl;
}

int main(){
	InitList();
	string filename="plant.txt";
	int count=0; 										//��¼ֲ�����ݵ�����
	int sumCmp=0;										//�ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL
	count=ReadFile(sumCmp,filename);
	string sname;										//����Ҫ���ҵ�ֲ��ѧ��
	getline(cin,sname);
	int flag=SearchHL(sname);
	if(flag!=-1){
		LinkList p=H[flag]->next;						//���ҳɹ�����pָ������ͷ���
		while(p) {
			if(p->data.sname==sname){					//���������Ϣ
				cout<<"���ҳɹ���"<<endl;
				cout<<"���ƣ�"<<p->data.name<<endl;
				cout<<"�ֲ��أ�" ;
				for(int j=0;j<100;j++)
					if(p->data.place[j]!="")
						cout<<p->data.place[j]<<" ";
				cout<<endl;
				cout<<"����������"<<p->data.detail<<endl;
				cout<<"ƽ�����ҳ���ASLΪ��"<<fixed<<setprecision(2)<<ASL_HL(sumCmp,count)<<endl;
				break;
			}
			p=p->next;
		}

	}else{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	return 0;
}

/*
��������
��plant.txt�ж�ȡֲ��Ļ�����Ϣ��ʵ�ֻ�������ַ����ɢ�в��ҡ�

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
ƽ�����ҳ���ASLΪ��1.51

�������룺
Pelargonium hortorum
Ԥ�������
����ʧ�ܣ�
*/
