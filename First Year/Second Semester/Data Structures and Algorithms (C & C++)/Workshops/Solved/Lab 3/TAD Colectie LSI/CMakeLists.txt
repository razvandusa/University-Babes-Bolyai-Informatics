cmake_minimum_required(VERSION 3.30)
project(TAD_Colectie_LSI)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAD_Colectie_LSI
        main.cpp
        "Multime/IteratorMultime.cpp"
        "Multime/Multime.cpp"
        "Teste/TestScurt.cpp"
        "Teste/TestExtins.cpp"
)