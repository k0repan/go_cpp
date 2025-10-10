cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "Go")
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-audio.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-graphics.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-network.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-system.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-window.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-main.lib")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
