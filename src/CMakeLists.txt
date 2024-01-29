set(SRC_LIST
        mprpcapplication.cc 
        mprpcconfig.cc
        rpcprovider.cc)

#生成动态库
add_library(mprpc SHARED ${SRC_LIST})

#查找muduo库
find_library(MUDUO_NET muduo_net)
find_library(MUDUO_BASE muduo_base)

if(NOT MUDUO_NET)
    message(FATAL_ERROR "muduo_net库没有找到")
endif()

if(NOT MUDUO_BASE)
    message(FATAL_ERROR "muduo_base库没有找到")
endif()

#链接库
target_link_libraries(mprpc muduo_net muduo_base pthread)