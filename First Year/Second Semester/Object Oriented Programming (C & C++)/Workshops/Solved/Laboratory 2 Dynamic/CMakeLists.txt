cmake_minimum_required(VERSION 3.3.3)
project(OOP_lab2 C)

set(CMAKE_C_STANDARD 11)

add_executable(OOP_lab2 main.c
        Domain/domain.c
        Domain/domain.h
        Repository/repository.c
        Repository/repository.h
        Tests/tests.h
        Tests/repository_tests.c
        Tests/service_tests.c
        UI/ui.c
        UI/ui.h
        Service/service.c
        Service/service.h
        Tests/domain_tests.c)
