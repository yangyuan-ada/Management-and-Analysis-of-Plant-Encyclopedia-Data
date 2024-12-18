#include<bits/stdc++.h>
#define m 6600											//ɢ�б�ı�
using namespace std;
struct Plant{											//ֲ����Ϣ����
	string name;										//����
	string sname;										//ѧ��
	string place[100];									//�ֲ���
	string detail;										//��������
};

typedef struct{            								//���ŵ�ַ��ɢ�б�Ĵ洢��ʾ
	Plant *key;
	int length;
}HashTable;

void InitHT(HashTable &HT){
//ɢ�б��ʼ��
    HT.key=new Plant[m];
    if(!HT.key)
    {
        exit(-2);
    }
    HT.length=0;

    return;
}

int H(string sname)
{
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

/*
	int sum=0;
    for(int i=0;i<sname.length();i++){
		sum+=((i)*(i)*int(sname[i]));
	}
	return sum%6599;
*/

void HTInsert(HashTable &HT,Plant p,int &sumCmp){
//��ɢ�б��в����µ�ֲ��p
//�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
    //ɢ�б��һ�μ���õ���λ��
    int i;
    i=H(p.sname);
    sumCmp++;

    //ɢ�б��϶ԱȺ��ƶ��Ĺ���
    while(H(HT.key[i].sname))
    {
        i=(i+1)%6599;
        sumCmp++;
    }

    HT.key[i]=p;
    HT.length++;

    return;
}

void ReadFile(HashTable &HT,int &sumCmp,string filename){
//��ȡplant.txt�ļ�������HT������ÿ��ֲ�����ݲ���ɢ�б�
    ifstream readfile;
    readfile.open(filename.c_str());

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
        HTInsert(HT,temp,sumCmp);
    }
    readfile.close();
}

int SearchHash(HashTable HT,string key){
//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1
    int i;
    i=H(key);

    int num;
    while(HT.key[i].sname!=key)
    {
        if(HT.key[i].sname=="")
        {
            return -1;
        }

        i=(i+1)%6599;
        num++;

        if(num==6599)
        {
            return -1;
        }
    }

    return i;
}

double ASL_HT(HashTable HT,int sumCmp){
//���ػ��ڿ��ŵ�ַ����ɢ�в��ҵ�ASL
    //ASL�Ķ������
    double asl;
    asl=1.0*sumCmp/HT.length;

    return asl;
}

int main(){
	HashTable HT;
	InitHT(HT);
	string filename="plant.txt";
	int sumCmp=0;										//�ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL
	ReadFile(HT,sumCmp,filename);
	string sname;										//����Ҫ���ҵ�ֲ��ѧ��
	getline(cin,sname);
	int flag=SearchHash(HT,sname);
	if(flag!=-1){
		cout<<"���ҳɹ���"<<endl;
		cout<<"���ƣ�"<<HT.key[flag].name<<endl;
		cout<<"�ֲ��أ�" ;
		for(int j=0;j<100;j++)
			if(HT.key[flag].place[j]!="")
				cout<<HT.key[flag].place[j]<<" ";
		cout<<endl;
		cout<<"����������"<<HT.key[flag].detail<<endl;
		cout<<"ƽ�����ҳ���ASLΪ��"<<fixed<<setprecision(2)<<ASL_HT(HT,sumCmp)<<endl;
	}else{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	return 0;
}

/*
��������
��plant.txt�ж�ȡֲ��Ļ�����Ϣ��ʵ�ֻ��ڿ��ŵ�ַ����ɢ�в��ҡ�
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
ƽ�����ҳ���ASLΪ��22.59

�������룺
Pelargonium hortorum
Ԥ�������
����ʧ�ܣ�
*/
