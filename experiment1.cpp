#include<bits/stdc++.h>

using namespace std;

const int Pcount = 7;
const int Runtime = 1;

enum Status{
    RUN, WAIT, FIN
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
    ~ProcessControlBlock()
    {}

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
            switch (this->alg)
            {
                case FB:
                    this->fb();
                    break;
        
                default:
                    this->pri();
                    break;
            }
        }
        this->PCD_show();
    }
    void PCD_show()
    {
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
            cout.width(5);
            cout << PCB_Data[i]->ID;
        }
        cout<<endl;
        cout<<"PRIORITY//TURNTIME"<<"            ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout.width(5);
            cout << PCB_Data[i]->Priority;
        }
        cout<<endl;
        cout<<"CPUTIME"<<"                       ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout.width(5);
            cout << PCB_Data[i]->Runtime;
        }
        cout<<endl;
        cout<<"ALLTIME"<<"                       ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout.width(5);
            cout << PCB_Data[i]->Totaltime;
        }
        cout<<endl;
        cout<<"STATE"<<"                         ";
        for(int i = 1; i <= Pcount; i++)
        {
            cout.width(5);
            if(PCB_Data[i]->Pstatus == RUN)
                cout << "R";
            else if(PCB_Data[i]->Pstatus == WAIT)
                cout << "W";
            else
                cout << "F";
        }
        cout << endl;
    }
    void Process_push(int pcd_id)
    {
        if(this->Head == nullptr)
            this->Head = this->Tail = new Node(pcd_id, Head);
        else if(this->PCB_Data[pcd_id]->Priority < this->PCB_Data[Head->pcb_id]->Priority)
            this->Head = new Node(pcd_id, Head);
        else
        {
            Node* ptr = this->Head;
            while(ptr->next != nullptr)
            {
                int next_id = ptr->next->pcb_id;
                if(this->PCB_Data[pcd_id]->Priority < this->PCB_Data[next_id]->Priority)
                    break;
                ptr = ptr->next;
            }
            ptr->next = new Node(pcd_id, ptr->next);
            if(ptr == this->Tail)
                this->Tail = this->Tail->next;
        }
    }
    
    static bool cmp(PCB* a, PCB* b)
    {
        return a->Priority < b->Priority;
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
            PCB_Data[Run]->Pstatus = RUN;
            Head = Tail = new Node(2);
            for(int i = 3; i <= Pcount; i++)
                Tail = Tail->next = new Node(i);
            break;
        
        default:
            vector<PCB*> sort_arry(PCB_Data);
            sort(sort_arry.begin()+1, sort_arry.end(), cmp);
            Run = sort_arry[1]->ID;
            PCB_Data[Run]->Pstatus = RUN;
            Head = Tail = new Node(sort_arry[2]->ID);
            for(int i = 3; i <= Pcount; i++)
                Tail = Tail->next = new Node(sort_arry[i]->ID);
            break;
        }
    }    
    ~pcb_list()
    {
        while(Head != nullptr)
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

    void fb()
    {
        PCB* running_pcb = this->PCB_Data[Run];
        running_pcb->Runtime += running_pcb->Priority * Runtime;
        if(running_pcb->Runtime >= running_pcb->Totaltime)
        {
            running_pcb->Pstatus = FIN;
            this->Run = this->Head == nullptr ? -1 : this->Head->pcb_id;
            if(this->Run != -1)
            {
                this->PCB_Data[Run]->Pstatus = RUN;
                Node* next = Head->next;
                delete Head;
                Head = next;
            }
        }
        else
        {
            running_pcb->Pstatus = WAIT;
            running_pcb->Priority += 1;
            this->Process_push(Run);
            this->Run = this->Head->pcb_id;
            this->PCB_Data[Run]->Pstatus = RUN;
            Node* next = Head->next;
            delete Head;
            Head = next;
        }
    }
    void pri()
    {
        PCB* running_pcb = this->PCB_Data[Run];
        running_pcb->Runtime += Runtime;
        if(running_pcb->Runtime >= running_pcb->Totaltime)
        {
            running_pcb->Pstatus = FIN;
            this->Run = this->Head == nullptr ? -1 : this->Head->pcb_id;
            if(this->Run != -1)
            {
                this->PCB_Data[Run]->Pstatus = RUN;
                Node* next = Head->next;
                delete Head;
                Head = next;
            }
        }
        else
        {
            running_pcb->Pstatus = WAIT;
            running_pcb->Priority += 3;
            this->Process_push(Run);
            this->Run = this->Head->pcb_id;
            this->PCB_Data[Run]->Pstatus = RUN;
            Node* next = Head->next;
            delete Head;
            Head = next;
        }
    }
};

int main()
{
    pcb_list a(FB);
    a.ProcessRun();
    return 0;
}