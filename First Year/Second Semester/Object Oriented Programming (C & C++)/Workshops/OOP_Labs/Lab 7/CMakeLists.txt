cmake_minimum_required(VERSION 3.3.3)
project(C__Tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__Tests main.cpp
        headers/domain.h
        headers/repository.h
        headers/service.h
        headers/ui.h
        src/domain.cpp
        src/repository.cpp
        src/service.cpp
        src/ui.cpp
        tests/tests_domain.cpp
        tests/tests_domain.h
        tests/tests_repository.cpp
        tests/tests_repository.h
        src/validator.cpp
        headers/validator.h
        tests/tests_validator.cpp
        tests/tests_validator.h
        tests/tests_service.cpp
        tests/tests_service.h
)
