cmake_minimum_required(VERSION 3.20)
project(app_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(mylib REQUIRED) 

add_executable(app main.cpp)

#connect as packet, not src
target_link_libraries(app PRIVATE mylib::mylib)
