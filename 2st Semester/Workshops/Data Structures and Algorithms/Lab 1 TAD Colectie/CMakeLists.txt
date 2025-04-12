cmake_minimum_required(VERSION 3.30)
project(Colectie)

set(CMAKE_CXX_STANDARD 20)

add_executable(Colectie main.cpp
        ProiectC++/Colectie/Colectie.cpp
        ProiectC++/Colectie/IteratorColectie.cpp
        Teste/TestScurt.cpp
        Teste/TestExtins.cpp
)
