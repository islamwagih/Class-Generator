cmake_minimum_required(VERSION 3.25)
project(iniClassGenerator)

set(CMAKE_CXX_STANDARD 17)
set(GUI ../GUI)
include_directories(${GUI})
add_executable(iniClassGenerator main.cpp CodeGeneratorINI.cpp CodeGeneratorINI.h ${GUI}/headers/Config.h ${GUI}/sources/Config.cpp ${GUI}/sources/rootconfig.cpp ${GUI}/headers/rootconfig.h fileWriter.h)
