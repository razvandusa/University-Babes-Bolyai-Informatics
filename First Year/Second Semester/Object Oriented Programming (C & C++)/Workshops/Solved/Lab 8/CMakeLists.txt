cmake_minimum_required(VERSION 3.3.3)
project(Lab_8)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_8 main.cpp
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
        headers/exceptions.h
        tests/tests_exceptions.cpp
        tests/tests_exceptions.h
        src/contract.cpp
        headers/contract.h
        tests/tests_contract.cpp
        tests/tests_contract.h
        src/undo.cpp
        headers/undo.h
        tests/tests_undo.cpp
        tests/tests_undo.h
)
