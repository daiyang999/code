#include"server.h"
vector<bool> server::sock_arr(10000,false);
unordered_map<string,int> server::name_sock_map;
pthread_mutex_t server::name_sock_mutx;
unordered_map<int,set<int> > server::group_map;
pthread_mutex_t server::group_mutx;
unordered_map<string,string> server::from_to_map;
pthread_mutex_t server::from_mutex;
server::server(int port, string ip):server_port(port),server_ip(ip)
{
    pthread_mutex_init(&name_sock_mutx,NULL);
}

server::~server()
{
    for(int i=0;i<sock_arr.size();i++){
        if(sock_arr[i]){
            close(i);
        }
    }
    close(server_sockfd);
}

void server::run()
{
    int LISTENQ=200;
    int i,maxi,listenfd,connfd,sockfd,epfd,nfds;
    ssize_t n;
    socklen_t clilen;
    //声明epoll_event结构体的变量，ev用于注册事件，数组用于回传要处理的事件
    struct epoll_event ev,events[10000];
    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(10000);
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd=socket(PF_INET,SOCK_STREAM,0);
    //把socket设置为非阻塞方式
    setnonblocking(listenfd);
    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;
    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    //设置serveraddr
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(8023);
    bind(listenfd,(sockaddr *)&serveraddr,sizeof(serveraddr));
    listen(listenfd,LISTENQ);
    clilen=sizeof(clientaddr);
    maxi=0;

    boost::asio::thread_pool tp(10);

    while(1){
        cout<<"-------------------"<<endl;
        cout<<"epoll_wait阻塞中"<<endl;
        //等待epoll事件的发生
        nfds=epoll_wait(epfd,events,10000,-1);
        cout<<"epoll_wait返回，有事件发生"<<endl;
        //处理所有发生的事件
        for(i=0;i<nfds;i++){
            //有新客户连接服务器
            if(events[i].data.fd==listenfd){
                connfd=accept(listenfd,(sockaddr *)&clientaddr,&clilen);
                if(connfd<0){
                    perror("connfd<0");
                    exit(1);
                }else{
                    cout<<"用户 "<<inet_ntoa(clientaddr.sin_addr)<<"正在连接！"<<endl;
                }
                //设置用于读操作的文件描述符
                ev.data.fd=connfd;
                //设置用于注册的读操作事件，采用ET边缘触发，为防止多个线程处理一个socket；
                ev.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
                //边缘触发将套接字设置为非阻塞
                setnonblocking(connfd);
                //注册ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN){
                sockfd=events[i].data.fd;
                events[i].data.fd=-1;
                cout<<"接收到读事件"<<endl;

                string recv_str;
                boost::asio::post(boost::bind(RecMsg,epfd,sockfd));
            }
        }
    }
    close(listenfd);
    // int server_sockfd=socket(AF_INET,SOCK_STREAM,0);

    // struct sockaddr_in server_sockaddr;
    // server_sockaddr.sin_family=AF_INET;
    // server_sockaddr.sin_port=htons(server_port);
    // server_sockaddr.sin_addr.s_addr=inet_addr(server_ip.c_str());

    // if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,
    //     sizeof(server_sockaddr))==-1){
    //         perror("bind");
    //         exit(1);
    //     }
    //     if(listen(server_sockfd,20)==-1){
    //         perror("listen");
    //         exit(1);
    //     }
    //     struct sockaddr_in client_addr;
    //     socklen_t length=sizeof(client_addr);

    //     while(1){
    //         int conn=accept(server_sockfd,(struct sockaddr*)&client_addr,&length);
    //         if(conn<0){
    //             perror("connect");
    //             exit(1);
    //         }
    //         cout<<"文件描述符为："<<conn<<" 的客户端成功连接！"<<endl;
    //         sock_arr.push_back(conn);

    //         thread t(server::RecMsg,conn);
    //         t.detach();
    //     }
}

void server::RecMsg(int epollfd,int conn)
{
    tuple<bool,string,string,int,int> info;
    get<0>(info)=false;
    get<3>(info)=-1;
    string recv_str;
    while(1){
        char buf[10];
        memset(buf,0,sizeof(buf));
        int ret=recv(conn,buf,sizeof(buf),0);
        if(ret<0){
            cout<<"recv返回值小于0"<<endl;
            if((errno==EAGAIN)||(errno==EWOULDBLOCK)){
                cout<<"数据读取完毕！"<<endl;
                cout<<"接受到的完整内容为："<<recv_str<<endl;
                cout<<"开始处理事件"<<endl;
                break;
            }
            cout<<"errno:"<<errno<<endl;
            return;
        }else if(ret==0){
            cout<<"recv返回值为0"<<endl;
            return;
        }else{
            cout<<"收到内容如下："<<buf<<endl;
            string tmp(buf);
            recv_str+=tmp;
        }
        
    }
    string str=recv_str;
    HandleRequest(epollfd,conn,str,info);
}

void server::setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0){
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts=opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0){
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }

}

