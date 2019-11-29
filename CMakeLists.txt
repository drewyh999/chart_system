cmake_minimum_required(VERSION 3.1.0)

project(chart_system)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


find_package(Qt5 COMPONENTS Core Gui Charts REQUIRED)

aux_source_directory(. MAIN_SRC)

add_executable(chart_system  ${MAIN_SRC} main.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Charts
)
