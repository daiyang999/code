#ifndef CLIENT_H
#define CLIENT_H

#include"global.h"

class client{
private:
    int server_port;
    string server_ip;
    int sock;
public:
    client(int port,string ip);
    ~client();
    void run();
    static void SendMsg(int conn);
    static void RecMsg(int conn);
    void HandleClient(int conn);
};

#endif