cmake_minimum_required(VERSION 3.31)
project(Melodii)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Melodii main.cpp
        headers/domain.h
        src/repository.cpp
        headers/repository.h
        tests/tests_repository.cpp
        tests/tests_repository.h
        src/service.cpp
        headers/service.h
        src/gui.cpp
        headers/gui.h
        headers/observer.h
        tests/tests_service.cpp
        tests/tests_service.h)

target_link_libraries(Melodii
        Qt::Core
        Qt::Gui
        Qt::Widgets
)