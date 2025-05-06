cmake_minimum_required(VERSION 3.3.3)
project(Lab_9)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_9 main.cpp
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
        src/disciplineGUI.cpp
        headers/disciplineGUI.h
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(Lab_8
        Qt::Core
        Qt::Gui
        Qt::Widgets
)