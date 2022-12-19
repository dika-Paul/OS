#include<bits/stdc++.h>

using namespace std;

class PROCESS{
public:

private: 
    vector<int> AP;                                 //资源申请矢量
    int VPMAXCLAIM;                                 //对资源的最大需求量
    int VALLOCATION;                                //完成请求标志
    int VCOUNT;                                     //进程请求计数器
};

class OS{
public:

private:
    vector<PROCESS> P_array;                        //进程表
    int TOTAL;                                      //已分配的系统资源总数
    int REMAINDER;                                  //剩余的系统资源数
    int INQUIRY;                                    //当前运行的进程号
    int OPTION;                                     //选择标志
};