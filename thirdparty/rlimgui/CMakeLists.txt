cmake_minimum_required(VERSION 3.25)

project(rlimgui)

add_library(rlimgui
    rlImGui.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui)