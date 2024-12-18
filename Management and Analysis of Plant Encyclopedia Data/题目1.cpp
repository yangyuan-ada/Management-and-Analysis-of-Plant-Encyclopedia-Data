#include<bits/stdc++.h>
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
    Plant data;    	   //结点的数据域
    struct LNode *next; //指针域
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{//从文件中读取数据，存入链表L中
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
{//判断该植物名称name是否存在于链表中
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
{//增加植物信息，输入植物的名称、学名、分布地和详情描述信息，将该植物的基本信息添加到plant.txt中的最后
 //如果该植物名称存在于plant.txt中，返回false，否则，返回true
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

        //读取结点的信息
        q->data.name=addname;
        getline(cin,q->data.sname);
        cin>>n;
        for(j=0;j<n;j++)
        {
            cin>>q->data.place[j];
        }
        cin>>q->data.detail;

        //将结点插入链表
        LinkList p;
        p=L->next;

        //重新将修改后的链表内容写入文件
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
{//构造一个空的单链表L
    L=new LNode;
    L->next=NULL;
}

void Check(string filename)
{//读取文件最后一行内容，即新增植物信息
	ifstream infile;
	infile.open(filename.c_str());    						//打开文件
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
	//读plant.txt文件
	ReadFile(L,filename);
	if(InsertPlant(L,filename))
	   Check(filename);
	else
	   cout<<"增加失败\n";
	return 0;
}

/*
任务描述
本关任务：已知plant.txt的路径为"data_edit/plant.txt"，从plant.txt中读取植物的基本信息，创建一个植物信息的链表，基于该链表，实现植物基本信息的增加功能。

编程要求
根据提示，在右侧编辑器补充代码，输入植物的名称、学名、分布地和详情描述信息，将该植物的基本信息添加到plant.txt中的最后。
（注：由于植物名称是唯一的，因此在增加时需要判断该植物名称是否存在于plant.txt中，若存在，则输出“增加失败”；输入分布地时，先输入分布地个数，再依次输入分布地）

测试说明
平台会对你编写的代码进行测试：

测试输入：
蒲公英
Taraxacum mongolicum
2
黑龙江
吉林
多年生草本。根略呈圆锥状，弯曲，长4～10厘米，表面棕褐色，皱缩，根头部有棕色或黄白色的毛茸。叶成倒卵状披针形、倒披针形或长圆状披针形，长4～20厘米，宽1-5厘米，先端钝或急尖，边缘有时具波状齿或羽状深裂，有时倒向羽状深裂或大头羽状深裂，顶端裂片较大，三角形或三角状戟形，全缘或具齿，每侧裂片3～5片，裂片三角形或三角状披针形，通常具齿，平展或倒向，裂片间常夹生小齿，基部渐狭成叶柄，叶柄及主脉常带红紫色，疏被蛛丝状白色柔毛或几无毛。

芍药
Paeonia lactiflora Pall
3
江苏
浙江
安徽
多年生草本植物，根粗壮，分枝黑褐色。茎高40-70厘米，无毛。下部茎生叶为二回三出复叶，上部茎生叶为三出复叶；小叶狭卵形，椭圆形或披针形。
 
测试输出：
蒲公英#Taraxacum mongolicum#黑龙江@吉林#多年生草本。根略呈圆锥状，弯曲，长4～10厘米，表面棕褐色，皱缩，根头部有棕色或黄白色的毛茸。叶成倒卵状披针形、倒披针形或长圆状披针形，长4～20厘米，宽1-5厘米，先端钝或急尖，边缘有时具波状齿或羽状深裂，有时倒向羽状深裂或大头羽状深裂，顶端裂片较大，三角形或三角状戟形，全缘或具齿，每侧裂片3～5片，裂片三角形或三角状披针形，通常具齿，平展或倒向，裂片间常夹生小齿，基部渐狭成叶柄，叶柄及主脉常带红紫色，疏被蛛丝状白色柔毛或几无毛。

测试输入：
钝裂银莲花
Anemone obtusiloba
2
西藏
四川
植株高10-30厘米。基生叶7-15，有长柄，多少密被短柔毛；叶片肾状五角形或宽卵形，长1.2-3厘米，宽1.7-5.5厘米，基部心形，三全裂或偶而三裂近基部，中全裂片菱状倒卵形，二回浅裂，侧全裂片与中全裂片近等大或稍小，各回裂片互相多少邻接或稍覆压，脉近平；叶柄3-18厘米。花葶2-5，有开展的柔毛；苞片3，无柄，稍不等大，宽菱形或楔形，常三深裂，长1-2厘米，多少密被柔毛；花梗1-2，长1.5-8厘米；萼片5(-8)，白色，蓝色或黄色，倒卵形或狭倒卵形，长0.8-1.2厘米，宽5-8毫米，外面有疏毛，雄蕊长约4毫米，花药椭圆形；心皮约8，子房密被柔毛。5月至7月开花。；

测试输出：
增加失败

二色补血草
Limonium bicolor
4
江苏
辽宁
黑龙江
吉林
多年生草本，高20-50厘米，全株(除萼外)无毛。叶基生，偶可花序轴下部1-3节上有叶，花期叶常存在，匙形至长圆状匙形，长3-15厘米，宽0.5-3厘米，先端通常圆或钝，基部渐狭成平扁的柄。花序圆锥状；花序轴单生，或2-5枚各由不同的叶丛中生出，通常有3-4棱角，有时具沟槽，偶可主轴圆柱状，住往自中部以上作数回分枝，末级小枝二棱形；不育枝少(花序受伤害时则下部可生多数不育枝)，通常简单，位于分枝下部或单生于分叉处；穗状花序有柄至无柄，排列在花序分枝的上部至顶端，由3-5(9)个小穗组成；小穗含2-3(5)花(含4-5花时则被第一内苞包裹的1-2花常不开放)；外苞长约2.5-3.5毫米，长圆状宽卵形(草质部呈卵形或长圆形)，第一内苞长约6-6.5毫米；萼长6-7毫米，漏斗状，萼筒径约1毫米，全部或下半部沿脉密被长毛，萼檐初时淡紫红或粉红色，后来变白，宽为花萼全长的一半(3-3.5毫米)，开张幅径与萼的长度相等，裂片宽短而先端通常圆，偶可有一易落的软尖，间生裂片明显，脉不达于裂片顶缘(向上变为无色)，沿脉被微柔毛或变无毛；花冠黄色。花期5(下旬)-7月，果期6-8月。

*/
