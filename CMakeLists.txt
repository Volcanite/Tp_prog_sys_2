cmake_minimum_required(VERSION 3.30)
project(untitled3 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled3
        gettftp.c
        gettftp.h
        get_server_adress.c
        get_server_adress.h
        create_socket.c
        create_socket.h)
