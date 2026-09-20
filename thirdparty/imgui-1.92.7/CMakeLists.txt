cmake_minimum_required(VERSION 3.25)

project(imgui)

add_library(${PROJECT_NAME}
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    misc/cpp/imgui_stdlib.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)