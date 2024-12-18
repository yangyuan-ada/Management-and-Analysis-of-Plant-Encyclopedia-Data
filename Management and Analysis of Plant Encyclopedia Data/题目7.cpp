#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ����
	string name;										//����
	string sname;										//ѧ��
	string place[100];									//�ֲ���
	string detail;										//��������
};
typedef struct BSTNode{									//����������
   Plant data;
   struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
int Level=0;  //����ȫ�����Ĳ���ܺ�

void InitBSTree(BSTree &T)
{//������������ʼ��
    T=NULL;
}

void BSTreeInsert(BSTree &T,Plant temp)
{
    Level++;    //ͨ���ݹ�������
    if(T==NULL)
    {
        BSTree S;
        S=new BSTNode;
        S->data=temp;
        S->lchild=S->rchild=NULL;
        T=S;
    }
    else if(temp.sname<T->data.sname)
    {
        BSTreeInsert(T->lchild,temp);
    }
    else if(temp.sname>T->data.sname)
    {
        BSTreeInsert(T->rchild,temp);
    }
}

int ReadFile(BSTree &T,string filename)
{//��ȡplant.txt�ļ�������BSTreeInsert������ÿ��ֲ�����ݲ������������
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
        BSTreeInsert(T,temp);
        plantnum++;
    }
    return plantnum;
}

void InOrderTraverse(BSTree T)
{//�������������T�ĵݹ��㷨
	if(T)
    {
        InOrderTraverse(T->lchild);
        cout<<T->data.sname;
        InOrderTraverse(T->rchild);
    }
}

BSTree SearchBST(BSTree T,string key)
{//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳֲ��ѧ������key������Ԫ��
//�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
	if(!T||key==T->data.sname)
        return T;
	else if(key<T->data.sname)
        return SearchBST(T->lchild,key);
	else
        return SearchBST(T->rchild,key);
}

double ASL_BSTree(BSTree T,int count)
{//���ػ��ڶ������������ҵ�ASL
    //ͨ������ÿһ��������ڲ���֮�Ͳ������ܵĽ�����
    double asl;
    double spot;
    spot=6490.0;
    asl=Level/spot;

    return asl;
}

int main(){
	BSTree T;
	InitBSTree(T);
	int count=0;
	string filename="plant.txt";
	count=ReadFile(T,filename);
//	InOrderTraverse(T);									//��������������������Ƿ񴴽��ɹ�
	string sname;										//����Ҫ���ҵ�ֲ��ѧ��
	getline(cin,sname);
	BSTNode *t=SearchBST(T,sname);
	if(t!=NULL){
		cout<<"���ҳɹ���"<<endl;
		cout<<"���ƣ�"<<t->data.name<<endl;
		cout<<"�ֲ��أ�" ;
		for(int j=0;j<100;j++)
			if(t->data.place[j]!="")
				cout<<t->data.place[j]<<" ";
		cout<<endl;
		cout<<"����������"<<t->data.detail<<endl;
		cout<<"ƽ�����ҳ���ASLΪ��"<<fixed<<setprecision(2)<<ASL_BSTree(T,count)<<endl;
	}else{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	return 0;
}

/*
��������
��plant.txt�ж�ȡֲ��Ļ�����Ϣ��ʵ�ֻ��ڶ����������Ĳ��ҡ�

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
ƽ�����ҳ���ASLΪ��35.98

�������룺
Pelargonium hortorum
Ԥ�������
����ʧ�ܣ�

*/
