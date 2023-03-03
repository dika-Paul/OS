#include<bits/stdc++.h>

const int USER_MAXN = 10;
const int FILE_MAXN = 10;
const int OPEN_MAXN = 5;

struct FILE_node{
    std::string file_name;
    int file_protect_num;
    int file_length;

    FILE_node()
        :file_name("****"),
        file_protect_num(0),
        file_length(0)
    {}
    FILE_node(std::string name, int protect_num = 7, int length = 0)
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
    
    OPEN_FILE_node(int num)
        :file_num(num),
        file_protect_num(0),
        file_ptr(nullptr)
    {}
    int open_file(int protect_num, FILE_node* ptr)
    {
        while((ptr->file_protect_num & protect_num) != protect_num)
        {
            std::cout << "Your file's open mode is illeage! input again     ";
            std::cin >> protect_num;
            protect_num = ((protect_num/100)<<2) + ((protect_num%100/10)<<1) + (protect_num%10);
            file_protect_num = protect_num;
        }
        file_protect_num = protect_num;
        file_ptr = ptr;
        return file_num;
    }
    void close_file()
    {
        file_protect_num = 0;
        file_ptr = nullptr;
        return;
    }
    void read_file()
    {
        if((file_protect_num - (file_protect_num>>2) - file_num%2) == 0)
        {
            std::cout << "Error message: it is not allowed to read this file!!!\n";
            return;
        }
        std::cout << "This file's length is " << file_ptr->file_length << std::endl;
        return;
    }
    void write_file()
    {
        if((file_protect_num>>2) == 0)
        {
            std::cout << "Error message: it is not allowed to write this file!!!\n";
            return;
        }
        std::string str;
        std::cin >> str;
        file_ptr->file_length = str.length();
        return;
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
        for(int i = 1; i <= OPEN_MAXN; i++)                     //将存放打开文件的链表初始化
            open_file_directory.push_back(OFN(i));
        std::cout << "Your name?     ";
        std::string name;
        std::cin >> name;
        while((*user_it).user_name != name)                     //遍历链表查找用户名,若没找到用户名，则重新输入
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
            std::cout << "Command name?   ";
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
    {
        if((*user_it).file_directory.size() == FILE_MAXN)
        {
            std::cout << "Your space is full, cann't create any more file.\n";
            return;
        }
        std::cout << "The new file's name(less than 9 chars)?    ";
        std::string file_name;
        std::cin >> file_name;
        std::cout << "The new file's protection code?     ";
        int file_protect_num;
        std::cin >> file_protect_num;
        file_protect_num = ((file_protect_num/100)<<2) + ((file_protect_num%100/10)<<1) + (file_protect_num%10);
        (*user_it).file_directory.push_back(new FILE_node(file_name, file_protect_num));
        std::cout << "The new file is created\n";
        (*user_it).directory_info_print();
        return;
    }
    void del()
    {   
        if((*user_it).file_directory.size() == 0)
            {
                std::cout << "There is no file.\n";
                return;
            }
        std::cout << "The file's name to be deleted?    ";
        std::string file_name;
        std::cin >> file_name;
        std::list<FILE_node*>::iterator file_it = (*user_it).file_directory.begin();
        while((*file_it)->file_name != file_name)
        {
            file_it++;
            if(file_it == (*user_it).file_directory.end())
            {
                std::cout << "There have not this file, try again.    ";
                std::cin >> file_name;
                file_it = (*user_it).file_directory.begin();
            }
        }
        bool flag = true;
        for(auto it : open_file_directory)
        {
            if(it.file_ptr->file_name == (*file_it)->file_name)
            {
                flag = false;
                break;
            }
        }
        if(!flag) 
        {    
            (*user_it).directory_info_print();
            return;
        }
        (*user_it).file_directory.erase(file_it);
        std::cout << "The file has been deleted.\n";
        (*user_it).directory_info_print();
    }
    void open()
    {
        if((*user_it).file_directory.size() == 0)
        {
            std::cout << "There is no file.\n";
            return;
        }
        std::cout << "The file's name to be opened?    ";
        std::string file_name;
        std::cin >> file_name;
        std::list<FILE_node*>::iterator file_it = (*user_it).file_directory.begin();
        while((*file_it)->file_name != file_name)
        {
            file_it++;
            if(file_it == (*user_it).file_directory.end())
            {
                std::cout << "There have not this file, try again.    ";
                std::cin >> file_name;
                file_it = (*user_it).file_directory.begin();
            }
        }
        std::cout << "Enter the open mode.     ";
        int file_protect_num;
        std::cin >> file_protect_num;
        file_protect_num = ((file_protect_num/100)<<2) + ((file_protect_num%100/10)<<1) + (file_protect_num%10);
        for(auto it = open_file_directory.begin(); it != open_file_directory.end(); it++)
        {
            if((*it).file_ptr == nullptr)
            {
                int No = (*it).open_file(file_protect_num, (*file_it));
                std::cout << "This file is opened, its open number is " << No << std::endl;
                return;
            }
        }
        std::cout << "There is not enough space to open file.\n";
        (*user_it).directory_info_print();
        return;
    }
    void close()
    {
        std::cout << "The open file number to be closed?      ";
        int file_num;
        std::cin >> file_num;
        while(file_num <=0 || file_num > OPEN_MAXN)
        {
            std::cout << "The number given is illeage, try again.";
            std:: cin >> file_num;
        }
        std::list<OFN>::iterator it = open_file_directory.begin();
        while(file_num != 1)
        {
            it++;
            file_num--;
        }
        (*it).close_file();
        std::cout << "This file is closed.\n";
        (*user_it).directory_info_print();
    }
    void read()
    {
        if(open_file_directory.size() == 0)
        {
            std::cout << "There is no file to read\n";
            return;
        }
        std::cout << "Open file number?    ";
        int file_num;
        std::cin >> file_num;
        std::list<OFN>::iterator it = open_file_directory.begin();
        while(file_num != 1)
        {
            it++;
            file_num--;
        }
        if((*it).file_ptr == nullptr)
        {
            std::cout << "There is no file at this number.\n";
            return;
        }
        (*it).read_file();
        (*user_it).directory_info_print();
        return;
    }
    void write()
    {
        if(open_file_directory.size() == 0)
        {
            std::cout << "There is no file to write\n";
            return;
        }
        std::cout << "Open file number?    ";
        int file_num;
        std::cin >> file_num;
        std::list<OFN>::iterator it = open_file_directory.begin();
        while(file_num != 1)
        {
            it++;
            file_num--;
        }
        if((*it).file_ptr == nullptr)
        {
            std::cout << "There is no file at this number.\n";
            return;
        }
        (*it).write_file();
        (*user_it).directory_info_print();
        return;
    }
}MFS;


int main()
{
    MFS mfs;
    mfs.sys_operate();
    return 0;
}