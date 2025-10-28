cmake_minimum_required(VERSION 3.34)

set(PROJECT_NAME Go)
project(${PROJECT_NAME} VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

function(includeDependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG ${gitTag}
        GIT_SHALLOW True
        GIT_PROGRESS True
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB_NAME raylib)
find_package(${LIB_NAME} QUIET)
if (NOT ${LIB_NAME}_FOUND)
    message(STATUS "Getting ${LIB_NAME} from GitHub...")
    includeDependency(${LIB_NAME} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB_NAME}")
endif()

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/board.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})