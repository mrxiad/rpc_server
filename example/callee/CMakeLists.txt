# 收集目录下所有文件
file(GLOB_RECURSE ALL_FILES
        "*.cc"
        "../*.cc"
        )

add_executable(provider ${ALL_FILES})

find_library(protobuf protobuf)

if (NOT protobuf)
    message(FATAL_ERROR "protobuf库未找到")
else ()
    message(STATUS "protobuf库路径为: ${protobuf}")
endif ()

target_link_libraries(provider mprpc protobuf)