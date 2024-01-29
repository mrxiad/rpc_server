/*
UserService原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
*/


#include <iostream>
#include <string>
#include "user.pb.h"
#include "rpcprovider.h"
#include "mprpcapplication.h"
using namespace std;

class UserService : public fixbug::UserServiceRpc {

    /*
        原本是这俩方法
    */
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;  
        return false;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id:" << id << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }
    //需要改造成以下的
    /*
        virtual void Login(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done);
        virtual void Register(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                            const ::fixbug::RegisterRequest* request,
                            ::fixbug::RegisterResponse* response,
                            ::google::protobuf::Closure* done);
    */

    virtual void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)override
    {

            /* 
                这里实现登录逻辑
                例如，验证用户名和密码
                设置 response 的值
            */

            // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
            std::string name = request->name();
            std::string pwd = request->pwd();

            // 做本地业务
            bool login_result = Login(name, pwd); 

            // 把响应写入  包括错误码、错误消息、返回值
            fixbug::ResultCode *code = response->mutable_result();
            code->set_errcode(0);
            code->set_errmsg("");
            response->set_sucess(login_result);

            // 执行回调操作   执行响应对象数据的序列化和网络发送（都是由框架来完成的）
            done->Run();
    }

    virtual void Register(::google::protobuf::RpcController* controller,
                            const ::fixbug::RegisterRequest* request,
                            ::fixbug::RegisterResponse* response,
                            ::google::protobuf::Closure* done)override
    {
        
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_sucess(ret);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    //provider.NotifyService(new UserService2());增加其他的服务

    // 启动一个rpc服务发布节点   Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}