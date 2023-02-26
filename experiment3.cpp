#include<bits/stdc++.h>

using namespace std;


int adress[32];//全局变量数组，地址流
int p;//全局变量p是一共有多少地址流


void init()
{//初始化函数,
    int t;
	srand(time(0));//随机产生指令序列
    p=12+rand()%32;
    cout<<"地址流个数 P="<<p<<endl;
	cout<<"随机产生的地址流序列\n";
	for(int i=0,j=0;i<p;i++,j++)
    {
		t=1+rand()%9;
		adress[i]=t;//将随机产生的指令数存入页面流
        printf("a[%d]=%d  ",i,t);
        j=j%5;
        if(i<10) printf(" ");
        if(j==4) printf("\n");
	}
	cout<<endl;
}
void OPT(int n)//FIFO算法，n是M的值
{  
	int e,q=p,m=n-1;
	int flag;
	int flag1;
	int queye=0;
	int leaflink[32];
    memset(leaflink,0,sizeof(leaflink));
	for(int x=0;x<q;x++)
    {
		e=x;
		flag=0;
		for(int i=0;i<n;i++)
        {
			if(leaflink[i]==adress[x])
            {
				flag=1;
				flag1=i;
				printf("有相同\n");
				break;
			}
		}
		if(flag==0)
        {
            int k=0;
            for(int j=0;j<m;j++)
            {//0 1 2
			    leaflink[k]=leaflink[k+1];
                k++;
			}
            leaflink[m]=adress[e];
            if(e>=m)
                queye++;
		}
		if(flag==1)
        {
            int temp[10]={0};
            for(int i=0;i<=m;i++)
                for(int a=e+1;a<q;a++)
                    if(leaflink[i]==adress[a])
                        temp[i]++;
            int index=0;
            for(int i=0;i<m;i++)
            {
                int min=temp[0];
                if(min>temp[i])
                {
                    min=temp[i];
                    index=i;
                }
            }
            int l=leaflink[index];
            leaflink[index]=leaflink[0];
            leaflink[0]=l;
		}
        for(int j=0;j<n;j++)
            printf("leaflink[%d]=%d ",j,leaflink[j]);
        cout<<endl;
    }
	cout<<"M="<<n<<"时FIFO的命中率为："<<(1-((double)queye/p))*100<<"%"<<"    "<<endl;
}

void LRU(int n)//LRU算法
{
	int i;
	int m=n-1;
	int q=p;
	int e;
	int queye=0;
	int flag;
	int flag1;
	int y;
	int leaflink[32];
	memset(leaflink,0,sizeof(leaflink));
	for(int x=0;x<q;x++)
    {
		flag=0;
		e=x;
		for(i=0;i<n;i++)
        {
			if(leaflink[i]==adress[x])
            {
				flag=1;
				flag1=i;
				printf("X=%d,lru[%d] = adress[%d]=%d ,flag= 1\n",x,i,x,adress[x]);
				break;
			}
		}
		if(flag==0)
        {
            int k=0;
			for(int j=0;j<m;j++)
            {//0 1 2
				leaflink[k]=leaflink[k+1];
                k++;
			}
			leaflink[m]=adress[e];
			queye++;
		}
		else if(flag==1)
        {
            y=flag1;
			for(int j=0;j<m;j++)
            {
				leaflink[flag1]=leaflink[flag1+1];
				flag1++;
            }
			leaflink[3]=adress[e];
			printf("发现相同后，改变leaflink[%d]=%d\n",m,leaflink[3]);
        }
		for(int j=0;j<n;j++)
            printf("leaflink[%d]=%d ",j,leaflink[j]);
        cout<<endl;
	}
	cout<<"发生替换次数："<<queye<<endl;
	cout<<"M="<<n<<"时LRU的命中率为："<<(1-((double)queye/p))*100<<"%"<<endl;
}

int main()
{
	init();
	char c;
	printf("请输入选择算法（O:最佳淘汰 L：最近最少使用）：");
	cin>>c;
	if(c=='O')
	    for(int i=3;i<4;i++)
		    OPT(i);
	else if(c=='L')
    {
        for(int i=4;i<5;i++)
        {
		   LRU(i);
		   cout<<endl;
	    }
	}
	return 0;
}
