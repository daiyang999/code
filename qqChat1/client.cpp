#include"client.h"
client::client(int port, string ip):server_port(port),server_ip(ip)
{
}

client::~client()
{
    close(sock);
}

void client::run()
{
    sock=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(server_port);
    servaddr.sin_addr.s_addr=inet_addr(server_ip.c_str());

    if(connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        perror("connect");
        exit(1);
    }
    cout<<"连接服务器成功！"<<endl;
    
    HandleClient(sock);
    return;
}

void client::SendMsg(int conn)
{
    while(1){
        string str;
        cin>>str;
        if(conn>0){
            str="content:"+str;
        }else{
            str="gr_message:"+str;
        }
        
        int ret=send(abs(conn),str.c_str(),str.length(),0);
        if(str=="content:exit"||ret<=0){
            break;
        }
    }
}

void client::RecMsg(int conn)
{
    char buffer[1000];
    while(1){
        memset(buffer,0,sizeof(buffer));
        int len=recv(conn,buffer,sizeof(buffer),0);
        if(len<=0){
            break;
        }
        cout<<"收到服务器发来的消息："<<buffer<<endl;
    }
}

void client::HandleClient(int conn)
{
    int choice;
    string name,pass,pass1;
    bool if_login=false;
    string login_name;

    ifstream f("cookie.txt");
    string cookie_str;
    if(f.good()){
        f>>cookie_str;
        f.close();
        cookie_str="cookie:"+cookie_str;
        send(sock,cookie_str.c_str(),cookie_str.length()+1,0);

        char cookie_ans[100];
        memset(cookie_ans,0,sizeof(cookie_ans));
        recv(sock,cookie_ans,sizeof(cookie_ans),0);

        string ans_str(cookie_ans);
        if(ans_str!="NULL"){
            if_login=true;
            login_name=ans_str;
        }
    }

    cout<<" ------------------\n";
    cout<<"|                  |\n";
    cout<<"| 请输入你要的选项:|\n";
    cout<<"|    0:退出        |\n";
    cout<<"|    1:登录        |\n";
    cout<<"|    2:注册        |\n";
    cout<<"|                  |\n";
    cout<<" ------------------ \n\n";

    while(1){
        if(if_login)break;
        cin>>choice;
        if(choice==0)break;
        else if(choice==2){
            cout<<"注册的用户名：";
            cin>>name;
            while(1){
                cout<<"密码：";
                cin>>pass;
                cout<<"确认密码：";
                cin>>pass1;
                if(pass==pass1)break;
                else{
                    cout<<"两次密码不一致！"<<endl;
                }
            }
            name="name:"+name;
            pass="pass:"+pass;
            string str=name+pass;
            send(conn,str.c_str(),str.length(),0);
            cout<<"注册成功！"<<endl;
            cout<<"继续输入你要的选项！";
        }
        else if(choice==1&&!if_login){
            while(1){
                cout<<"用户名：";
                cin>>name;
                cout<<"密码：";
                cin>>pass;
                string str="login"+name;
                str+="pass:";
                str+=pass;
                send(sock,str.c_str(),str.length(),0);
                char buffer[1000];
                memset(buffer,0,sizeof(buffer));
                recv(sock,buffer,sizeof(buffer),0);
                string recv_str(buffer);
                if(recv_str.substr(0,2)=="ok"){
                    if_login=true;
                    login_name=name;

                    string tmpstr=recv_str.substr(2);
                    tmpstr="cat > cookie.txt <<end \n"+tmpstr+"\nend";
                    system(tmpstr.c_str());

                    cout<<"登陆成功！"<<endl;
                    break;
                }else{
                    cout<<"用户名或密码错误！"<<endl;
                }
            }
        }
    }
    while(if_login&&1){
        if(if_login){
            system("clear");
            cout<<"        欢迎回来,"<<login_name<<endl;
            cout<<" -------------------------------------------\n";
            cout<<"|                                           |\n";
            cout<<"|          请选择你要的选项：               |\n";
            cout<<"|              0:退出                       |\n";
            cout<<"|              1:发起单独聊天               |\n";
            cout<<"|              2:发起群聊                   |\n";
            cout<<"|                                           |\n";
            cout<<" ------------------------------------------- \n\n";
        }
        cin>>choice;
        if(choice==0)break;
        if(choice==1){
            cout<<"请输入对方用户名: ";
            string target_name,content;
            cin>>target_name;
            string sendstr("target:"+target_name+"from:"+login_name);
            send(sock,sendstr.c_str(),sendstr.length(),0);
            cout<<"清输入你想说的话（exit结束）:"<<endl;
            thread t1(client::SendMsg,conn);
            thread t2(client::RecMsg,conn);
            t1.join();
            t2.join();
        }else if(choice==2){
            cout<<"清输入群号："<<endl;
            int num;
            cin>>num;
            string sendstr("group:"+to_string(num));
            send(sock,sendstr.c_str(),sendstr.length(),0);
            cout<<"请输入你想说的话（exit）结束："<<endl;
            thread t1(client::SendMsg,-conn);
            thread t2(client::RecMsg,conn);
            t1.join();
            t2.join();
        }
    }
    close(sock);
}
