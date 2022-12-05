#include<bits/stdc++.h>

using namespace std;

const int Pcount = 5;

enum Status{
    RUN, WAIT
};

typedef class ProcessControlBlock{
public:
    friend struct cmp;
    friend void ProcessDisplay(PCB* pcblen[]);
    ProcessControlBlock(int n);
    ~ProcessControlBlock();

private:
    int ID;
    int Priority;
    int Runtime;
    int Totaltime;
    Status Pstatus;
}PCB;



struct cmp{
	bool operator()(PCB* P1,PCB* P2){
		return P1->Priority < P2->Priority; 
	}
};

priority_queue<PCB*, vector<PCB*>, cmp> ProcessQueue;

int main()
{
    return 0;
}