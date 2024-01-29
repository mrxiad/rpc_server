#ifndef RPCPROVIDER_H
#define RPCPROVIDER_H


#include "google/protobuf/service.h"
#include<muduo/net/TcpServer.h> 
#include<muduo/net/EventLoop.h>
#include<muduo/net/InetAddress.h>
#include <memory>

// 框架提供的专门发布rpc服务的网络对象类
class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();

private:
    
    muduo::net::EventLoop m_eventLoop; // TcpServer底层会使用muduo库中的EventLoop来实现epoll

    void OnConnection(const muduo::net::TcpConnectionPtr &conn);
    void OnMessage(const muduo::net::TcpConnectionPtr &conn,
                                     muduo::net::Buffer *buffer, 
                                     muduo::Timestamp stamp);
};

#endif