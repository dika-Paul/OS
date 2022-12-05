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
    PCB* pcb;
    Node* next;
    Node(PCB* temp, Node* ptr = nullptr)
        :pcb(temp),
        next(ptr)
    {}
    ~Node()
    {
        delete this->pcb;
    }
};

class pcb_list{
public:
    void ProcessRun()
    {
        while(1)
        {

        }
    }

    pcb_list(Alg choice)
        :Run(nullptr),
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
            Run = PCB_Data[1];
            PCB_Data[0]->Pstatus = RUN;
            Head = Tail = new Node(PCB_Data[1]);
            for(int i = 2; i < Pcount; i++)
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
    PCB* Run;
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