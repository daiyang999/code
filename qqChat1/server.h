#ifndef SERVER_H
#define SERVER_H

#include"global.h"
class server{
private:
    int server_port;//服务器端口号  
    int server_sockfd;//设为listen状态的套接字描述符
    string server_ip;//服务器ip
    static vector<bool> sock_arr;//保存所有的套接字描述符
    static unordered_map<string,int> name_sock_map;//名字和套接字描述符
    static pthread_mutex_t name_sock_mutx;//互斥锁
    static unordered_map<int,set<int> > group_map;
    static pthread_mutex_t group_mutx;
    static unordered_map<string,string> from_to_map;
    static pthread_mutex_t from_mutex;
public:
    server(int port,string ip);
    ~server();
    void run();//服务器开始服务
    static void RecMsg(int epollfd,int conn);//子线程工作的静态函数
    static void setnonblocking(int conn);
    static void HandleRequest(int epollfd,int conn,string str,tuple<bool,string,string,int,int> &info);
};


#endif