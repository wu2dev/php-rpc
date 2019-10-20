cmake_minimum_required(VERSION 3.15)
project(php_rpc)

set(CMAKE_CXX_STANDARD 14)
set(SRC_LIST src/main.cpp src/RPCServer.cpp src/RPCServer.h src/RPCClient.cpp src/RPCClient.h)
set(PHP_INCLUDE /usr/include/php)
include_directories(${PHP_INCLUDE}/main)
include_directories(${PHP_INCLUDE}/Zend)
include_directories(${PHP_INCLUDE}/)
add_executable(php_rpc ${SRC_LIST})
target_link_libraries(php_rpc jsoncpp)

