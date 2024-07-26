cmake_minimum_required(VERSION 3.0.0)
project(DataFrame)
add_library(DataFrame src/DataFrame.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
