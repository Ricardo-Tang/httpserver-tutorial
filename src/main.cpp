#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
int main(){
    //1.创建套接字
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        std::cerr<<"socket error"<<std::endl;
        exit(0);
    }
    //2.绑定对应ip和端口
    unsigned short port = 5000;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    int ret = bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        std::cerr<<"bind"<<std::endl;
        exit(0);
    }

    //3.设置监听
    ret = listen(sfd,128);
    if(ret==-1){
        std::cerr<<"listen"<<std::endl;
        exit(0);
    }

    //4.阻塞等待并接受客户端连接
    struct sockaddr_in clientaddr;
    socklen_t clientlen=sizeof(clientlen);
    int cfd = accept(sfd,(struct sockaddr*)&clientaddr,&clientlen);
    if(cfd==-1){
        std::cerr<<"accept"<<std::endl;
        exit(0);
    }

    //5.与客户端通信
    char buffer[2048];
    bzero(buffer,sizeof(buffer));
    int len =recv(cfd,buffer,sizeof(buffer),0);
    if(len<0){
        std::cerr<<"read"<<std::endl;
        exit(0);
    }else if(len==0){
        std::cout<<"客户端已关闭"<<std::endl;

    }else{
        std::cout<<buffer;
    }
    close(cfd);
    close(sfd);
    return 0;
}