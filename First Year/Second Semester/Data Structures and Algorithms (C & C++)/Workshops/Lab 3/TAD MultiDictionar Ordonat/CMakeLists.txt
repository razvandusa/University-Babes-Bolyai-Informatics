cmake_minimum_required(VERSION 3.30)
project(MultiDictionar_Ordonat)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiDictionar_Ordonat
                App.cpp
        "Proiect C++/MDO.cpp"
                "Proiect C++/IteratorMDO.cpp"
                Teste/TestScurt.cpp
                Teste/TestExtins.cpp
)