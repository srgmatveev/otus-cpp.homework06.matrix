cmake_minimum_required(VERSION 3.9)
set(MY_PROJECT_NAME matrix)
project(${MY_PROJECT_NAME})
add_executable(${MY_PROJECT_NAME} main.cpp)
set_target_properties(${MY_PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )