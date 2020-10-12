cmake_minimum_required(VERSION 3.15)
project(securityLab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(securityLab3 main.cpp Rc4.cpp AesUtils.cpp Aes.cpp)