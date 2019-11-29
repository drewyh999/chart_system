cmake_minimum_required(VERSION 3.15)
project(chart_system)

set(CMAKE_CXX_STANDARD 11)

add_executable(chart_system MainWindow.cpp MainWindow.h ui_header.h Property.cpp Property.h Curve_Color.cpp Curve_Color.h Scroll_Speed.cpp Scroll_Speed.h Channel_Count.cpp Channel_Count.h ChartContainer.cpp ChartContainer.h ChartRow.cpp ChartRow.h DataProcessor.cpp DataProcessor.h test_ChartRow_GUI.cpp)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)


find_package(Qt5Core)
find_package(Qt5Widgets)
target_link_libraries(
        ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        )
qt5_use_modules(${PROJECT_NAME} Core Widgets OpenGL Xml Gui Charts)