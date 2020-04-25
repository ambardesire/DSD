cmake_minimum_required(VERSION 3.14)
project(Multicast)

set(CMAKE_CXX_STANDARD 11)

set(COMMON_SRC "PaqueteDatagrama.cpp" "SocketMulticast.cpp" "mensaje.h" )


add_executable(Client Client.cpp ${COMMON_SRC})


add_executable(Server Servidor.cpp ${COMMON_SRC})
