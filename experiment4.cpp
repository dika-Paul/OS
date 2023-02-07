#include<bits/stdc++.h>

const int USER_MAXN = 10;
const int FILE_MAXN = 10;

struct FILE_node{
    std::string file_name;
    int file_protect_num;
    int file_length;

    FILE_node()
        :file_name("****"),
        file_protect_num(0),
        file_length(0)
    {}
    FILE_node(std::string name, int protect_num, int length)
        :file_name(name),
        file_protect_num(protect_num),
        file_length(length)
    {}
    void file_info_print()
    {
        std::cout << std::setw(16) << std::left << file_name << std::setw(16) << std::left << (std::bitset<3>)file_protect_num << file_length << std::endl;
    }
};

typedef
struct USER_FILE_directory{
    std::string user_name;
    std::list<FILE_node*> file_directory;

    USER_FILE_directory()
        :user_name("none"),
        file_directory(std::list<FILE_node*>())
    {}
    USER_FILE_directory(std::string name)
        :user_name(name),
        file_directory(std::list<FILE_node*>())
    {
        /*建立默认文件*/
        file_directory.push_back(new FILE_node(user_name, 7, 888));
        file_directory.push_back(new FILE_node("main", 7, 999));
    }
    void directory_info_print()
    {
        std::cout << "File Name       Protection     Code Length\n";
        for(std::list<FILE_node*>::iterator it = file_directory.begin(); it != file_directory.end(); it++)
        {
            (*it)->file_info_print();
        }
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
        open_file_directory(std::list<OFN>())
    {
        user_directory.push_back(UFD("admin"));
        while(user_directory.size() < USER_MAXN)
        {
            std::cout << "Do you want to log up a new account? Y/N?   ";
            char c;
            std::cin >> c;
            if(c == 'y' || c == 'Y')
            {
                std::string user_name;
                std::cout << "Please enter your account name:   ";
                std::cin >> user_name;
                user_directory.push_back(UFD(user_name));
            }
            else    break;
        }
    }
    void sys_operate()
    {
        user_it = user_directory.begin();
        std::cout << "Your name?     ";
        std::string name;
        std::cin >> name;
        while((*user_it).user_name != name)                    //遍历链表查找用户名,若没找到用户名，则重新输入
        {
            user_it++;
            if(user_it == user_directory.end())
            {
                std::cout << "Your name is not in the user name table, try again.\n";
                std::cin >> name;
                user_it = user_directory.begin();
            }
        }
        (*user_it).directory_info_print();
        std::string input_command;
        std::cout << "Command name?   ";
        std::cin >> input_command;
        while(input_command != "bye")
        {
            if(input_command == "create")   creat();
            else if(input_command == "delete")  del();
            else if(input_command == "open")    open();
            else if(input_command == "close")   close();
            else if(input_command == "write")   write();
            else    std::cout << "Command name given is wrong, input again    ";
            std::cin >> input_command;
        }    
        (*user_it).directory_info_print(); 
        std::cout << "Good bye";
    }

private:
    std::list<UFD> user_directory;
    std::list<OFN> open_file_directory;
    std::list<UFD>::iterator user_it;
    void creat()
    {}
    void del()
    {}
    void open()
    {}
    void close()
    {}
    void read()
    {}
    void write()
    {}
}MFS;


int main()
{
    MFS mfs;
    mfs.sys_operate();
    return 0;
}