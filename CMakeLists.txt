cmake_minimum_required(VERSION 3.28.3)

project(
    myProject
    LANGUAGES C CXX
    VERSION 1.0.0
    
)

add_executable(run main.cpp input_parsing.cpp)