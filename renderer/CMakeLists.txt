# cmake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(render)

# INCLUDE_DIRECTORIES(. ./runner)

# 查找当前目录下的所有源文件，并将文件保存到DIR_SOURCES变量
aux_source_directory(. DIR_SOURCES)

# 指定生成目标
add_executable(Run ${DIR_SOURCES})

# 添加runner子目录
add_subdirectory(runner)

# 添加链接库
target_link_libraries(Run Runlibs)