void server::HandleRequest(int epollfd,int conn, string str,tuple<bool,string,string,int,int> &info)
{
    char buffer[1000];
    string name,pass;
    bool if_login=get<0>(info);
    string login_name=get<1>(info);
    string target_name=get<2>(info);
    int target_conn=get<3>(info);
    int group_num=get<4>(info);

    redisContext *redis_target=redisConnect("127.0.0.1",6379);
    if(redis_target->err){
        redisFree(redis_target);
        cout<<"连接redis失败！"<<endl;
    }

    MYSQL *con=mysql_init(NULL);
    mysql_real_connect(con,"127.0.0.1","daiyang","111111","ChatProject",0,NULL,CLIENT_MULTI_STATEMENTS);
    
    if(str.find("cookie:")!=str.npos){
        string cookie=str.substr(7);
        string redis_str="hget "+cookie+" name";
        redisReply *r=(redisReply*)redisCommand(redis_target,redis_str.c_str());
        string send_res;
        if(r->str){
            cout<<"查询redis结果: "<<r->str<<endl;
            send_res=r->str;
        }else{
            send_res="NULL";

        }
        send(conn,send_res.c_str(),send_res.length()+1,0);
    }

    if(str.find("name:")!=str.npos){
        int p1=str.find("name:"),p2=str.find("pass:");
        name=str.substr(p1+5,p2-5);
        pass=str.substr(p2+5,str.length()-p2-4);
        string search="INSERT INTO USER VALUES (\"";
        search+=name;
        search+="\",\"";
        search+=pass;
        search+="\");";
        cout<<"sql语句："<<search<<endl<<endl;
        mysql_query(con,search.c_str());
    }
    else if(str.find("login")!=str.npos){
        int p1=str.find("login"),p2=str.find("pass:");
        name=str.substr(p1+5,p2-5);
        pass=str.substr(p2+5,str.length()-p2-4);
        string search="SELECT * FROM USER WHERE NAME=\"";
        search+=name;
        search+="\";";
        cout<<"sql语句: "<<search<<endl;
        auto search_res=mysql_query(con,search.c_str());
        auto result=mysql_store_result(con);
        int col=mysql_num_fields(result);
        int row=mysql_num_rows(result);

        if(search_res==0&&row!=0){
            cout<<"查询成功！"<<endl;
            auto info=mysql_fetch_row(result);
            cout<<"查询到用户名: "<<info[0]<<" 密码："<<info[1]<<endl;

            if(info[1]==pass){
                cout<<"登陆密码正确！"<<endl;
                string str1="ok";
                if_login=true;
                login_name=name;
                pthread_mutex_lock(&name_sock_mutx);
                name_sock_map[login_name]=conn;
                pthread_mutex_unlock(&name_sock_mutx);

                srand(time(NULL));
                for(int i=0;i<10;i++){
                    int type=rand()%3;
                    if(type==0) str1+='0'+rand()%9;
                    else if(type==1) str1+='a'+rand()%26;
                    else if(type==2) str1+='A'+rand()%26;
                }
                string redis_str="hget "+str1.substr(2)+" name"+login_name;
                redisReply *r=(redisReply*)redisCommand(redis_target,redis_str.c_str());
                redis_str="expire "+str1.substr(2)+" 300";
                r=(redisReply*)redisCommand(redis_target,redis_str.c_str());
                cout<<"随机生成的sessionid为: "<<str1.substr(2)<<endl;

                send(conn,str1.c_str(),str1.length()+1,0);
            }
            else{
                cout<<"登录密码错误！"<<endl;
                char str1[100]="wrong";
                send(conn,str1,strlen(str1),0);
            }
        }else{
            cout<<"查询失败！"<<endl;
            char str1[100]="wrong";
            send(conn,str1,strlen(str1),0);
        }
    }
    else if(str.find("target:")!=str.npos){
        int pos1=str.find("from");
        string target=str.substr(7,pos1-7),from=str.substr(pos1+4);
        target_name=target;
        if(name_sock_map.find(target)==name_sock_map.end()){
            cout<<"源用户为："<<login_name<<",目标用户："<<target_name<<"人未登录，无法发送请求！"<<endl;
        }else{
            cout<<"源用户："<<login_name<<"向目标用户"<<target_name<<"发起的私聊即将建立！"<<endl;
            cout<<"目标用户的套接字描述符为："<<name_sock_map[target]<<endl;
            target_conn=name_sock_map[target];
        }
    }
    else if(str.find("content:")!=str.npos){
        if(target_conn==-1){
            cout<<"找不到目标用户："<<target_name<<"的套接字，将尝试重新查找！"<<endl;
            if(name_sock_map.find(target_name)!=name_sock_map.end()){
                target_conn=name_sock_map[target_name];
                cout<<"查找成功！"<<endl;
            }else{
                cout<<"查找失败！"<<endl;
            }
        }
        string recv_str(str);
        string send_str=recv_str.substr(8);
        cout<<"用户："<<login_name<<" 向 "<<target_name<<" 发送 "<<send_str<<endl;
        send_str="["+login_name+"]:"+send_str;
        send(target_conn,send_str.c_str(),send_str.length(),0);
    }else if(str.find("group:")!=str.npos){
        string recv_str(str);
        string num_str=recv_str.substr(6);
        group_num=stoi(num_str);
        cout<<"用户："<<login_name<<" 绑定群聊号为："<<num_str<<endl;
        pthread_mutex_lock(&group_mutx);
        group_map[group_num].insert(conn);
        pthread_mutex_unlock(&group_mutx);
    }
    else if(str.find("gr_message:")!=str.npos){
        string send_str(str);
        send_str=send_str.substr(11);
        send_str="["+login_name+"]:"+send_str;
        cout<<"群聊信息："<<send_str<<endl;
        for(auto i:group_map[group_num]){
            if(i!=conn){
                send(i,send_str.c_str(),send_str.length(),0);
            }
        }
    }

    //线程工作完毕之后重新注册事件
    epoll_event event;
    event.data.fd=conn;
    event.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,conn,&event);


    get<0>(info)=if_login;
    get<1>(info)=login_name;
    get<2>(info)=target_name;
    get<3>(info)=target_conn;
    get<4>(info)=group_num;
}
