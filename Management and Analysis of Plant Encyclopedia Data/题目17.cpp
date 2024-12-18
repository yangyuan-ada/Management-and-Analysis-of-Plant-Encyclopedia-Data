/*
��������
����Ҫ��ֲ����п�ʡ��ֲʱ�����ѵĳɱ�������ֲ���·�̳���ϢϢ��أ������ݲ���������Ȼ������ض�ֲ��������Ӱ�죩��
�û�����ͨ������ֲ�����ƺʹ���ֲ��Ŀ�ĵأ��õ������ֲ����Ҫ���ѵ����·����
���У�����ֲ��Ŀ��ʡ�������и�ֲ��ķֲ������������ʡ���Ѵ��ڣ�������ֲ����
���������ֲ�ĳ����غ͵ִ�Ŀ��ʡ�����·�����ȡ�

���Ҫ��
����
ֲ�����ƺ���ֲĿ��ʡ��

���
�����غ���ֲ���·������

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
��ľ ����
��ľ �½�
��ľ �Ĵ�
��ɫ��Ѫ�� �㶫
0
Ԥ�������
���� 1255
�Ĵ� 2838
��ʡ���Ѵ��ڣ�������ֲ
���� 1517

��ɫ��Ѫ�� ����
��ɫ��Ѫ�� �Ĵ�
��ɫ��Ѫ�� ���� 
��ɫ��Ѫ�� �½�
0 
*/

#include<bits/stdc++.h>
#define MVNum 34                        //��󶥵���
#define ERROR 0
int inf=0x7fffffff;
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

typedef struct
{
    string vexs[MVNum];               	//�����
    int arcs[MVNum][MVNum];            	//�ڽӾ���
    int vexnum;                        	//ͼ���ܶ�����
    int arcnum;                        	//ͼ���ܱ���
}Graph;

int LocateVex(Graph G,string u)
{//�����򷵻�u�ڶ�����е��±꣬���򷵻�ERROR
    int i;
    for(i=0;i<MVNum;++i)
    {
        if(u==G.vexs[i])
        {
            return i;
        }
    }
    return ERROR;
}

string OrigialVex(Graph G,int u)
{//�����򷵻ض�������±�Ϊu��Ԫ��
    if(u>=0&&u<=MVNum)
    {
        return G.vexs[u];
    }
}

void InitGraph(Graph &G){
    int i,j;
	G.vexnum=34;    //34��ʡ��������λ
	string place[]={"����","�Ϻ�","���","����","���ɹ�","����","����","����","�½�","���","����","�ӱ�","ɽ��","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","�Ĵ�","����","����","����","����","�ຣ","̨��"};

    for(i=0;i<G.vexnum;i++)
	{
		G.vexs[i]=place[i];
	}

	for(i=0;i<G.vexnum;i++)
    {
		for(j=0;j<G.vexnum;j++)
		{
			if(i==j)
            {
                G.arcs[i][j]=0;
            }
			else
            {
                G.arcs[i][j]=inf;   //ʹ����������ڽӾ���
            }
		}
	}
}

void CreateGraph(Graph &G,string filename)
{//�����ڽӾ����ʾ������distance.txt����������ͼG
 //��distance.txtʱҪʹ��filename����
	ifstream infile;
	infile.open(filename.c_str());
	string line;

	while (getline(infile,line))
	{
	    string s;
		stringstream ss(line);

		int flag=0;
		int v1,v2,w;

		while (getline(ss,s,'#'))
		{
			if (flag==0)
            {
				v1=LocateVex(G,s);  //ȷ�����
			}
			if (flag==1)
			{
				v2=LocateVex(G,s);  //ȷ�����
			}
			if (flag==2)
			{
				w=atoi(s.c_str());
				G.arcs[v1][v2]=G.arcs[v2][v1]=w;    //ȷ��Ȩֵ
			}
			flag++;
		}
	}
	infile.close();
	return;
}

int Dijkstra(Graph G,string v1,string v2)
{//����Dijkstra�㷨��v1��v2�����·��������·������
    int i,j,m,n;
    int st=LocateVex(G,v1);
    int ed=LocateVex(G,v2);
	vector<int> dis(G.vexnum),visited(G.vexnum);

	//��ʼ��dis����,���㵽�����·��
	for(i=0;i<G.vexnum;i++)
    {
		dis[i]=G.arcs[st][i];
	}

	//��ʼ��visited����,�Ѿ��������ĵ�
	for(i=0;i<G.vexnum;i++)
	{
	    visited[i]=0;
	}
	visited[st]=1;

	for(i=0;i<G.vexnum-1;i++)
    {
		int min=inf;    //�ҵ�δ��ǵ��е���Сֵ

		for(j=0;j<G.vexnum;j++)
		{
			if(visited[j]==0&&dis[j]<min)
            {
				min=dis[j];
				m=j;
			}
		}
		visited[m] = 1;

		for(n=0;n<G.vexnum;n++)
		{
			if(G.arcs[m][n]<inf)
			{
				if(dis[n]>dis[m]+G.arcs[m][n])
                {
                    dis[n]=dis[m]+G.arcs[m][n]; //�����滻���·��
                }
			}
		}
	}
	return dis[ed];
}

int GetDistribution(string name,string distribution[],string filename)
{//ʹ��filename��ȡplant.txt�ļ�
 //���ݴ����ֲ�������õ�ֲ��ֲ���distribution�������طֲ�������
	ifstream readfile;
	readfile.open(filename.c_str());
	string line;

	while(getline(readfile,line))
	{
		Plant temp;
		int placenum;
		int same,flag,sum;

		same=0;
		flag=0;
		sum=0;

		string s;
		stringstream sall(line);

		while(getline(sall,s,'#'))
		{
			if(flag==0&&s==name)
			{
				same=1;
			}
			if(flag==1)
			{
			    sum++;
			}
			if(flag==2&&same==1)
			{
				placenum=0;
				string place;
				stringstream splace(s);

				while(getline(splace,place,'@'))
				{
					distribution[placenum] = place;
					placenum++;
				}
				return placenum;
			}
			if(flag==3)
			{
			    sum++;
			}
			flag++;
		}
	}
	readfile.close();
}

int main()
{
    string name,place;      //ֲ������name��Ŀ��ʡ��place
    Graph G;
    InitGraph(G);
    CreateGraph(G,"distance.txt");	//·�����Ϊ�Լ��ı���·��
    while(cin>>name>>place){
    	if(name=="0"&&place=="0")
    		break;
    	string distribution[34];
		int placenum=GetDistribution(name,distribution,"plant.txt");
		int min_d=99999;
		string start_place;
		int flag=1;
    	for(int i=0;i<placenum;i++){
    		if(distribution[i]==place){
    			cout<<"��ʡ���Ѵ��ڣ�������ֲ"<<endl;
    			flag=0;break;
    		}
    		//����Dijkstra�㷨��v1��v2�����·��������·������
    		int d=Dijkstra(G,distribution[i],place);
    		if(d<min_d){
    			min_d=d;
    			start_place=distribution[i];
    		}
    	}
    	if(flag==1)
    		cout<<start_place<<" "<<min_d<<endl;
	}
    return 0;
}

