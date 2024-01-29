#include"rpcprovider.h"
#include <iostream>
#include "mprpcapplication.h"


void RpcProvider::NotifyService(google::protobuf::Service *service){
    
}

void RpcProvider::Run(){
    std::cout<<"启动rpc服务节点，开始提供rpc远程网络调用服务"<<std::endl;
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip,port);
    std::cout<<"RpcProvider listen on "<<ip<<":"<<port<<std::endl;
    //创建tcpServer对象
    muduo::net::TcpServer server(&m_eventLoop,address,"RpcProvider");

    //注册链接回调
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    //线程池
    server.setThreadNum(4);

    //启动服务端
    server.start();

    //让当前线程进行阻塞等待
    m_eventLoop.loop();
}



void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn){

}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &conn,
                                     muduo::net::Buffer *buffer, 
                                     muduo::Timestamp stamp){

}