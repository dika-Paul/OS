#include<bits/stdc++.h>

const int USER_MAXN = 10;
const int FILE_MAXN = 10;

struct FILE_node{
    std::string file_name;
    int file_protect_num;
    int file_length;

    FILE_node(std::string name = "****", int protect_num = 7, int length = 0)
        :file_name(name),
        file_protect_num(protect_num),
        file_length(length)
    {}
};

typedef
struct USER_FILE_directory{
    std::string user_name;
    std::list<FILE_node*> file_directory;

    USER_FILE_directory(std::string name = "none")
        :user_name(name),
        file_directory(std::list<FILE_node*>())
    {
        /*建立默认文件*/
        file_directory.push_back(new FILE_node(user_name, 7, 888));
        file_directory.push_back(new FILE_node("main", 7, 999));
    }
}UFD;

typedef
struct  OPEN_FILE_node{
    int file_num;
    int file_protect_num;
    FILE_node* file_ptr;
    
    OPEN_FILE_node(int num, int protect_num, FILE_node* ptr)
        :file_num(num),
        file_protect_num(protect_num),
        file_ptr(ptr)
    {
        while(file_ptr->file_protect_num & file_protect_num != file_protect_num)
        {
            std::cout << "Your file's open mode is illeage! input again     ";
            std::cin >> protect_num;
            protect_num = (protect_num/100)<<2 + (protect_num%100/10)<<1 + (protect_num%10);
            file_protect_num = protect_num;
        }
    }
}OFN;

typedef
class MAIN_FILE_system{
public:
    MAIN_FILE_system()
        :user_directory(std::list<UFD>()),
        open_file_directory(std::vector<OFN>(5))
    {
        user_directory.push_back(UFD("admin"));
        while(user_directory.size() < USER_MAXN)
        {
            std::cout << "Do you want to log up a new account? y/n?   ";
            char c;
            std::cin >> c;
            if(c == 'y' || c == 'Y')
            {
                std::string user_name;
                std::cout << "Please enter your account name:   ";
                std::cin >> user_name;
                user_directory.push_back(UFD(user_name));
            }
        }
    }
    void sys_operate()
    {
        std::list<UFD>::iterator user_it = user_directory.begin();
        
    }

private:
    std::list<UFD> user_directory;
    std::vector<OFN> open_file_directory;
    void creat();
    void del();
    void open();
    void close();
    void read();
    void write();
}MFS;
