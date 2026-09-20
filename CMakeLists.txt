cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory(thirdparty/raylib-6.0)
add_subdirectory(thirdparty/imgui-1.92.7)
add_subdirectory(thirdparty/rlimgui)

project(2d-shapes)
set(SOURCE_FILES
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui rlimgui)