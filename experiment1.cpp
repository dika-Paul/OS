#include<bits/stdc++.h>

using namespace std;

const int Pcount = 5;

enum Status{
    RUN, WAIT
};
enum Alg{
    FB, PRI
};

typedef class ProcessControlBlock{
public:
    friend class pcb_list;
    ProcessControlBlock()
    {}
    ProcessControlBlock(int n, Alg choice)
        :ID(n),
        Runtime(0),
        Totaltime(rand() % 10 + 1),
        Pstatus(WAIT)
    {
        switch (choice)
        {
        case FB:
            Priority = 1;
            break;
        
        default:
            Priority = rand() % Pcount + 1;
            break;
        }
    }
    ~ProcessControlBlock();

private:
    int ID;
    int Priority;
    int Runtime;
    int Totaltime;
    Status Pstatus;
}PCB;

struct Node{
    int pcb_id;
    Node* next;
    Node(int id, Node* ptr = nullptr)
        :pcb_id(id),
        next(ptr)
    {}
    ~Node()
    {}
};

class pcb_list{
public:
    void ProcessRun()
    {
        while(Run  != -1)
        {
            this->PCD_show();
            this->run();
        }
    }
    void PCD_show()
    {
        cout.width(3);
        cout<<"===================================================================="<<endl;
        cout<<"RUNNING PROC.                        "<<"WAITING QUEUE"<<endl;
        cout<<"                                   ";
        for(Node* ptr = this->Head; ptr != nullptr; ptr = ptr->next)
            cout<<ptr->pcb_id<<"    ";
        cout<<endl;
        cout<<"===================================================================="<<endl;
        cout<<"ID"<<"                            ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout << PCB_Data[i]->ID <<"    ";
        }
        cout<<endl;
        cout<<"PRIORITY//TURNTIME"<<"            ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout << PCB_Data[i]->Priority<<"    ";
        }
        cout<<endl;
        cout<<"CPUTIME"<<"                       ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout << PCB_Data[i]->Runtime<<"    ";
        }
        cout<<endl;
        cout<<"ALLTIME"<<"                       ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout << PCB_Data[i]->Totaltime<<"    ";
        }
        cout<<endl;
        cout<<"STATE"<<"                         ";
        for(int i = 1; i <= Pcount; i++)
        {
            if(PCB_Data[i]->Pstatus == RUN)
                cout << "R" <<"    ";
            else
                cout << "W" <<"    ";
        }
    }

    pcb_list(Alg choice)
        :Run(0),
        Head(nullptr),
        Tail(nullptr),
        PCB_Data(vector<PCB*>(1, new PCB())),
        alg(choice)
    {
        for(int i = 1; i <= Pcount; i++)
            PCB_Data.push_back(new PCB(i, choice));
        switch (alg)
        {
        case FB:
            Run = 1;
            PCB_Data[1]->Pstatus = RUN;
            Head = Tail = new Node(2);
            for(int i = 3; i <= Pcount; i++)
                Tail = Tail->next = new Node(i);
            break;
        
        default:
            break;
        }
    }    
    ~pcb_list()
    {
        while(Head->next != nullptr)
        {
            Node* next = Head->next;
            delete Head;
            Head = next;
        }
        while(!PCB_Data.empty())
        {
            PCB* temp = *PCB_Data.begin();
            PCB_Data.erase(PCB_Data.begin());
            delete temp;
        }
    }

private:
    int Run;
    Node* Head;
    Node* Tail;
    vector<PCB*> PCB_Data;
    Alg alg;

    void run();
    void fb();
    void pri();
};

int main()
{
    return 0;
}