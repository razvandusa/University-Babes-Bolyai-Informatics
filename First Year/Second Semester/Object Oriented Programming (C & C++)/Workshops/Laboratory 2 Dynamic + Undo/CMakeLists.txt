cmake_minimum_required(VERSION 3.3.3)
project(lab2_4 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
#


add_executable(lab2_4 main.c
        model/participant.h
        model/participant.c
        repo/repo.h
        ui/ui.c
        ui/ui.h
        service/service_participanti.c
        service/service_participanti.h
        repo/repo.c
        util/util.h
        util/util.c
        teste/teste_repo.c
        teste/teste_domain.c
        teste/teste_service.c
        teste/teste_domain.h
        teste/teste_repo.h
        teste/teste_service.h
        teste/test_all.h
        model/validation.c
        model/validation.h)
