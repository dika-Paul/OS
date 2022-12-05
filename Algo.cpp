#include<bits/stdc++.h>
using namespace std;
const int n=5;
struct pcb
{
    int id,priority,runtime,totaltime;
    char status;
}PCB[n+1];
int link[n+1];
int run,head,tail;
void initprocess()
{
    int i;
    for(int i=1;i<=n;i++)
    {
        PCB[i].id=i;
        PCB[i].priority=rand()%4+1;
        PCB[i].runtime=0;
        PCB[i].totaltime=rand()%9+1;
        PCB[i].status='W';
    }
}
void show()
{
    int i;
    /*cout<<run<<" "<<head<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<"   ";
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<link[i]<<"   ";
    }
    cout<<endl;*/
    cout<<"=========================================================="<<endl;
    cout<<"RUNNING PROC.                        "<<"WAITING QUEUE"<<endl;
    cout<<"                                   ";
    for(int i=head;i!=-1;i=link[i])
    {
        cout<<i<<"    ";
    }
    cout<<endl;
    cout<<"=========================================================="<<endl;
    cout<<"ID"<<"                            ";
    for(int i=1;i<=n;i++)
    {
        cout<<PCB[i].id<<"    ";
    }
    cout<<endl;
    cout<<"PRIORITY//TURNTIME"<<"            ";
    for(int i=1;i<=n;i++)
    {
        cout<<PCB[i].priority<<"    ";
    }
    cout<<endl;
    cout<<"CPUTIME"<<"                       ";
    for(int i=1;i<=n;i++)
    {
        cout<<PCB[i].runtime<<"    ";
    }
    cout<<endl;
    cout<<"ALLTIME"<<"                       ";
    for(int i=1;i<=n;i++)
    {
        cout<<PCB[i].totaltime<<"    ";
    }
    cout<<endl;
    cout<<"STATE"<<"                         ";
    for(int i=1;i<=n;i++)
    {
        cout<<PCB[i].status<<"    ";
    }
    cout<<endl;
    cout<<"NEXT"<<"                          ";
    for(int i=1;i<=n;i++)
    {
        cout<<link[i]<<"    ";
    }
    cout<<endl;
}
void priority()
{
    int i,j,k;
    int sort[n+1];
    initprocess();
    for(int i=1;i<=n;i++)
    {
        sort[i]=i;
    }
    for(int i=1;i<=n;i++)
    {
        for(j=1;j<=n-i;j++)
        {
            if(PCB[sort[j]].priority<PCB[sort[j+1]].priority)
            {
                k=sort[j];sort[j]=sort[j+1];sort[j+1]=k;
            }
        }
    }
    head=sort[1];
    for(int i=1;i<=n;i++)
    {
        link[sort[i]]=sort[i+1];
    }
    tail=sort[n];
    link[tail]=-1;
    run=-1;
    run=head;
    PCB[run].status='R';
    head=link[head];
    while(run!=-1)
    {
        show();
        PCB[run].totaltime--;
        PCB[run].priority-=3;
        PCB[run].runtime++;
        if(PCB[run].totaltime==0)
        {
            PCB[run].status='F';
            run=head;
            if(head!=-1)
            {
                head=link[head];
                PCB[head].status='R';
            }
        }
        else
        {
            if(head!=-1 && PCB[run].priority<PCB[head].priority)
            {
                k=head;
                PCB[run].status='W';
                while(k!=tail && PCB[link[k]].priority>PCB[run].priority)
                {
                    k=link[k];
                }
                if(k==tail)
                {
                    link[k]=run;
                    tail=run;
                    link[run]=-1;
                    run=head;
                    head=link[head];
                    PCB[run].status='R';
                }
                else
                {
                    link[run]=link[k];
                    link[k]=run;
                    run=head;
                    head=link[head];
                    PCB[run].status='R';
                }
            }
        }
    }
    show();
}
void roundrobin()
{
    initprocess();
    int i;
    for(i=1;i<=n;i++)
    {
        link[i]=i+1;
    }
    head=1;
    tail=n;
    link[tail]=-1;
    run=head;
    head=link[head];
    PCB[run].status='R';
    while(run!=-1)
    {
        show();
        PCB[run].totaltime--;
        PCB[run].runtime++;
        if(PCB[run].totaltime==0)
        {
            PCB[run].status='F';
            run=head;
            if(head!=-1)
            {
                head=link[head];
                PCB[head].status='R';
            }
        }
        else
        {
            if(head!=-1 && PCB[run].runtime%PCB[run].priority==0)
            {
                PCB[run].status='W';
                link[tail]=run;
                link[run]=-1;
                tail=run;
                run=head;
                head=link[head];
                PCB[run].status='R';
            }
        }
    }
    show();
}
int main()
{
    while(1)
    {
        cout<<"TYPE THE ALGORTITHM:";
        char str[20];
        cin>>str;
        char *str1="PRIORITY";
        char *str2="ROUNDROBIN";
        if(strcmp(str,str1)==0)
        {
            cout<<"OUTPUT OF "<<str<<endl;
            cout<<"=================================="<<endl;
            priority();
        }
        if(strcmp(str,str2)==0)
        {
            cout<<"OUTPUT OF "<<str<<endl;
            cout<<"=================================="<<endl;
            roundrobin();
        }
        cout<<"SYSTEM FINISHED"<<endl;
        cout<<endl<<endl;
    }
    return 0;
}
