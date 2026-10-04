cmake_minimum_required(VERSION 3.30)
project(Produse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Produse
        main.cpp
        src/service.cpp
        src/repository.cpp
        src/domain.cpp
        tests/tests_repository.cpp
        src/gui.cpp
        tests/tests_service.cpp
        tests/tests_service.h
        headers/observer.h)

target_link_libraries(Produse
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

