#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ����
	string name;										//����
	string sname;										//ѧ��
	string place[100];									//�ֲ���
	string detail;										//��������
};

typedef struct{            								//˳���
	Plant *plant;
	int length;
}SqList;

void InitList(SqList &L)
{//˳����ʼ��
	L.plant=new Plant[10000];
    if(!L.plant)
    {
        exit(-2);
    }
    L.length=0;
    return;
}

void ListInsert(SqList &L,int i,Plant p)
{//��˳���L�е�i��λ�ò����µ�ֲ��p
    L.plant[i]=p;
    return;
}

void ReadFile(SqList &L,string filename)
{//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳���
    ifstream readfile;
    readfile.open(filename.c_str());

    string line;
    L.length=0;
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
        ListInsert(L,L.length++,temp);
    }
    readfile.close();
}

void Sort_Seq(SqList L)
{//����ֲ��ѧ����˳���L��С�����������
    int i,j;
    Plant temp;
    for(i=0;i<L.length-1;i++)
    {
        for(j=0;j<L.length-1-i;j++)
        {
            if(L.plant[j].sname>L.plant[j+1].sname)
            {
                temp=L.plant[j];
                L.plant[j]=L.plant[j+1];
                L.plant[j+1]=temp;
            }
        }
    }
}

int Search_Bin(SqList L,string key)
{//��˳���L���۰����ֲ��ѧ������key������Ԫ��
//���ҵ����򷵻ظ�Ԫ���ڱ��е��±꣬���򷵻�-1
	int low,high,mid;
	low=0;
	high=L.length-1;

	while(low<=high)
    {
        mid=(low+high)/2;

        if(L.plant[mid].sname==key)
        {
            return mid;
        }
        else if(L.plant[mid].sname>key)
        {
            high=mid-1;
        }
        else if(L.plant[mid].sname<key)
        {
            low=mid+1;
        }
    }

    return -1;
}

double ASL_Bin(SqList L)
{//���ػ���˳�����۰���ҵ�ASL
	int i;
	i=1;
	double count;
    count=0;
    double asl;

    //ͨ��ѭ�������ķ���һ��һ�����
	while(pow(2,i)-1<L.length)
    {
        count=count+pow(2,i-1)*i;
        i++;
    }
    count=count+(L.length-(pow(2,i-1)-1))*i;

    asl=count/L.length;
    return asl;
}

int main(){
	SqList L;
	InitList(L);
	string filename="plant.txt";
	ReadFile(L,filename);
	Sort_Seq(L);										
	string sname;										//����Ҫ���ҵ�ֲ������ 
	getline(cin,sname);
	int flag=Search_Bin(L,sname);
	if(flag!=-1){
		cout<<"���ҳɹ���"<<endl;
		cout<<"���ƣ�"<<L.plant[flag].name<<endl;
		cout<<"�ֲ��أ�" ;
		for(int j=0;j<100;j++)
			if(L.plant[flag].place[j]!="")
				cout<<L.plant[flag].place[j]<<" ";
		cout<<endl; 
		cout<<"����������"<<L.plant[flag].detail<<endl;
		cout<<"ƽ�����ҳ���ASLΪ��"<<fixed<<setprecision(2)<<ASL_Bin(L)<<endl;
	}else{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	return 0;
}

/*
��������
��plant.txt�ж�ȡֲ��Ļ�����Ϣ��ʵ�ֻ���˳�����۰���ҡ�

���Ҫ��
������ʾ�����Ҳ�༭��������룬����ֲ��ѧ���������ҳɹ��������ֲ���Ӧ�Ļ�����Ϣ�����ơ��ֲ��ء�������������
ͬʱ��������ҳɹ�ʱ��ƽ�����ҳ���ASL���������������ʧ�ܣ�����

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
Gentiana omeiensis
Ԥ�������
���ҳɹ���
���ƣ���ü����
�ֲ��أ��Ĵ�
�����������������ݱ�����30-40���ף��������ں�ɫ����Ĥ��Ҷ�ʰ�Χ�������������쳤��ƽ�Ի�б�죬�߶��������ʵ������֦2-4��������������1-3��Ӫ��֦��1����֦����ֱ֦��������ɫ����ʱ�Ϻ�ɫ���пգ���Բ�Σ��⻬��Ҷ�󲿷ֻ���������Բ�λ���Բ״�����Σ���5.5-12���ף���1-1.5���ף��ȶ˶ۣ�����������Ҷ��3��������������ԣ�����������ͻ��Ҷ��Ĥ�ʣ���4-8���ף�����Ҷ�٣�2-4�ԣ����Σ�ϡ����Բ�Σ���4-6���ף���1.5-2���ף��ȶ˶ۣ�����������Ҷ��1-3��������������ԣ���������ͻ��Ҷ����1-4.5���ף������ϲ�Ҷ��С�������̡������������������ϲ�ҶҸ�г���ɡ״��ϡ�����²���֦���г��ܻ�������С���������������Σ���11-13���ף����泣����ɫ����Ͳ���ʣ�һ�࿪�ѣ��ʷ����״����ԵĤ�ʣ���ݼ�С�����Σ���1-1.5���ף���ȱ�������Σ�������ɫ������ɫ���ƺͰߵ㣬Ͳ״���Σ���3.5-4���ף���Ƭ���Σ���4.5-5.5���ף��ȶ�Բ�λ�ۣ��ϰ벿ȫԵ���°벿�в�����ϸ�ݣ���ƫб�����λ������Σ���1-1.5���ף��ȶ˼��⣬��Ե�в�����ϸ�ݣ����������ڹ�Ͳ�²������룬��˿��״���Σ���13-16���ף���ҩ����Բ�Σ���3-3.5���ף��ӷ���״�����Σ���10-13���ף����˽���������10-13���ף������̶��֣���2-2.5���ף���ͷС��2�ѣ���Ƭ��Բ�Ρ������ڲأ�����Բ�Σ���1.3-1.5���ף����˶ۣ�������1-2���ף����ӻƺ�ɫ���й��󣬾�Բ�Σ���1-1.2���ף�����ߺ���״��϶��������7-9�¡�
ƽ�����ҳ���ASLΪ��11.74

Hortorum pelargonium
�������룺
Pelargonium hortorum
Ԥ�������
����ʧ�ܣ�
*/
