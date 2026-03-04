cmake_minimum_required(VERSION 3.30)
project(Apartamente)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Apartamente main.cpp
        src/domain.cpp
        headers/domain.h
        src/repository.cpp
        headers/repository.h
        src/service.cpp
        headers/service.h
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
        src/GUI.cpp
        headers/GUI.h
)
target_link_libraries(Apartamente
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

