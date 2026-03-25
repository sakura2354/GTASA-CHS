cmake_minimum_required(VERSION 3.10)

project(gtasa_utf8_patch)

# 设置 NDK 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -O3")

# 包含头文件路径
include_directories(include jni)

# 生成动态库
add_library(gtasa_utf8 SHARED
    jni/main.cpp
    jni/hooks.cpp
    jni/utils.cpp
)

# 链接 Android 系统日志库和图形库
target_link_libraries(gtasa_utf8 log android)
