cmake_minimum_required(VERSION 3.30)
project(Rochii)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Rochii main.cpp
        src/domain.cpp
        headers/domain.h
        src/repository.cpp
        headers/repository.h
        src/service.cpp
        headers/service.h
        src/gui.cpp
        headers/gui.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        tests/tests_repository.cpp
        tests/tests_repository.h
        tests/tests_service.cpp
        tests/tests_service.h
        tests/tests_utils.cpp
        tests/tests_utils.h)
target_link_libraries(Rochii
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

