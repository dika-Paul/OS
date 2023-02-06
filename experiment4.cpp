#include<bits/stdc++.h>

const int USER_MAXN = 10;
const int FILE_MAXN = 10;

struct FILE_node{
    std::string file_name;
    int file_protect_num;
    int file_length;
    FILE_node(std::string name = "****", int protect_num = 0, int length = 0)
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
        file_directory.push_back(new FILE_node(user_name, 11, 888));
    }
}UFD;

typedef
struct  OPEN_FILE_directory{
    int file_num;
    int file_protect_num;
    FILE_node* file;

}OFD;

typedef
class MAIN_FILE_directory{
public:
    MAIN_FILE_directory();

private:
    std::list<UFD> user_directory;
    std::vector<OFD> open_file_directory;
    void creat();
    void del();
    void open();
    void close();
    void read();
    void write();
}MFD;
