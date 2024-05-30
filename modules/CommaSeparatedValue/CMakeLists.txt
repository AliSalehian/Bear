cmake_minimum_required(VERSION 3.0.0)
project(CommaSeparatedValue)
add_library(CommaSeparatedValue src/CommaSeparatedValue.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
