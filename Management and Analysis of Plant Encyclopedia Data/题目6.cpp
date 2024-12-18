#include<bits/stdc++.h>
using namespace std;
struct Plant{											//植物信息定义
	string name;										//名称
	string sname;										//学名
	string place[100];									//分布地
	string detail;										//详情描述
};

typedef struct{            								//顺序表
	Plant *plant;
	int length;
}SqList;

void InitList(SqList &L)
{//顺序表初始化
	L.plant=new Plant[10000];
    if(!L.plant)
    {
        exit(-2);
    }
    L.length=0;
    return;
}

void ListInsert(SqList &L,int i,Plant p)
{//在顺序表L中第i个位置插入新的植物p
    L.plant[i]=p;
    return;
}

void ReadFile(SqList &L,string filename)
{//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表
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
{//根据植物学名对顺序表L由小到大进行排序
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
{//在顺序表L中折半查找植物学名等于key的数据元素
//若找到，则返回该元素在表中的下标，否则返回-1
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
{//返回基于顺序表的折半查找的ASL
	int i;
	i=1;
	double count;
    count=0;
    double asl;

    //通过循环迭代的方法一层一层计算
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
	string sname;										//输入要查找的植物名称 
	getline(cin,sname);
	int flag=Search_Bin(L,sname);
	if(flag!=-1){
		cout<<"查找成功！"<<endl;
		cout<<"名称："<<L.plant[flag].name<<endl;
		cout<<"分布地：" ;
		for(int j=0;j<100;j++)
			if(L.plant[flag].place[j]!="")
				cout<<L.plant[flag].place[j]<<" ";
		cout<<endl; 
		cout<<"详情描述："<<L.plant[flag].detail<<endl;
		cout<<"平均查找长度ASL为："<<fixed<<setprecision(2)<<ASL_Bin(L)<<endl;
	}else{
		cout<<"查找失败！"<<endl;
	}
	return 0;
}

/*
任务描述
从plant.txt中读取植物的基本信息，实现基于顺序表的折半查找。

编程要求
根据提示，在右侧编辑器补充代码，输入植物学名，若查找成功，输出该植物对应的基本信息（名称、分布地、详情描述），
同时，输出查找成功时的平均查找长度ASL；否则，输出“查找失败！”。

测试说明
平台会对你编写的代码进行测试：

测试输入：
Gentiana omeiensis
预期输出：
查找成功！
名称：峨眉龙胆
分布地：四川
详情描述：多年生草本，高30-40厘米，基部被黑褐色枯老膜质叶鞘包围。根茎短缩或伸长，平卧或斜伸，具多数略肉质的须根。枝2-4个丛生，其中有1-3个营养枝和1个花枝；花枝直立，黄绿色或有时紫红色，中空，近圆形，光滑。叶大部分基生，狭椭圆形或椭圆状披针形，长5.5-12厘米，宽1-1.5厘米，先端钝，基部渐狭，叶脉3条，在两面均明显，并在下面稍突起，叶柄膜质，长4-8厘米；茎生叶少，2-4对，匙形，稀狭椭圆形，长4-6厘米，宽1.5-2厘米，先端钝，基部渐狭，叶脉1-3条，在两面均明显，并在下面突起，叶柄长1-4.5厘米，愈向茎上部叶愈小，柄愈短。花多数，顶生和生上部叶腋中呈轮伞状，稀花序下部分枝，有长总花梗，无小花梗；花萼狭钟形，长11-13毫米，外面常带紫色，萼筒草质，一侧开裂，呈佛焰苞状，边缘膜质，萼齿极小，钻形，长1-1.5毫米，弯缺狭，截形；花冠蓝色，无深色条纹和斑点，筒状钟形，长3.5-4厘米，裂片卵形，长4.5-5.5毫米，先端圆形或钝，上半部全缘，下半部有不整齐细齿，褶偏斜，截形或三角形，长1-1.5毫米，先端急尖，边缘有不整齐细齿；雄蕊着生于冠筒下部，整齐，花丝线状钻形，长13-16毫米，花药狭矩圆形，长3-3.5毫米；子房线状披针形，长10-13毫米，两端渐狭，柄长10-13毫米，花柱短而粗，长2-2.5毫米，柱头小，2裂，裂片半圆形。蒴果内藏，狭椭圆形，长1.3-1.5厘米，两端钝，柄长至1-2厘米；种子黄褐色，有光泽，矩圆形，长1-1.2毫米，表面具海绵状网隙。花果期7-9月。
平均查找长度ASL为：11.74

Hortorum pelargonium
测试输入：
Pelargonium hortorum
预期输出：
查找失败！
*/
