cmake_minimum_required(VERSION 3.3.3)
project(Lab_13-14)

set(CMAKE_CXX_STANDARD 20)

# Include header files directory
include_directories(headers)

add_executable(Lab_13-14
        main.cpp
        src/contractCrud.cpp
        src/GUI/contractGUI.cpp
        src/GUI/contractCrudGUI.cpp
        src/GUI/contractReadOnlyGUI.cpp
        src/GUI/filterGUI.cpp
        src/GUI/sortGUI.cpp
        src/domain.cpp
        src/repository.cpp
        src/service.cpp
        src/ui.cpp
        src/validator.cpp
        src/contract.cpp
        src/undo.cpp
        src/GUI/GUI.cpp

        tests/tests_domain.cpp
        tests/tests_repository.cpp
        tests/tests_service.cpp
        tests/tests_validator.cpp
        tests/tests_exceptions.cpp
        tests/tests_contract.cpp
        tests/tests_undo.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

target_link_libraries(Lab_13-14 Qt::Core Qt::Gui Qt::Widgets)