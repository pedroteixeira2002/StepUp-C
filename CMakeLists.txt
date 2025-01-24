cmake_minimum_required(VERSION 3.24)
project(LP_G14 C)

set(CMAKE_C_STANDARD 11)

add_executable(LP_G14
        main.c strs.h clients.c clients.h clients.h utils.c menus.c menus.h products.c products.h materials.c materials.h orders.h production.c orders.c files.c files.h)
