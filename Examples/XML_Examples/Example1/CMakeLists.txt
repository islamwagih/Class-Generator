cmake_minimum_required(VERSION 3.24)
project(Example1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Example1
        main.cpp

        pugixml.cpp

        )
