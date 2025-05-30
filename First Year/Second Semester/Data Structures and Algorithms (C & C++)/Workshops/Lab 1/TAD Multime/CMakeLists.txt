cmake_minimum_required(VERSION 3.30)
project(TAD_Multime)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAD_Multime main.cpp
        ProiectC++/Multime/Multime.cpp
        ProiectC++/Multime/IteratorMultime.cpp
        Teste/TestExtins.cpp
        Teste/TestScurt.cpp)
