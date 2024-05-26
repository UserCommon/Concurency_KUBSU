cmake_minimum_required(VERSION 3.9)
project(MyProject LANGUAGES CXX)

find_package(OpenMP REQUIRED)
add_executable(MyProject main.cpp)
target_link_libraries(MyProject PRIVATE OpenMP::OpenMP_CXX)
