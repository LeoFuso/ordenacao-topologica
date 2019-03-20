cmake_minimum_required(VERSION 3.13)
project(ordenacao_topologica C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c ordenacao_topologica.c helper.c grafo.c queue.c queue.h)