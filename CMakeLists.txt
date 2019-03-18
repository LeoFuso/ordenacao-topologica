cmake_minimum_required(VERSION 3.13)
project(ordenacao_topologica C)

set(CMAKE_C_STANDARD 11)

add_executable(ordenacao_topologica main.c helper.h ordenacao_topologica.c ordenacao_topologica.h helper.c)