cmake_minimum_required(VERSION 3.20)
project(lab5_v15 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(lab5_v15 main.cpp)
target_link_libraries(lab5_v15 PRIVATE Threads::Threads)