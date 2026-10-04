cmake_minimum_required(VERSION 3.30)
project(TAD_Matrice_LSI)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAD_Matrice_LSI
        main.cpp
        "TAD Matrice/Matrice.cpp"
        "Teste/TestScurt.cpp"
        "Teste/TestExtins.cpp"
)
