/*
任务描述
当需要对植物进行跨省移植时，花费的成本与运载植物的路程长度息息相关（这里暂不考虑气候等环境因素对植物生长的影响）。
用户可以通过输入植物名称和待移植的目的地，得到运输该植物需要花费的最短路径。
其中，若移植的目的省份中已有该植物的分布，则输出“该省份已存在，无需移植”；
否则，输出移植的出发地和抵达目的省份最短路径长度。

编程要求
输入
植物名称和移植目的省份

输出
出发地和移植最短路径长度

测试说明
平台会对你编写的代码进行测试：

测试输入：
柏木 北京
柏木 新疆
柏木 四川
二色补血草 广东
0
预期输出：
江苏 1255
四川 2838
该省份已存在，无需移植
江苏 1517

二色补血草 江苏
二色补血草 四川
二色补血草 湖北 
二色补血草 新疆
0 
*/

#include<bits/stdc++.h>
#define MVNum 34                        //最大顶点数
#define ERROR 0
int inf=0x7fffffff;
using namespace std;

struct Plant
{
	//植物信息定义
	string name;										//植物名称
	string sname;										//学名
	string place[100];									//分布地
	string detail;										//详情描述
};

typedef struct LNode
{
    Plant data;    	    //结点的数据域
    struct LNode *next; //指针域
}LNode,*LinkList;

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
	G.vexnum=34;    //34个省级行政单位
	string place[]={"北京","上海","天津","重庆","内蒙古","广西","西藏","宁夏","新疆","香港","澳门","河北","山西","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南","陕西","甘肃","青海","台湾"};

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
                G.arcs[i][j]=inf;   //使用无穷大建立邻接矩阵
            }
		}
	}
}

void CreateGraph(Graph &G,string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要使用filename参数
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
				v1=LocateVex(G,s);  //确定结点
			}
			if (flag==1)
			{
				v2=LocateVex(G,s);  //确定结点
			}
			if (flag==2)
			{
				w=atoi(s.c_str());
				G.arcs[v1][v2]=G.arcs[v2][v1]=w;    //确定权值
			}
			flag++;
		}
	}
	infile.close();
	return;
}

int Dijkstra(Graph G,string v1,string v2)
{//利用Dijkstra算法求v1到v2的最短路径并返回路径长度
    int i,j,m,n;
    int st=LocateVex(G,v1);
    int ed=LocateVex(G,v2);
	vector<int> dis(G.vexnum),visited(G.vexnum);

	//初始化dis数组,顶点到各点的路程
	for(i=0;i<G.vexnum;i++)
    {
		dis[i]=G.arcs[st][i];
	}

	//初始化visited数组,已经被经过的点
	for(i=0;i<G.vexnum;i++)
	{
	    visited[i]=0;
	}
	visited[st]=1;

	for(i=0;i<G.vexnum-1;i++)
    {
		int min=inf;    //找到未标记点中的最小值

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
                    dis[n]=dis[m]+G.arcs[m][n]; //不断替换最短路径
                }
			}
		}
	}
	return dis[ed];
}

int GetDistribution(string name,string distribution[],string filename)
{//使用filename读取plant.txt文件
 //根据传入的植物名，得到植物分布地distribution，并返回分布地数量
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
    string name,place;      //植物名称name和目的省份place
    Graph G;
    InitGraph(G);
    CreateGraph(G,"distance.txt");	//路径需改为自己的本地路径
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
    			cout<<"该省份已存在，无需移植"<<endl;
    			flag=0;break;
    		}
    		//利用Dijkstra算法求v1到v2的最短路径并返回路径长度
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

