/*
��������
����ĳ�ط���һ����ֲ��ʱ����Ҫ��ʱ��������׵ر������׵���ֲ�Ĺ����У���·�̹�����ֲ������������;��������
�û�������ֲ�﷢�ֵء���ֲĿ�ĵؼ���ֲ���ܽ��ܵ����·�̣�ͨ����ʡ��ͼ���б�����������п��е�����·����

���Ҫ��
����
��ֲ�﷢�ֵأ���ֲĿ�ĵأ��ɽ��ܵ����·��

���
ȫ�����еļ�·��������������

����˵��
ƽ̨������д�Ĵ�����в��ԣ�

�������룺
���� �Ϻ� 1800
Ԥ�������
���� �ӱ� ɽ�� ���� �Ϻ�
���� ��� �ӱ� ɽ�� ���� �Ϻ�
���� �ӱ� ɽ�� ���� �㽭 �Ϻ�
���� �ӱ� ɽ�� ���� ���� �Ϻ�
���� �ӱ� ���� ���� ���� �Ϻ�

�������룺
���� ���� 4900
Ԥ�������
���� �Ĵ� ���� ���� ���� ����
���� �ຣ ���� ���� ���� ���� ����
���� �Ĵ� ���� ���� ���� ����
���� ���� ���� �㶫 ����
���� �ຣ ���� ���� ���� ���� ���� ����

�㶫 ���� 2400 
*/

#include<bits/stdc++.h>
#define MVNum 34                           //��󶥵���
#define ERROR 0
int inf=0x7fffffff;
using namespace std;

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
	G.vexnum=34;		//34��ʡ��������λ
	string place[]={"����","�Ϻ�","���","����","���ɹ�","����","����","����","�½�","���","����","�ӱ�","ɽ��","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","�Ĵ�","����","����","����","����","�ຣ","̨��"};

	for(int i=0;i<G.vexnum;i++)
    {
		G.vexs[i]=place[i];
	}

	for(i=0;i<MVNum;i++)
	{
		for(j=0;j<MVNum;j++)
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

void CreateGraph(Graph &G, string filename)
{//�����ڽӾ����ʾ������distance.txt����������ͼG
 //��distance.txtʱҪ����filename����
	int distance;

	ifstream infile;
	infile.open(filename.c_str());
	string line;

	while (getline(infile, line))
	{
	    string s;
		stringstream ss(line);

		int flag=0;
		int v1,v2,w;

		while(getline(ss,s,'#'))
		{
			if(flag==0)
            {
				v1=LocateVex(G,s);  //ȷ�����
			}
			if(flag==1) {
				v2=LocateVex(G,s);  //ȷ�����
			}
			if(flag==2) {
				w=atoi(s.c_str());
				G.arcs[v1][v2]=G.arcs[v2][v1]=w;    //ȷ��Ȩֵ
			}
			flag++;
		}
	}
	infile.close();
	return;
}

int path[100]={0};
int visited[100]={0};
int startpoint,endpoint;
int MaxDistance;
int PathNum=0;  //·������
string PathPoint[10000]={}; //·�����

void DFS(Graph G,int PointNum,int NowPoint,int NowDistance)
{
	int i,j;
	//·�����ȵ��ж�
	if (NowDistance>MaxDistance)
    {
		return;
	}
    //����·���Ľ��
	visited[NowPoint]=1;
	path[PointNum++]=NowPoint;

	if(NowPoint==endpoint&&PointNum>=1)
    {
        //�ѵ��յ�ʱ����·������
		PathNum++;
		for(i=0;i<PointNum-1;i++)
		{
			PathPoint[NowDistance].append(OrigialVex(G,path[i]));
			PathPoint[NowDistance].append(" ");
		}
		PathPoint[NowDistance].append(OrigialVex(G,path[PointNum-1]));

	}
	else
    {
        //δ���յ�ʱ���ϵݹ����
		for(j=0;j<MVNum;j++)
		{
			if (j!=NowPoint&&visited[j]==0&&G.arcs[NowPoint][j]!=inf)
            {
				DFS(G,PointNum,j,NowDistance+G.arcs[NowPoint][j]);
			}
		}
	}
    //���ܲ���ʱ������һ���
	visited[NowPoint]=0;
	PointNum--;
}

void FindWay(Graph G,string p1,string p2,int n)
{//�ҵ�p1��p2���г���С��n��·������·�̴�С�������
 //�����õ��ݹ麯����ȫ�ֱ����������ж��岢�������
	startpoint=LocateVex(G,p1);
	endpoint=LocateVex(G,p2);
	MaxDistance=n;

	DFS(G,0,startpoint,0);

	//ѭ�����ȫ��·��
	int i;
	for(i=0;i<10000;i++)
    {
		if(!PathPoint[i].empty())
		{
			cout<<PathPoint[i]<<endl;
		}
	}
}

int main()
{
    string p1,p2;      	//�������p1���յ�p2
    int n;				//�ɽ��ܵ������
    Graph G;
    InitGraph(G);
    CreateGraph(G,"distance.txt");	//·�����Ϊ�Լ��ı���·��
    cin>>p1>>p2>>n;
    FindWay(G,p1,p2,n);
    return 0;
}
