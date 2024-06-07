cmake_minimum_required(VERSION 3.28)
project(Football_Team_Management)

set(CMAKE_CXX_STANDARD 17)

add_executable(Football_Team_Management main.cpp
        Player.cpp
        Team.cpp
        Player.h
        Team.h
        Admin.cpp
        Admin.h)
