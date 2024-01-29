#include"rpcprovider.h"
#include <iostream>
#include "mprpcapplication.h"


void RpcProvider::NotifyService(google::protobuf::Service *service){
    std::cout<<"注册服务"<<std::endl;
}

void RpcProvider::Run(){
    std::cout<<"启动rpc服务节点，开始提供rpc远程网络调用服务"<<std::endl;
}