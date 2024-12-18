/*
任务描述
当在某地发现一株新植物时，需要及时对其进行易地保护。易地移植的过程中，若路程过长，植物容易在运载途中死亡。
用户输入新植物发现地、移植目的地及该植物能接受的最大路程，通过对省份图进行遍历，输出所有可行的运输路径。

编程要求
输入
新植物发现地，移植目的地，可接受的最大路程

输出
全部可行的简单路径（不包含环）

测试说明
平台会对你编写的代码进行测试：

测试输入：
北京 上海 1800
预期输出：
北京 河北 山东 江苏 上海
北京 天津 河北 山东 江苏 上海
北京 河北 山东 江苏 浙江 上海
北京 河北 山东 安徽 江苏 上海
北京 河北 河南 安徽 江苏 上海

测试输入：
西藏 福建 4900
预期输出：
西藏 四川 重庆 湖北 江西 福建
西藏 青海 甘肃 陕西 湖北 江西 福建
西藏 四川 陕西 湖北 江西 福建
西藏 云南 广西 广东 福建
西藏 青海 甘肃 陕西 河南 湖北 江西 福建

广东 湖北 2400 
*/

#include<bits/stdc++.h>
#define MVNum 34                           //最大顶点数
#define ERROR 0
int inf=0x7fffffff;
using namespace std;

typedef struct
{
    string vexs[MVNum];               	//顶点表
    int arcs[MVNum][MVNum];            	//邻接矩阵
    int vexnum;                        	//图的总顶点数
    int arcnum;                        	//图的总边数
}Graph;

int LocateVex(Graph G,string u)
{//存在则返回u在顶点表中的下标，否则返回ERROR
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
{//存在则返回顶点表中下标为u的元素
    if(u>=0&&u<=MVNum)
    {
        return G.vexs[u];
    }
}

void InitGraph(Graph &G){
    int i,j;
	G.vexnum=34;		//34个省级行政单位
	string place[]={"北京","上海","天津","重庆","内蒙古","广西","西藏","宁夏","新疆","香港","澳门","河北","山西","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南","陕西","甘肃","青海","台湾"};

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
				G.arcs[i][j]=inf;   //使用无穷大建立邻接矩阵
			}
		}
	}
}

void CreateGraph(Graph &G, string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要调用filename参数
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
				v1=LocateVex(G,s);  //确定结点
			}
			if(flag==1) {
				v2=LocateVex(G,s);  //确定结点
			}
			if(flag==2) {
				w=atoi(s.c_str());
				G.arcs[v1][v2]=G.arcs[v2][v1]=w;    //确定权值
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
int PathNum=0;  //路径数量
string PathPoint[10000]={}; //路径结点

void DFS(Graph G,int PointNum,int NowPoint,int NowDistance)
{
	int i,j;
	//路径长度的判断
	if (NowDistance>MaxDistance)
    {
		return;
	}
    //访问路径的结点
	visited[NowPoint]=1;
	path[PointNum++]=NowPoint;

	if(NowPoint==endpoint&&PointNum>=1)
    {
        //已到终点时不断路径操作
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
        //未到终点时不断递归调用
		for(j=0;j<MVNum;j++)
		{
			if (j!=NowPoint&&visited[j]==0&&G.arcs[NowPoint][j]!=inf)
            {
				DFS(G,PointNum,j,NowDistance+G.arcs[NowPoint][j]);
			}
		}
	}
    //不能操作时返回上一结点
	visited[NowPoint]=0;
	PointNum--;
}

void FindWay(Graph G,string p1,string p2,int n)
{//找到p1到p2所有长度小于n的路径并按路程从小到大输出
 //若需用到递归函数或全局变量等请自行定义并合理调用
	startpoint=LocateVex(G,p1);
	endpoint=LocateVex(G,p2);
	MaxDistance=n;

	DFS(G,0,startpoint,0);

	//循环输出全部路径
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
    string p1,p2;      	//运输起点p1，终点p2
    int n;				//可接受的最长距离
    Graph G;
    InitGraph(G);
    CreateGraph(G,"distance.txt");	//路径需改为自己的本地路径
    cin>>p1>>p2>>n;
    FindWay(G,p1,p2,n);
    return 0;
}
